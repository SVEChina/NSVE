//
// IMIPhysicsShapeSphere.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIPhysicsShapeSphere.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"

using namespace imi;

IMIPhysicsShapeSphere::IMIPhysicsShapeSphere(IMIInstPtr _app)
:IMIPhysicsShape(_app) {
    m_type = E_PHYSICS_SHAPE_SPHERE;
    setRadius(0.0f);
    m_pColShape = nullptr;
}

IMIPhysicsShapeSphere::IMIPhysicsShapeSphere(IMIInstPtr _app, f32 _radius):IMIPhysicsShape(_app) {
    m_type = E_PHYSICS_SHAPE_SPHERE;
    setRadius(_radius);
    m_pColShape = nullptr;
}

IMIPhysicsShapeSphere::~IMIPhysicsShapeSphere() {
    
}

void IMIPhysicsShapeSphere::init(){
    m_pColShape = new btSphereShape(btScalar(m_radius));
    // 刚体是动态的如果且仅当质量为非零时，否则是静止的
    bool t_isDynamic = (m_mass != 0.f);
    btVector3 t_localInertia(m_localInertia.x,m_localInertia.y,m_localInertia.z);
    if (t_isDynamic)
        m_pColShape->calculateLocalInertia(m_mass,t_localInertia);
}

void IMIPhysicsShapeSphere::destroy(){

}

void IMIPhysicsShapeSphere::update(f32 _dt){
    
}

void IMIPhysicsShapeSphere::setRadius(const f32 _radius){
    m_radius = _radius;
}

const f32 IMIPhysicsShapeSphere::getRadius() const{
    return m_radius;
}
