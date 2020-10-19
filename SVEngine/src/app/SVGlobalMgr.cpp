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
#include "../basesys/SVARBackgroundMgr.h"
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
    m_pSceneMgr = nullptr;
    m_camera_mgr = nullptr;
    m_detect_mgr = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
    m_ar_mgr = nullptr;
}

SVGlobalMgr::~SVGlobalMgr() {
    m_pBasicSys = nullptr;
    m_pSceneMgr = nullptr;
    m_camera_mgr = nullptr;
    m_detect_mgr = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
    m_ar_mgr = nullptr;
    m_ani_mgr = nullptr;
}

void SVGlobalMgr::init() {
    //AR背景，AR引擎特有的系统
    m_ar_mgr = MakeSharedPtr<SVARBackgroundMgr>(mApp);
    m_ar_mgr->init();
    SV_LOG_ERROR("sve init m_ar_mgr end!\n");
    //相机系统
    m_camera_mgr = MakeSharedPtr<SVCameraMgr>(mApp);
    m_camera_mgr->init();
    //场景系统
    m_pSceneMgr = MakeSharedPtr<SVSceneMgr>(mApp);
    m_pSceneMgr->init();
    SV_LOG_ERROR("sve init SVSceneMgr end!\n");
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
    if (m_pSceneMgr) {
        //场景析够(场景虽然也是节点 但是需要单独管理,因为节点需要挂在场景上,所以在节点没析够前,场景不能析构掉)
        m_pSceneMgr->destroy();
        SV_LOG_ERROR("SVSceneMgr:destroy sucess");
    }
    //AR 背景
    if(m_ar_mgr) {
        m_ar_mgr->destroy();
        SV_LOG_ERROR("SVARBackgroundMgr:destroy sucess");
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
        timeTag(false,"ani cost");
    }
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
    if(m_ar_mgr) {
        //AR背景
        m_ar_mgr->update(dt);
        timeTag(false,"arbg cost");
    }
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
