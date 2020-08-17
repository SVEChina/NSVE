//
// SVMesh2DNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMesh2DNode.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"
#include "../app/SVInst.h"
#include "../mtl/SVMtlNocolor.h"
#include "../rendercore/SVRenderObject.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

SVMesh2DNode::SVMesh2DNode(SVInstPtr _app)
: SVNode(_app) {
    ntype = "SVMesh2DNode";
    m_pMesh = nullptr;
}

SVMesh2DNode::~SVMesh2DNode() {
    m_pMesh = nullptr;
}

void SVMesh2DNode::update(f32 _dt) {
    SVNode::update(_dt);
    
}

void SVMesh2DNode::render() {
    if (m_visible ){
        
    }
    SVNode::render();
}

void SVMesh2DNode::setMesh(SVRenderMeshPtr _mesh) {
    m_pMesh = _mesh;
}
