//
// IMIModelNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIModelNode.h"
#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIScene.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../mtl/IMIMtl3D.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../basesys/IMIConfig.h"
#include "../rendercore/IMIRenderer.h"
#include "../core/IMIModel.h"
#include "../core/IMIMesh3d.h"

using namespace imi;

//
IMIModelNode::IMIModelNode(IMIInstPtr _app)
:IMINode(_app) {
    ntype = "IMIModelNode";
    m_model = nullptr;
}

IMIModelNode::~IMIModelNode() {
    m_model = nullptr;
}

void IMIModelNode::update(f32 _dt) {
    IMINode::update(_dt);
    if(m_model) {
        m_model->update(_dt,m_absolutMat);
    }
}

void IMIModelNode::render() {
    if (!m_visible)
        return;
    if(m_model) {
        m_model->render();
    }
    IMINode::render();
}

void IMIModelNode::setModel(IMIModelPtr _model) {
    if(m_model!=_model) {
        m_model = _model;
    }
//    if(m_model) {
//        m_aabbBox = m_model->getBox();
//    }
}

IMIModelPtr IMIModelNode::getModel() {
    return m_model;
}
