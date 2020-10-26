//
// SVModelNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVModelNode.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderMesh.h"
#include "../mtl/SVMtl3D.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRenderer.h"
#include "../core/SVModel.h"
#include "../core/SVMesh3d.h"

using namespace sv;

//
SVModelNode::SVModelNode(SVInstPtr _app)
:SVNode(_app) {
    ntype = "SVModelNode";
    m_model = nullptr;
}

SVModelNode::~SVModelNode() {
    m_model = nullptr;
}

void SVModelNode::update(f32 _dt) {
    SVNode::update(_dt);
    if(m_model) {
        m_model->update(_dt,m_absolutMat);
    }
}

void SVModelNode::render() {
    if (!m_visible)
        return;
    if(m_model) {
        m_model->render();
    }
    SVNode::render();
}

void SVModelNode::setModel(SVModelPtr _model) {
    if(m_model!=_model) {
        m_model = _model;
    }
//    if(m_model) {
//        m_aabbBox = m_model->getBox();
//    }
}

SVModelPtr SVModelNode::getModel() {
    return m_model;
}
