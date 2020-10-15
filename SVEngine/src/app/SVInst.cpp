//
// SVInst.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVInst.h"
#include "SVGlobalMgr.h"
#include "SVGlobalParam.h"
//
#include "../env/SVCtxBase.h"
#include "../env/SVCtxIOS.h"
#include "../env/SVCtxOSX.h"
#include "../env/SVEGLContext.h"
//
#include "../script/SVLuaSys.h"

#include "../work/SVTdCore.h"
#include "../work/SVThreadPool.h"

#include "../file/SVFileMgr.h"

#include "../basesys/SVBasicSys.h"
#include "../basesys/SVConfig.h"
#include "../basesys/SVCameraMgr.h"
#include "../basesys/SVARBackgroundMgr.h"
#include "../basesys/SVComData.h"
#include "../basesys/SVResMgr.h"

#include "../event/SVEventMgr.h"
#include "../event/SVEvent.h"

#include "../operate/SVOpBase.h"
#include "../operate/SVOpCreate.h"
#include "../operate/SVOpThread.h"
//
#include "../rendercore/SVRTargetMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVMetal/SVRendererMetal.h"
#include "../rendercore/SVGL/SVRendererGL.h"

#include "../mtl/SVMtlLib.h"
//#include "../mtl/SVMtlCore.h"

using namespace sv;

static void lua_regist_SVInst(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
       //lua_pushcfunction(L, &SVInst::SVInst);
       //lua_pushglobal(L, "SVInst");
//       // 创建userdata要用的元表(其名为Foo), 起码要定义__gc方法, 以便回收内存
//       luaL_newmetatable(L, "SVObject");
//       lua_pushstring(L, "__gc");
//       //lua_pushcfunction(L, &SVObject::gc_obj);
//       lua_settable(L, -3);
    }
}

LUA_REG_IMP(SVInst,lua_regist_SVInst);

SVInst::SVInst() {
    m_sv_st = SV_ST_NULL;
    m_async = false;
    m_ctx = nullptr;
    m_file_sys = nullptr;
    m_render_mgr = nullptr;
    m_event_sys = nullptr;
    m_res_mgr = nullptr;
}

SVInst::~SVInst() {
    m_ctx = nullptr;
    m_file_sys = nullptr;
    m_mtl_lib = nullptr;
    m_render_mgr = nullptr;
    m_event_sys = nullptr;
    m_res_mgr = nullptr;
}

SVInstPtr SVInst::makeCreate() {
    return MakeSharedPtr<SVInst>();
}

SVInstPtr SVInst::share() {
    return std::dynamic_pointer_cast<SVInst>(shareObject()) ;
}

//构建引擎的整个逻辑系统，唯独与渲染器无关
void SVInst::init(bool async) {
    m_async = async;
    //
    m_renderer = nullptr;
    //lua脚本系统
    if(!m_lua_sys) {
        m_lua_sys = MakeSharedPtr<SVLuaSys>( share() );
        m_lua_sys->init();
        SV_LOG_ERROR("sve init m_lua_sys end!\n");
    }
    //文件系统
    if(!m_file_sys) {
        m_file_sys = MakeSharedPtr<SVFileMgr>( share() );
    }
    //加载配置
    m_config.init();
    m_config.loadConfig();
    //消息系统
    m_event_sys = MakeSharedPtr<SVEventMgr>( share() );
    m_event_sys->init();
    //材质库
    m_mtl_lib = MakeSharedPtr<SVMtlLib>( share() );
    m_mtl_lib->init();
    m_event_sys->listenSysEvent(m_mtl_lib,SVMtlLib::procSysEvent);
    //渲染管理
    m_render_mgr = MakeSharedPtr<SVRenderMgr>( share() );
    m_render_mgr->init();
    //资源管理加载
    m_res_mgr = MakeSharedPtr<SVResMgr>( share() );
    m_res_mgr->init();
    m_event_sys->listenSysEvent(m_res_mgr,SVResMgr::procSysEvent);
    //全局
    m_global_mgr = MakeSharedPtr<SVGlobalMgr>( share() );
    m_global_mgr->init();
    //
    if(async) {
        //异步 需要自己开一个线程，同步，不需要
    }
    m_sv_st = SV_ST_WAIT;
}

void SVInst::destroy() {
    m_global_mgr = nullptr;
    //
    if(m_render_mgr) {
        m_render_mgr->destroy();
    }
    //
    if(m_mtl_lib) {
        m_mtl_lib->destroy();
        m_mtl_lib = nullptr;
    }
    //
    m_file_sys = nullptr;
    //去掉脚本系统
    if(m_lua_sys) {
        m_lua_sys->destroy();
        m_lua_sys = nullptr;
    }
    //
    if (m_event_sys) {
        //事件系统最后析够,因为很多其他模块 会注册监听事件
        m_event_sys->destroy();
    }
    m_sv_st = SV_ST_NULL;
}

void SVInst::resize(s32 _w,s32 _h) {
    //相机重置size
    if(m_global_mgr && m_global_mgr->m_camera_mgr ) {
        m_global_mgr->m_camera_mgr->resize(_w, _h);
    }
    //
    //所有target重置大小
    if(m_renderer) {
        m_renderer->resize(_w, _h);
    }
}

//创建渲染器环境
SVCtxBasePtr SVInst::createEnv(SV_R_ENV _type) {
    SVCtxBasePtr t_ctx = nullptr;
#ifdef SV_ANDROID
    if(_type == E_R_GLES_ANDORID) {
        m_rcore = E_R_GLES_ANDORID;
        return m_ctx;
    }
    if(_type == E_R_VULKAN_ANDORID) {
        m_rcore = E_R_VULKAN_ANDORID;
        return m_ctx;
    }
#endif
    
#ifdef SV_OSX
    if(_type == E_R_METAL_OSX) {
        m_rcore = E_R_METAL_OSX;
        m_ctx = MakeSharedPtr<SVCtxOSXMetal>( share() );
        return m_ctx;
    }
    if(_type == E_R_GL_OSX) {
        m_rcore = E_R_GL_OSX;
        m_ctx = MakeSharedPtr<SVCtxOSXGL>( share() );
        return m_ctx;
    }
#endif
        
#ifdef SV_IOS
    if(_type == E_R_METAL_IOS) {
        m_rcore = E_R_METAL_IOS;
        m_ctx = MakeSharedPtr<SVCtxIOSMetal>( share() );
        return m_ctx;
    }
    if(_type == E_R_GLES_IOS) {
        m_rcore = E_R_GLES_IOS;
        m_ctx = MakeSharedPtr<SVCtxIOSGLES>( share() );
        return m_ctx;
    }
#endif
    return nullptr;
}

//销毁渲染环境，包括渲染器
void SVInst::destroyEnv() {
    if(m_renderer){
        m_renderer->clearRes();
        m_renderer->destroy();
        m_renderer = nullptr;
    }
}

//设置渲染路径
void SVInst::setRenderPath(s32 _rpath) {
    if(!m_renderer){
        return;
    }
    //常见AR阶段
    if(m_global_mgr->m_arbg_mgr) {
        m_global_mgr->m_arbg_mgr->enable();
        m_global_mgr->m_arbg_mgr->setInputCameraTex("svres/sve.png");
    }
    //创建正常的阶段
    //创建一堆东西
    if(_rpath == 0) {
        //普通渲染
        
    }else if(_rpath == 1) {
        //
        
    }else if(_rpath == 2) {
        //
    }
}

//跑线程模型 就是引擎运行
void SVInst::start() {
    m_sv_st = SV_ST_RUN;
}

//引擎的线程模型，停止运行
//开启一个线程，销毁引擎，引擎销毁完毕以后，调用返回
void SVInst::stop() {
    m_sv_st = SV_ST_WAIT;
}

void SVInst::updateSVE(f32 _dt) {
    //处理一般逻辑，例如运动，消息处理等等
    //先跑脚本系统
    if(m_lua_sys) {
        m_lua_sys->update(_dt);
        //timeTag(false,"lua cost");
    }
    //事件处理系统更新
    if(m_event_sys) {
        m_event_sys->update(_dt);
    }
    //
    m_global_mgr->update(_dt);
}

void SVInst::renderSVE() {
    if(m_render_mgr ) {
        m_render_mgr->render();
    }
}

void SVInst::suspend(){
}

void SVInst::resume(){
}

void SVInst::clearCache(){
}

//
void SVInst::addRespath(cptr8 path) {
    if(!m_file_sys) {
         m_file_sys = MakeSharedPtr<SVFileMgr>(share());
    }
    m_file_sys->addRespath(path);
}

void SVInst::clearRespath() {
    if(m_file_sys) {
        m_file_sys->clearRespath();
        m_file_sys->addRespath("./");
    }
}

SVEventMgrPtr SVInst::getEventMgr(){
    return m_event_sys;
}

SVBasicSysPtr SVInst::getBasicSys(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pBasicSys;
}

SVCameraMgrPtr SVInst::getCameraMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_camera_mgr;
}

SVSceneMgrPtr SVInst::getSceneMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pSceneMgr;
}

SVLightSysPtr SVInst::getLightSys() {
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pLightSys;
}

SVModuleSysPtr SVInst::getModuleSys(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pModuleSys;
}

SVShaderMgrPtr SVInst::getShaderMgr(){
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_shader_mgr;
}

SVTexMgrPtr SVInst::getTexMgr(){
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_tex_mgr;
}

SVRTargetMgrPtr SVInst::getTargetMgr() {
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_target_mgr;
}

SVComDataPtr SVInst::getComData(){
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_common_data;
}

SVMtlLibPtr SVInst::getMtlLib() {
    return m_mtl_lib;
}

SVRenderMgrPtr SVInst::getRenderMgr(){
    return m_render_mgr;
}

SVDetectMgrPtr SVInst::getDetectMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_detect_mgr;
}

SVDeformMgrPtr SVInst::getDeformMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pDeformSys;
}

SVModelMgrPtr SVInst::getModelMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pModelMgr;
}

SVPhysicsWorldMgrPtr SVInst::getPhysicsWorldMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pPhysicSys;
}

SVRendererPtr SVInst::getRenderer() {
    return m_renderer;
}

//设置渲染器
void SVInst::_initRenderer(SVRendererPtr _renderer) {
    //设置渲染器
    m_renderer = _renderer;
    //发送一个系统级别的消息
    if(m_event_sys) {
        SVEvtRenderInitPtr _event = MakeSharedPtr<SVEvtRenderInit>(m_renderer);
        m_event_sys->pushEvent(_event);
    }
}
