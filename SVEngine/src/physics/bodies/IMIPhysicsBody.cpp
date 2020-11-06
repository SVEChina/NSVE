//
// IMIPhysicsBody.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIPhysicsBody.h"

using namespace imi;

IMIPhysicsBody::IMIPhysicsBody(IMIInstPtr _app):IMIGBaseEx(_app) {
    m_type = E_PHYSICS_BODY_BASE;
    m_pNode = nullptr;
}

IMIPhysicsBody::~IMIPhysicsBody() {
    m_pNode = nullptr;
}

void IMIPhysicsBody::init(){
    
}

void IMIPhysicsBody::destroy(){
    
}

void IMIPhysicsBody::update(f32 _dt){
    
}

PHYSICSBODYTYPE IMIPhysicsBody::getType() const{
    return m_type;
}

void IMIPhysicsBody::setNode(IMINodePtr _node) {
    if (_node) {
        m_pNode = _node;
    }
}

IMINodePtr IMIPhysicsBody::getNode(){
    return m_pNode;
}
