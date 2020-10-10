//
// SVGlobalMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVGlobalMgr.h"
#include "SVInst.h"
#include "../basesys/SVBasicSys.h"
#include "../basesys/SVFontProcess.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVCameraMgr.h"
#include "../basesys/SVComData.h"
#include "../basesys/SVDeformMgr.h"
#include "../basesys/SVModelMgr.h"
#include "../basesys/SVPhysicsWorldMgr.h"
#include "../basesys/SVARBackgroundMgr.h"
#include "../module/SVModuleSys.h"
#include "../basesys/SVLightSys.h"
#include "../event/SVEventMgr.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVShaderMgr.h"
#include "../mtl/SVMtlLib.h"
#include "../detect/SVDetectMgr.h"
#include "../rendercore/SVRenderMgr.h"
#include "../base/svstr.h"

#include <sys/time.h>

//#include <Python/Python.h>

using namespace sv;

SVGlobalMgr::SVGlobalMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    //引擎系统和操作指令系统要先建立起来
    m_event_sys = nullptr;
    m_pBasicSys = nullptr;
    m_pSceneMgr = nullptr;
    m_camera_mgr = nullptr;
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
    m_detect_mgr = nullptr;
    m_common_data = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
    m_arbg_mgr = nullptr;
}

SVGlobalMgr::~SVGlobalMgr() {
    m_event_sys = nullptr;
    m_pBasicSys = nullptr;
    m_pSceneMgr = nullptr;
    m_camera_mgr = nullptr;
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
    m_detect_mgr = nullptr;
    m_common_data = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
    m_arbg_mgr = nullptr;
}

void SVGlobalMgr::init() {
    //消息系统建立起来
    m_event_sys = MakeSharedPtr<SVEventMgr>(mApp);
    m_event_sys->init();
    SV_LOG_ERROR("sve init m_event_sys end!\n");
    //构建静态数据
    m_common_data = MakeSharedPtr<SVComData>(mApp);
    m_common_data->init();
    SV_LOG_ERROR("sve init m_common_data end!\n");
    //AR背景，AR引擎特有的系统
    m_arbg_mgr = MakeSharedPtr<SVARBackgroundMgr>(mApp);
    m_arbg_mgr->init();
    SV_LOG_ERROR("sve init m_arbg_mgr end!\n");
//    //基础系统
//    m_pBasicSys = MakeSharedPtr<SVBasicSys>(mApp));
//    m_pBasicSys->init();
    //相机系统
    m_camera_mgr = MakeSharedPtr<SVCameraMgr>(mApp);
    m_camera_mgr->init();
//    //灯光系统
//    m_pLightSys = MakeSharedPtr<SVLightSys>(mApp);
//    m_pLightSys->init();
//    //组件系统
//    m_pModuleSys = MakeSharedPtr<SVModuleSys>(mApp));
//    m_pModuleSys->init();
    //纹理管理器初始化
    m_tex_mgr = MakeSharedPtr<SVTexMgr>(mApp);
    m_tex_mgr->init();
    SV_LOG_ERROR("sve init m_tex_mgr end!\n");
    //shader程序初始化
    m_shader_mgr = MakeSharedPtr<SVShaderMgr>(mApp);
    m_shader_mgr->init();
    SV_LOG_ERROR("sve init m_shader_mgr end!\n");
    //场景系统
    m_pSceneMgr = MakeSharedPtr<SVSceneMgr>(mApp);
    m_pSceneMgr->init();
    SV_LOG_ERROR("sve init SVSceneMgr end!\n");
//    //模型管理部分
//    m_pModelMgr = MakeSharedPtr<SVModelMgr>(mApp.get());
//    m_pModelMgr->init();

//    //创建识别对象成功
//    m_detect_mgr = MakeSharedPtr<SVDetectMgr>(mApp.get());
//    m_detect_mgr->init(DETECT_T_ST);
//    //变形系统
//    m_pDeformSys = MakeSharedPtr<SVDeformMgr>(mApp.get());
//    m_pDeformSys->init();
//    //
//    m_pPhysicSys = MakeSharedPtr<SVPhysicsWorldMgr>(mApp.get());
//    m_pPhysicSys->init();
//    //加载默认字体
//    m_pBasicSys->loadDefaultFMFont();
}

void SVGlobalMgr::destroy() {
//    if (m_detect_mgr) {
//        //识别模块
//        m_detect_mgr->destroy();
//        SV_LOG_ERROR("SVDetectMgr:destroy sucess");
//    }
    //相机析构
    if (m_camera_mgr) {
        //要先析构相机上的节点，才能析构场景
        m_camera_mgr->destroy();
        SV_LOG_ERROR("SVCameraMgr:destroy sucess");
    }
    //场景析构
    if (m_pSceneMgr) {
        //场景析够(场景虽然也是节点 但是需要单独管理,因为节点需要挂在场景上,所以在节点没析够前,场景不能析构掉)
        m_pSceneMgr->destroy();
        SV_LOG_ERROR("SVSceneMgr:destroy sucess");
    }
    //AR 背景
    if(m_arbg_mgr) {
        m_arbg_mgr->destroy();
        SV_LOG_ERROR("SVARBackgroundMgr:destroy sucess");
    }
    //纹理析够 析构都要用到渲染模块
    if (m_tex_mgr) {
        m_tex_mgr->destroy();
        SV_LOG_ERROR("SVTexMgr:destroy sucess");
    }
    //shader析构
    if (m_shader_mgr) {
        m_shader_mgr->destroy();
        SV_LOG_ERROR("SVShaderMgr:destroy sucess");
    }
//    //模型析构
//    if (m_pModelMgr) {
//        m_pModelMgr->destroy();
//        SV_LOG_ERROR("SVModelMgr:destroy sucess");
//    }
//    //组件系统析构
//    if(m_pModuleSys) {
//        m_pModuleSys->destroy();
//        SV_LOG_ERROR("m_pModuleSys:destroy sucess");
//    }
//    if(m_pBasicSys){
//        //基础系统
//        m_pBasicSys->destroy();
//        SV_LOG_ERROR("SVBasicSys:destroy sucess");
//    }
//    if(m_pDeformSys){
//        //
//        m_pDeformSys->destroy();
//        SV_LOG_ERROR("m_pDeformSys:destroy sucess");
//    }
//    if(m_pPhysicSys){
//        //物理销毁
//        m_pPhysicSys->destroy();
//        SV_LOG_ERROR("m_pPhysics:destroy sucess");
//    }
//    
//    if(m_pLightSys) {
//        //灯光销毁
//        m_pLightSys->destroy();
//        SV_LOG_ERROR("m_pLightSys:destroy sucess");
//    }
    if (m_event_sys) {
        //事件系统最后析够,因为很多其他模块 会注册监听事件
        m_event_sys->destroy();
        SV_LOG_ERROR("SVEventMgr:destroy sucess");
    }
}

void SVGlobalMgr::update(f32 dt) {
//    //
//    m_detect_mgr->update(dt);           //识别数据新更新
//    timeTag(false,"detect cost");
//    //
//    m_pModuleSys->update(dt);           //组件系统更新
//    timeTag(false,"module cost");
//    m_pBasicSys->update(dt);            //基础系统更新
//    timeTag(false,"basesys cost");
//    m_event_sys->update(dt);            //事件处理系统更新
//    timeTag(false,"event cost");
//    m_pModelMgr->update(dt);            //模型管理
//    timeTag(false,"model cost");
//    m_pPhysicSys->update(dt);             //物理更新
//    timeTag(false,"physics cost");
    if(m_camera_mgr) {
        //相机更新
        m_camera_mgr->update(dt);
        timeTag(false,"camera cost");
    }
    if(m_pSceneMgr) {
        //场景更新(节点系统)
        m_pSceneMgr->update(dt);
        timeTag(false,"scene cost");
    }
//    m_pLightSys->update(dt);            //灯光系统更新
//    timeTag(false,"light cost");
    if(m_arbg_mgr) {
        //AR背景
        m_arbg_mgr->update(dt);
        timeTag(false,"arbg cost");
    }
//    m_pDeformSys->update(dt);           //变形更新
//    timeTag(false,"deform cost");
//    m_tex_mgr->update(dt);              //删除不用的纹理
//    timeTag(false,"texmgr cost");
}

void SVGlobalMgr::timeTag(bool _clear,cptr8 _tag){
    if(_clear){
        gettimeofday(&timTagLast, nullptr);
        SV_LOG_INFO("timeTag reset %s \n",_tag);
    }else{
        timeval timTagCur;
        gettimeofday(&timTagCur, nullptr);
        s32 dt = s32((timTagCur.tv_sec - timTagLast.tv_sec) * 1000.0f + (timTagCur.tv_usec - timTagLast.tv_usec) * 0.001f);
        timTagLast = timTagCur;
        SV_LOG_INFO("timeTag %d %s\n",dt,_tag);
    }
}
