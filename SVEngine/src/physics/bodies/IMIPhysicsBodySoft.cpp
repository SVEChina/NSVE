//
// IMIPhysicsBodySoft.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIPhysicsBodySoft.h"
#include "IMIPhysicsBodyRigid.h"
#include "../../base/IMIVec3.h"

using namespace imi;

IMIPhysicsBodySoft::IMIPhysicsBodySoft(IMIInstPtr _app):IMIPhysicsBody(_app) {
    m_type = E_PHYSICS_BODY_SOFT;
    m_softBody = nullptr;
}

IMIPhysicsBodySoft::~IMIPhysicsBodySoft() {
    m_softBody = nullptr;
}

void IMIPhysicsBodySoft::init(){
    
}

void IMIPhysicsBodySoft::destroy(){
    if (m_softBody) {
        delete m_softBody;
    }
}

void IMIPhysicsBodySoft::update(f32 _dt){
    
}

btSoftBody* IMIPhysicsBodySoft::getBody(){
    return m_softBody;
}

void IMIPhysicsBodySoft::setTotalMass(f32 _mass){
    if (m_softBody) {
        m_softBody->setTotalMass(_mass);
    }
}

void IMIPhysicsBodySoft::setMass(s32 _bulletnode, f32 _mass){
    if (m_softBody) {
        m_softBody->setMass(_bulletnode, _mass);
    }
}

void IMIPhysicsBodySoft::setTimeScale(f32 _timescale){
    if (m_softBody) {
         m_softBody->m_cfg.timescale = _timescale;
    }
}

void IMIPhysicsBodySoft::appendAnchor(s32 _node,
                  IMIPhysicsBodyRigidPtr _body, bool _disableCollisionBetweenLinkedBodies, f32 _influence){
    if (m_softBody) {
        m_softBody->appendAnchor(_node, _body->getBody(), _disableCollisionBetweenLinkedBodies, _influence);
    }
}

void IMIPhysicsBodySoft::getNodes(IMISoftBodyNodeArray &_nodearray){
    if (m_softBody) {
        for (s32 i = 0; i < m_softBody->m_nodes.size(); i++) {
            const btSoftBody::Node& n = m_softBody->m_nodes[i];
            _nodearray.append(n);
        }
    }
}

s32 IMIPhysicsBodySoft::getNodesSize(){
    if (m_softBody) {
        return m_softBody->m_nodes.size();
    }
    return 0;
}

void IMIPhysicsBodySoft::getLinks(IMISoftBodyLinkArray &_linkarray){
    if (m_softBody) {
        for (s32 i = 0; i < m_softBody->m_links.size(); i++) {
            const btSoftBody::Link& l = m_softBody->m_links[i];
            _linkarray.append(l);
        }
    }
}

s32 IMIPhysicsBodySoft::getLinksSize(){
    if (m_softBody) {
        return m_softBody->m_links.size();
    }
    return 0;
}

void IMIPhysicsBodySoft::getFaces(IMISoftBodyFaceArray &_facearray){
    if (m_softBody) {
        for (s32 i = 0; i < m_softBody->m_faces.size(); i++) {
            const btSoftBody::Face& f = m_softBody->m_faces[i];
            _facearray.append(f);
        }
    }
}

s32 IMIPhysicsBodySoft::getFacesSize(){
    if (m_softBody) {
        return m_softBody->m_faces.size();
    }
    return 0;
}

