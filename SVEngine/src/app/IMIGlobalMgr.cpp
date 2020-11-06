//
// IMIGlobalMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIGlobalMgr.h"
#include "IMIInst.h"
#include "../basesys/IMIBasicSys.h"
#include "../basesys/IMIFontProcess.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMICameraMgr.h"
#include "../basesys/IMIDeformMgr.h"
#include "../basesys/IMIModelMgr.h"
#include "../basesys/IMIPhysicsWorldMgr.h"
#include "../basesys/IMIAniMgr.h"

#include "../module/IMIModuleSys.h"
#include "../basesys/IMILightSys.h"
#include "../event/IMIEventMgr.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMIShaderMgr.h"
#include "../mtl/IMIMtlLib.h"
#include "../detect/IMIDetectMgr.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../base/imistr.h"

#include <sys/time.h>

//#include <Python/Python.h>

using namespace imi;

IMIGlobalMgr::IMIGlobalMgr(IMIInstPtr _app)
:IMIGBaseEx(_app) {
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

IMIGlobalMgr::~IMIGlobalMgr() {
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

void IMIGlobalMgr::init() {
    //相机系统
    m_camera_mgr = MakeSharedPtr<IMICameraMgr>(mApp);
    m_camera_mgr->init();
    //场景系统
    m_scene_mgr = MakeSharedPtr<IMISceneMgr>(mApp);
    m_scene_mgr->init();
    IMI_LOG_ERROR("sve init IMISceneMgr end!\n");
    m_detect_mgr = MakeSharedPtr<IMIDetectMgr>(mApp);
    m_detect_mgr->init(DETECT_T_ST);
    //动画系统
    m_ani_mgr = MakeSharedPtr<IMIAniMgr>(mApp);
    m_ani_mgr->init();
}

void IMIGlobalMgr::destroy() {
    //相机析构
    if (m_camera_mgr) {
        //要先析构相机上的节点，才能析构场景
        m_camera_mgr->destroy();
        IMI_LOG_ERROR("IMICameraMgr:destroy sucess");
    }
    //场景析构
    if (m_scene_mgr) {
        //场景析够(场景虽然也是节点 但是需要单独管理,因为节点需要挂在场景上,所以在节点没析够前,场景不能析构掉)
        m_scene_mgr->destroy();
        IMI_LOG_ERROR("IMISceneMgr:destroy sucess");
    }
    if (m_detect_mgr) {
        m_detect_mgr->destroy();
        IMI_LOG_ERROR("IMIDetectMgr:destroy sucess");
    }
    //ANI
    if(m_ani_mgr) {
        m_ani_mgr->destroy();
        IMI_LOG_ERROR("IMIAniMgr:destroy sucess");
    }
}

void IMIGlobalMgr::update(f32 dt) {
    if(m_ani_mgr) {
        m_ani_mgr->update(dt);
        timeTag(false,"ani cost");
    }
    if(m_camera_mgr) {
        //相机更新
        m_camera_mgr->update(dt);
        timeTag(false,"camera cost");
    }
    if(m_scene_mgr) {
        //场景更新(节点系统)
        m_scene_mgr->update(dt);
        timeTag(false,"scene cost");
    }
    if (m_detect_mgr) {
        m_detect_mgr->update(dt);
        timeTag(false,"detect cost");
    }
}

void IMIGlobalMgr::timeTag(bool _clear,cptr8 _tag){
    if(_clear){
        gettimeofday(&timTagLast, nullptr);
        IMI_LOG_INFO("timeTag reset %s \n",_tag);
    }else{
        timeval timTagCur;
        gettimeofday(&timTagCur, nullptr);
        s32 dt = s32((timTagCur.tv_sec - timTagLast.tv_sec) * 1000.0f + (timTagCur.tv_usec - timTagLast.tv_usec) * 0.001f);
        timTagLast = timTagCur;
        IMI_LOG_INFO("timeTag %d %s\n",dt,_tag);
    }
}
