//
// IMIPhysicsShapeBox.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIPhysicsShapeBox.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"

using namespace imi;

IMIPhysicsShapeBox::IMIPhysicsShapeBox(IMIInstPtr _app)
:IMIPhysicsShape(_app) {
    m_type = E_PHYSICS_SHAPE_BOX;
    setSize(FVec3_zero);
}

IMIPhysicsShapeBox::IMIPhysicsShapeBox(IMIInstPtr _app, FVec3 _size):IMIPhysicsShape(_app) {
    m_type = E_PHYSICS_SHAPE_BOX;
    setSize(_size);
}

IMIPhysicsShapeBox::~IMIPhysicsShapeBox() {
    
}

void IMIPhysicsShapeBox::init(){
    m_pColShape = new btBoxShape(btVector3(m_size.x,m_size.y,m_size.z));
    // 刚体是动态的如果且仅当质量为非零时，否则是静止的
    bool t_isDynamic = (m_mass != 0.f);
    btVector3 t_localInertia(m_localInertia.x,m_localInertia.y,m_localInertia.z);
    if (t_isDynamic){
        m_pColShape->calculateLocalInertia(m_mass,t_localInertia);
    }
}

void IMIPhysicsShapeBox::destroy(){
    
}

void IMIPhysicsShapeBox::update(f32 _dt){
    
}

void IMIPhysicsShapeBox::setSize(const FVec3& _size){
    m_size = _size;
}

const FVec3& IMIPhysicsShapeBox::getSize() const{
    return m_size;
}
