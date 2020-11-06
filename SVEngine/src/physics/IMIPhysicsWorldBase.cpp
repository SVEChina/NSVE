//
// IMIPhysicsWorldBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIPhysicsWorldBase.h"

using namespace imi;

IMIPhysicsWorldBase::IMIPhysicsWorldBase(IMIInstPtr _app):IMIGBaseEx(_app) {
    m_type = E_PHYSICS_WORLD_BASE;
    m_lock= MakeSharedPtr<IMILock>();
}

IMIPhysicsWorldBase::~IMIPhysicsWorldBase() {
    m_lock = nullptr;
}

void IMIPhysicsWorldBase::init(){
    
}

void IMIPhysicsWorldBase::destroy(){
    
}

void IMIPhysicsWorldBase::update(f32 _dt){
    
}

const IMI_PHYSICSWORLDTYPE IMIPhysicsWorldBase::getType() const{
    return m_type;
}

void IMIPhysicsWorldBase::setGravity(const FVec3 &_gravity){
    m_gravity = _gravity;
}

const FVec3& IMIPhysicsWorldBase::getGravity() const{
    return m_gravity;
}
