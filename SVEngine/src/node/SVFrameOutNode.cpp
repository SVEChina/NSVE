//
// SVFrameOutNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFrameOutNode.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVComData.h"
#include "../basesys/SVSceneMgr.h"
#include "../mtl/SVMtlRGB2YUV.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRenderTexture.h"
#include "../rendercore/SVRenderObject.h"
#include "../rendercore/SVRenderMgr.h"
#include "../mtl/SVTexture.h"

using namespace sv;

SVFrameOutNode::SVFrameOutNode(SVInstPtr _app)
:SVNode(_app) {
    ntype = "SVFrameOutNode";
    m_pData = nullptr;
}

SVFrameOutNode::~SVFrameOutNode() {
}

void SVFrameOutNode::create(s32 _width,s32 _height) {
    
}

void SVFrameOutNode::destroy() {
    
}

void SVFrameOutNode::update(float _dt) {
    SVNode::update(_dt);
}

void SVFrameOutNode::render() {
}

void SVFrameOutNode::lockData() {
    
}

void SVFrameOutNode::unlockData() {
    
}

void* SVFrameOutNode::getData() {
    return m_pData;
}
