//
// SVCameraMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVCameraMgr.h"
#include "../basesys/SVCameraNode.h"
#include "../work/SVTdCore.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRTarget.h"

using namespace sv;

SVCameraMgr::SVCameraMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 3;
    m_cameraLock = MakeSharedPtr<SVLock>();
}

SVCameraMgr::~SVCameraMgr() {
    m_cameraLock = nullptr;
}

void SVCameraMgr::init() {
    //主相机
    m_mainCamera = MakeSharedPtr<SVCameraNode>(mApp);
    m_mainCamera->init();
    m_mainCamera->setProject();
    //ui相机
    m_uiCamera = MakeSharedPtr<SVCameraNode>(mApp);
    m_uiCamera->init();
    m_uiCamera->setOrtho();
}

//
void SVCameraMgr::destroy() {
    if(m_mainCamera) {
        m_mainCamera->destroy();
        m_mainCamera = nullptr;
    }
    if(m_uiCamera) {
        m_uiCamera->destroy();
        m_uiCamera = nullptr;
    }    
}

//更新
void SVCameraMgr::update(f32 dt) {
     //主相机更新
    if(m_mainCamera){
        m_mainCamera->update(dt);
        SVRTargetPtr t_main_rt = mApp->getRenderMgr()->getMainRT();
        if( t_main_rt ) {
            t_main_rt->setVPMat(m_mainCamera->getVPMatObj());
        }
    }
    //更新ui相机
    if(m_uiCamera) {
        m_uiCamera->update(dt);
    }
}

SVCameraNodePtr SVCameraMgr::getMainCamera(){
    return m_mainCamera;
}

SVCameraNodePtr SVCameraMgr::getUICamera() {
    return m_uiCamera;
}

void SVCameraMgr::resize(f32 _w,f32 _h) {
    if(m_mainCamera){
        m_mainCamera->setSize(_w,_h);
    }
    if(m_uiCamera){
        m_uiCamera->setSize(_w,_h);
    }
}
