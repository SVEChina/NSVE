//
// IMIInst.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIInst.h"
#include "IMIGlobalMgr.h"
#include "IMIGlobalParam.h"
//
#include "../env/IMICtxBase.h"
#include "../env/IMICtxIOS.h"
#include "../env/IMICtxOSX.h"
#include "../env/IMIEGLContext.h"
//
#include "../script/IMILuaSys.h"

#include "../work/IMITdCore.h"
#include "../work/IMIThreadPool.h"

#include "../file/IMIFileMgr.h"

#include "../basesys/IMIBasicSys.h"
#include "../basesys/IMIConfig.h"
#include "../basesys/IMICameraMgr.h"
#include "../basesys/IMIARBackgroundMgr.h"
#include "../basesys/IMIComData.h"
#include "../basesys/IMIResMgr.h"
#include "../basesys/IMISceneMgr.h"

#include "../event/IMIEventMgr.h"
#include "../event/IMIEvent.h"

#include "../operate/IMIOpBase.h"
#include "../operate/IMIOpCreate.h"
#include "../operate/IMIOpThread.h"
//
#include "../detect/IMIDetectBase.h"
#include "../detect/IMIDetectMgr.h"
//
#include "../rendercore/IMIRTargetMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderPath.h"
#include "../rendercore/IMIGL/IMIRendererGL.h"

#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMIFilterLib.h"
#include "../mtl/IMIFilterBase.h"

using namespace imi;

static void lua_regist_IMIInst(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
       //lua_pushcfunction(L, &IMIInst::IMIInst);
       //lua_pushglobal(L, "IMIInst");
//       // 创建userdata要用的元表(其名为Foo), 起码要定义__gc方法, 以便回收内存
//       luaL_newmetatable(L, "IMIObject");
//       lua_pushstring(L, "__gc");
//       //lua_pushcfunction(L, &IMIObject::gc_obj);
//       lua_settable(L, -3);
    }
}

LUA_REG_IMP(IMIInst,lua_regist_IMIInst);

IMIInst::IMIInst() {
    m_sv_st = IMI_ST_NULL;
    m_async = false;
    m_ctx = nullptr;
    m_file_sys = nullptr;
    m_render_mgr = nullptr;
    m_render_path = nullptr;
    m_event_sys = nullptr;
    m_res_mgr = nullptr;
    m_ar_mgr = nullptr;
}

IMIInst::~IMIInst() {
    m_ctx = nullptr;
    m_file_sys = nullptr;
    m_mtl_lib = nullptr;
    m_render_mgr = nullptr;
    m_render_path = nullptr;
    m_event_sys = nullptr;
    m_res_mgr = nullptr;
    m_ar_mgr = nullptr;
}

IMIInstPtr IMIInst::makeCreate() {
    return MakeSharedPtr<IMIInst>();
}

IMIInstPtr IMIInst::share() {
    return std::dynamic_pointer_cast<IMIInst>(shareObject()) ;
}

//构建引擎的整个逻辑系统，唯独与渲染器无关
void IMIInst::init(bool async) {
    m_async = async;
    //
    m_renderer = nullptr;
    //lua脚本系统
    if(!m_lua_sys) {
        m_lua_sys = MakeSharedPtr<IMILuaSys>( share() );
        m_lua_sys->init();
        IMI_LOG_ERROR("sve init m_lua_sys end!\n");
    }
    //文件系统
    if(!m_file_sys) {
        m_file_sys = MakeSharedPtr<IMIFileMgr>( share() );
    }
    //加载配置
    m_config.init();
    m_config.loadConfig();
    //消息系统
    m_event_sys = MakeSharedPtr<IMIEventMgr>( share() );
    m_event_sys->init();
    //渲染管理
    m_render_mgr = MakeSharedPtr<IMIRenderMgr>( share() );
    m_render_mgr->init();
    //资源管理加载
    m_res_mgr = MakeSharedPtr<IMIResMgr>( share() );
    m_res_mgr->init();
    m_render_mgr->registRenderHelper(m_res_mgr);
    m_event_sys->listenSysEvent(m_res_mgr,IMIResMgr::procSysEvent);
    //创建渲染路径
    m_render_path = MakeSharedPtr<IMIRenderPath>( share() );
    m_event_sys->listenSysEvent(m_render_path,IMIRenderPath::procSysEvent);
    //材质库
    m_mtl_lib = MakeSharedPtr<IMIMtlLib>( share() );
    m_mtl_lib->init();
    m_event_sys->listenSysEvent(m_mtl_lib,IMIMtlLib::procSysEvent);
    //AR背景，AR引擎特有的系统
    m_ar_mgr = MakeSharedPtr<IMIARBackgroundMgr>( share() );
    m_ar_mgr->init();
    //全局
    m_global_mgr = MakeSharedPtr<IMIGlobalMgr>( share() );
    m_global_mgr->init();
    //
    if(async) {
        //异步 需要自己开一个线程，同步，不需要
    }
    m_sv_st = IMI_ST_WAIT;
}

void IMIInst::destroy() {
    m_global_mgr = nullptr;
    //AR 背景
    if(m_ar_mgr) {
        m_ar_mgr->destroy();
        m_ar_mgr = nullptr;
    }
    //
    if(m_render_mgr) {
        m_render_mgr->destroy();
        m_render_mgr = nullptr;
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
        m_event_sys = nullptr;
    }
    //
    if(m_ctx) {
        m_ctx = nullptr;
    }
    m_sv_st = IMI_ST_NULL;
}

void IMIInst::resize(s32 _w,s32 _h) {
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
IMICtxBasePtr IMIInst::createEnv(IMI_R_ENV _type) {
    IMICtxBasePtr t_ctx = nullptr;
#ifdef IMI_ANDROID
    if(_type == E_R_GLES_ANDORID) {
        m_rcore = E_R_GLES_ANDORID;
        return m_ctx;
    }
    if(_type == E_R_VULKAN_ANDORID) {
        m_rcore = E_R_VULKAN_ANDORID;
        return m_ctx;
    }
#endif
    
#ifdef IMI_OSX
    if(_type == E_R_METAL_OSX) {
        m_rcore = E_R_METAL_OSX;
        m_ctx = MakeSharedPtr<IMICtxOSXMetal>( share() );
        return m_ctx;
    }
    if(_type == E_R_GL_OSX) {
        m_rcore = E_R_GL_OSX;
        m_ctx = MakeSharedPtr<IMICtxOSXGL>( share() );
        return m_ctx;
    }
#endif
        
#ifdef IMI_IOS
    if(_type == E_R_METAL_IOS) {
        m_rcore = E_R_METAL_IOS;
        m_ctx = MakeSharedPtr<IMICtxIOSMetal>( share() );
        return m_ctx;
    }
    if(_type == E_R_GLES_IOS) {
        m_rcore = E_R_GLES_IOS;
        m_ctx = MakeSharedPtr<IMICtxIOSGLES>( share() );
        return m_ctx;
    }
#endif
    return nullptr;
}

//销毁渲染环境，包括渲染器
void IMIInst::destroyEnv() {
//    if(m_renderer){
//        m_renderer->destroy();
//        m_renderer = nullptr;
//    }
    if(m_ctx) {
        m_ctx->destroy();
    }
}

//设置渲染路径
void IMIInst::setRenderPath(s32 _rpath) {
    if(!m_renderer){
        return;
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
void IMIInst::start() {
    m_sv_st = IMI_ST_RUN;
}

//引擎的线程模型，停止运行
//开启一个线程，销毁引擎，引擎销毁完毕以后，调用返回
void IMIInst::stop() {
    m_sv_st = IMI_ST_WAIT;
}

void IMIInst::updateIMI(f32 _dt) {
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
    //
    if(m_ar_mgr) {
        m_ar_mgr->update(_dt);  //AR背景
    }
}

void IMIInst::renderIMI() {
    if(m_render_mgr ) {
        m_render_mgr->render();
    }
}

void IMIInst::suspend(){
}

void IMIInst::resume(){
}

void IMIInst::clearCache(){
}

void IMIInst::addRespath(cptr8 path) {
    if(!m_file_sys) {
         m_file_sys = MakeSharedPtr<IMIFileMgr>(share());
    }
    m_file_sys->addRespath(path);
}

void IMIInst::clearRespath() {
    if(m_file_sys) {
        m_file_sys->clearRespath();
        m_file_sys->addRespath("./");
    }
}

void IMIInst::inputFrame(u8 *_frameData, s32 _width, s32 _height){
    //先只支持RGBA
    if(m_ar_mgr) {
        m_ar_mgr->enable(_width, _height);
        IMIDataSwapPtr frameData = MakeSharedPtr<IMIDataSwap>();
        frameData->writeData(_frameData, _width*_height*4);
        m_ar_mgr->setInputCameraTex(frameData, IMI_PF_BGRA);
    }
}

void IMIInst::inputKeyData(u8 *_keyData){
    if (_keyData && getDetectMgr()) {
        IMIDetectBasePtr t_detect = getDetectMgr()->getDetect();
        if( t_detect ) {
            t_detect->pushData(_keyData);
        }
    }
}

#include "../file/IMILoaderGLTFEx.h"
#include "../node/IMISkinNode.h"

void IMIInst::test() {
    if(getSceneMgr()) {
        getSceneMgr()->test();
    }
//    IMISkinNodePtr skinNode = MakeSharedPtr<IMISkinNode>(share());
//    IMILoaderGLTFEx::loadFromFile(share(),"res/woniu_xiuxian/scene.gltf", skinNode)
//    IMICubePtr t_box_node = MakeSharedPtr<IMICube>(mApp);
//    t_box_node->setRotation(45.0f, 45.0f, 45.0f);
//    t_box_node->setMtl("normal3d");
//    IMISurfacePtr t_surface = t_box_node->getSurface();
//    if(t_surface) {
//        t_surface->setTexture(1, 0, t_tex);
//    }
    
    //常见AR阶段
//    if(m_ar_mgr) {
//        m_ar_mgr->enable();
//        m_ar_mgr->setInputCameraTex("res/bg2.png");
//    }
    
//    //滤镜设置例子
//    IMIFilterBasePtr t_filter = IMIFilterLib::openFilter(share(),FILTER_LUT);
//    if(t_filter) {
//        IMISurfacePtr t_surface = t_filter->getSurface();
//        if(t_surface) {
//            IMITexturePtr _tex_img = getTexMgr()->getTexture("res/filterimg/sunset_20170620.png");
//            t_surface->setTexture(1, 1, _tex_img);
//        }
//    }
//    IMIFilterLib::openFilter( share() ,FILTER_HDR);
    //
}

IMIEventMgrPtr IMIInst::getEventMgr(){
    return m_event_sys;
}

IMIBasicSysPtr IMIInst::getBasicSys(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pBasicSys;
}

IMICameraMgrPtr IMIInst::getCameraMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_camera_mgr;
}

IMISceneMgrPtr IMIInst::getSceneMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_scene_mgr;
}

IMIAniMgrPtr IMIInst::getAniMgr() {
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_ani_mgr;
}

IMILightSysPtr IMIInst::getLightSys() {
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pLightSys;
}

IMIModuleSysPtr IMIInst::getModuleSys(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pModuleSys;
}

IMIShaderMgrPtr IMIInst::getShaderMgr(){
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_shader_mgr;
}

IMITexMgrPtr IMIInst::getTexMgr(){
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_tex_mgr;
}

IMIRTargetMgrPtr IMIInst::getTargetMgr() {
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_target_mgr;
}

IMIComDataPtr IMIInst::getComData(){
    if(!m_res_mgr)
        return nullptr;
    return m_res_mgr->m_common_data;
}

IMIMtlLibPtr IMIInst::getMtlLib() {
    return m_mtl_lib;
}

IMIRenderMgrPtr IMIInst::getRenderMgr(){
    return m_render_mgr;
}

IMIRenderPathPtr IMIInst::getRenderPath(){
    return m_render_path;
}

IMIDetectMgrPtr IMIInst::getDetectMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_detect_mgr;
}

IMIDeformMgrPtr IMIInst::getDeformMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pDeformSys;
}

IMIModelMgrPtr IMIInst::getModelMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pModelMgr;
}

IMIPhysicsWorldMgrPtr IMIInst::getPhysicsWorldMgr(){
    if(!m_global_mgr)
        return nullptr;
    return m_global_mgr->m_pPhysicSys;
}

IMIRendererPtr IMIInst::getRenderer() {
    return m_renderer;
}

IMIARBackgroundMgrPtr IMIInst::getARBGMgr() {
    return m_ar_mgr;
}

//设置渲染器
void IMIInst::_initRenderer(IMIRendererPtr _renderer) {
    //设置渲染器
    m_renderer = _renderer;
    //发送一个系统级别的消息
    if(m_event_sys) {
        IMIvtRenderInitPtr _event = MakeSharedPtr<IMIvtRenderInit>(m_renderer);
        m_event_sys->pushEvent(_event,true);
        m_event_sys->update(0.03f);
    }
}
