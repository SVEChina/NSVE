//
// IMIFrameOutNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFrameOutNode.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMIComData.h"
#include "../basesys/IMISceneMgr.h"
#include "../mtl/IMIMtlRGB2YUV.h"
#include "../basesys/IMIConfig.h"
#include "../rendercore/IMIRTarget.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../mtl/IMITexture.h"

using namespace imi;

IMIFrameOutNode::IMIFrameOutNode(IMIInstPtr _app)
:IMINode(_app) {
    ntype = "IMIFrameOutNode";
    m_pData = nullptr;
}

IMIFrameOutNode::~IMIFrameOutNode() {
}

void IMIFrameOutNode::create(s32 _width,s32 _height) {
    
}

void IMIFrameOutNode::destroy() {
    
}

void IMIFrameOutNode::update(float _dt) {
    IMINode::update(_dt);
}

void IMIFrameOutNode::render() {
}

void IMIFrameOutNode::lockData() {
    
}

void IMIFrameOutNode::unlockData() {
    
}

void* IMIFrameOutNode::getData() {
    return m_pData;
}
