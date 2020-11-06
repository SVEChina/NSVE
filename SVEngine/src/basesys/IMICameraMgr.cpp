//
// IMICameraMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMICameraMgr.h"
#include "../basesys/IMICameraNode.h"
#include "../work/IMITdCore.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRTarget.h"

using namespace imi;

IMICameraMgr::IMICameraMgr(IMIInstPtr _app)
:IMISysBase(_app) {
    m_subsysType = 3;
    m_lock = MakeSharedPtr<IMILockSpin>();
    m_camera_pool.clear();
}

IMICameraMgr::~IMICameraMgr() {
    m_camera_pool.clear();
    m_lock = nullptr;
}

void IMICameraMgr::init() {
    m_main_camera = MakeSharedPtr<IMICameraNode>(mApp);
    m_main_camera->init();
    m_main_camera->setProject();
    m_main_camera->active();
}

void IMICameraMgr::destroy() {
    if(m_main_camera) {
        m_main_camera->destroy();
        m_main_camera = nullptr;
    }
}

void IMICameraMgr::update(f32 _dt) {
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

IMICameraNodePtr IMICameraMgr::createCamera(s32 _cameraID) {
    CAMERAPOOL::iterator it = m_camera_pool.find(_cameraID);
    if(it == m_camera_pool.end()) {
        IMICameraNodePtr t_camera = MakeSharedPtr<IMICameraNode>(mApp);
        t_camera->init();
        m_camera_pool.insert(std::make_pair(_cameraID, t_camera));
        return t_camera;
    }
    return it->second;
}

void IMICameraMgr::destroyCamera(s32 _cameraID) {
    CAMERAPOOL::iterator it = m_camera_pool.find(_cameraID);
    if(it != m_camera_pool.end()) {
        IMICameraNodePtr t_camera = it->second;
        m_camera_pool.erase(it);
    }
}

IMICameraNodePtr IMICameraMgr::getCamera(s32 _cameraID) {
    CAMERAPOOL::iterator it = m_camera_pool.find(_cameraID);
    if(it != m_camera_pool.end()) {
        return it->second;
    }
    return nullptr;
}

//设置相机绑定
void IMICameraMgr::bindCamera(IMI_TEXIN _targetID,s32 _cameraID) {
    if(mApp->getRenderer()) {
        IMIRTargetPtr t_target = mApp->getRenderer()->getTarget(_targetID);
        IMICameraNodePtr t_camera = getCamera(_cameraID);
        if(t_target && t_camera) {
            t_target->bindCamera(t_camera);
        }
    }
}

//解开相机绑定
void IMICameraMgr::unbindCamera(IMI_TEXIN _targetID) {
    if(mApp->getRenderer()) {
        IMIRTargetPtr t_target = mApp->getRenderer()->getTarget(_targetID);
        if(t_target) {
            t_target->bindCamera(nullptr);
        }
    }
}

IMICameraNodePtr IMICameraMgr::getMainCamera(){
    return m_main_camera;
}

void IMICameraMgr::resize(f32 _w,f32 _h) {
    if(m_main_camera){
        m_main_camera->setSize(_w,_h);
    }
}
