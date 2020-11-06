//
// IMIPhysicsWorldMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIPhysicsWorldMgr.h"
#include "../physics/IMIPhysicsWorldBase.h"
#include "../physics/IMIPhysicsSoftRigidWorld.h"
#include "../physics/IMIPhysicsWorld.h"

using namespace imi;

IMIPhysicsWorldMgr::IMIPhysicsWorldMgr(IMIInstPtr _app)
:IMISysBase(_app) {
    m_subsysType = 4;
    m_rigidWorld = nullptr;
    m_softWorld = nullptr;
}

IMIPhysicsWorldMgr::~IMIPhysicsWorldMgr() {
    m_rigidWorld = nullptr;
    m_softWorld = nullptr;
}

void IMIPhysicsWorldMgr::init() {
    m_rigidWorld = MakeSharedPtr<IMIPhysicsWorld>(mApp);
    m_rigidWorld->init();
    m_softWorld = MakeSharedPtr<IMIPhysicsSoftRigidWorld>(mApp);
    m_softWorld->init();
}

void IMIPhysicsWorldMgr::destroy() {
    if (m_rigidWorld) {
        m_rigidWorld->destroy();
    }
    if (m_softWorld) {
        m_softWorld->destroy();
    }
}

void IMIPhysicsWorldMgr::update(f32 _dt) {
    if (m_rigidWorld) {
        m_rigidWorld->update(_dt);
    }
    if (m_softWorld) {
        m_softWorld->update(_dt);
    }
}

void IMIPhysicsWorldMgr::setRigidWorld(IMIPhysicsWorldPtr _world){
    if (_world) {
        m_rigidWorld = _world;
    }
}

void IMIPhysicsWorldMgr::setSoftWorld(IMIPhysicsSoftRigidWorldPtr _world){
    if (_world) {
        m_softWorld = _world;
    }
}

IMIPhysicsWorldPtr IMIPhysicsWorldMgr::getRigidWorld(){
    return m_rigidWorld;
}

IMIPhysicsSoftRigidWorldPtr IMIPhysicsWorldMgr::getSoftWorld(){
    return m_softWorld;
}
