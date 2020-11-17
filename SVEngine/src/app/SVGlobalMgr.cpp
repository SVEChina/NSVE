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
#include "../basesys/SVDeformMgr.h"
#include "../basesys/SVModelMgr.h"
#include "../basesys/SVPhysicsWorldMgr.h"
#include "../basesys/SVAniMgr.h"

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
    m_pBasicSys = nullptr;
    m_scene_mgr = nullptr;
    m_camera_mgr = nullptr;
    m_detect_mgr = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
}

SVGlobalMgr::~SVGlobalMgr() {
    m_pBasicSys = nullptr;
    m_scene_mgr = nullptr;
    m_camera_mgr = nullptr;
    m_detect_mgr = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
    m_ani_mgr = nullptr;
}

void SVGlobalMgr::init() {
    //相机系统
    m_camera_mgr = MakeSharedPtr<SVCameraMgr>(mApp);
    m_camera_mgr->init();
    //场景系统
    m_scene_mgr = MakeSharedPtr<SVSceneMgr>(mApp);
    m_scene_mgr->init();
    SV_LOG_ERROR("sve init SVSceneMgr end!\n");
    m_detect_mgr = MakeSharedPtr<SVDetectMgr>(mApp);
    m_detect_mgr->init(DETECT_T_ST);
    //动画系统
    m_ani_mgr = MakeSharedPtr<SVAniMgr>(mApp);
    m_ani_mgr->init();
}

void SVGlobalMgr::destroy() {
    //相机析构
    if (m_camera_mgr) {
        //要先析构相机上的节点，才能析构场景
        m_camera_mgr->destroy();
        SV_LOG_ERROR("SVCameraMgr:destroy sucess");
    }
    //场景析构
    if (m_scene_mgr) {
        //场景析够(场景虽然也是节点 但是需要单独管理,因为节点需要挂在场景上,所以在节点没析够前,场景不能析构掉)
        m_scene_mgr->destroy();
        SV_LOG_ERROR("SVSceneMgr:destroy sucess");
    }
    if (m_detect_mgr) {
        m_detect_mgr->destroy();
        SV_LOG_ERROR("SVDetectMgr:destroy sucess");
    }
    //ANI
    if(m_ani_mgr) {
        m_ani_mgr->destroy();
        SV_LOG_ERROR("SVAniMgr:destroy sucess");
    }
}

void SVGlobalMgr::update(f32 dt) {
    if(m_ani_mgr) {
        m_ani_mgr->update(dt);
//        timeTag(false,"ani cost");
    }
    if(m_camera_mgr) {
        //相机更新
        m_camera_mgr->update(dt);
//        timeTag(false,"camera cost");
    }
    if(m_scene_mgr) {
        //场景更新(节点系统)
        m_scene_mgr->update(dt);
//        timeTag(false,"scene cost");
    }
    if (m_detect_mgr) {
        m_detect_mgr->update(dt);
//        timeTag(false,"detect cost");
    }
}

void SVGlobalMgr::timeTag(bool _clear,cptr8 _tag){
    if(_clear){
        gettimeofday(&timTagLast, nullptr);
//        SV_LOG_INFO("timeTag reset %s \n",_tag);
    }else{
        timeval timTagCur;
        gettimeofday(&timTagCur, nullptr);
        s32 dt = s32((timTagCur.tv_sec - timTagLast.tv_sec) * 1000.0f + (timTagCur.tv_usec - timTagLast.tv_usec) * 0.001f);
        timTagLast = timTagCur;
//        SV_LOG_INFO("timeTag %d %s\n",dt,_tag);
    }
}
