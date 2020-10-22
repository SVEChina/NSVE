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
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTarget.h"

using namespace sv;

SVCameraMgr::SVCameraMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 3;
    m_lock = MakeSharedPtr<SVLockSpin>();
    m_camera_pool.clear();
}

SVCameraMgr::~SVCameraMgr() {
    m_camera_pool.clear();
    m_lock = nullptr;
}

void SVCameraMgr::init() {
    m_main_camera = MakeSharedPtr<SVCameraNode>(mApp);
    m_main_camera->init();
    m_main_camera->setProject();
    m_main_camera->active();
}

void SVCameraMgr::destroy() {
    if(m_main_camera) {
        m_main_camera->destroy();
        m_main_camera = nullptr;
    }
}

void SVCameraMgr::update(f32 _dt) {
    //主相机更新
    if(m_main_camera){
        m_main_camera->update(_dt);
    }
    //其他相机更新
    CAMERAPOOL::iterator it = m_camera_pool.begin();
    while (it!=m_camera_pool.end()) {
        it->second->update(_dt);
        it++;
    }
}

SVCameraNodePtr SVCameraMgr::createCamera(s32 _cameraID) {
    CAMERAPOOL::iterator it = m_camera_pool.find(_cameraID);
    if(it == m_camera_pool.end()) {
        SVCameraNodePtr t_camera = MakeSharedPtr<SVCameraNode>(mApp);
        t_camera->init();
        m_camera_pool.insert(std::make_pair(_cameraID, t_camera));
        return t_camera;
    }
    return it->second;
}

void SVCameraMgr::destroyCamera(s32 _cameraID) {
    CAMERAPOOL::iterator it = m_camera_pool.find(_cameraID);
    if(it != m_camera_pool.end()) {
        SVCameraNodePtr t_camera = it->second;
        m_camera_pool.erase(it);
    }
}

SVCameraNodePtr SVCameraMgr::getCamera(s32 _cameraID) {
    CAMERAPOOL::iterator it = m_camera_pool.find(_cameraID);
    if(it != m_camera_pool.end()) {
        return it->second;
    }
    return nullptr;
}

//设置相机绑定
void SVCameraMgr::bindCamera(SV_TEXIN _targetID,s32 _cameraID) {
    if(mApp->getRenderer()) {
        SVRTargetPtr t_target = mApp->getRenderer()->getTarget(_targetID);
        SVCameraNodePtr t_camera = getCamera(_cameraID);
        if(t_target && t_camera) {
            t_target->bindCamera(t_camera);
        }
    }
}

//解开相机绑定
void SVCameraMgr::unbindCamera(SV_TEXIN _targetID) {
    if(mApp->getRenderer()) {
        SVRTargetPtr t_target = mApp->getRenderer()->getTarget(_targetID);
        if(t_target) {
            t_target->bindCamera(nullptr);
        }
    }
}

SVCameraNodePtr SVCameraMgr::getMainCamera(){
    return m_main_camera;
}

void SVCameraMgr::resize(f32 _w,f32 _h) {
    if(m_main_camera){
        m_main_camera->setSize(_w,_h);
    }
}
