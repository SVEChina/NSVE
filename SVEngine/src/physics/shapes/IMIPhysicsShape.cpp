//
// IMIPhysicsShape.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIPhysicsShape.h"

using namespace imi;

IMIPhysicsShape::IMIPhysicsShape(IMIInstPtr _app)
:IMIGBaseEx(_app) {
    m_type = E_PHYSICS_SHAPE_BASE;
    m_size=FVec3(0.0,0.0,0.0);
    m_mass=0.0;
    m_localInertia =FVec3(0.0,0.0,0.0);
    m_pColShape = nullptr;
}

IMIPhysicsShape::~IMIPhysicsShape() {
    
}

void IMIPhysicsShape::init(){
    
}

void IMIPhysicsShape::destroy(){
    if(m_pColShape){
        free(m_pColShape);
        m_pColShape = nullptr;
    }
}

void IMIPhysicsShape::update(f32 _dt){
    
}

btCollisionShape* IMIPhysicsShape::getShape(){
    return m_pColShape;
}

PHYSICSSHAPETYPE IMIPhysicsShape::getType() const{
    return m_type;
}
