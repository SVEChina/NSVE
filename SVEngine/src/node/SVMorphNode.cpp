//
// SVMorphNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMorphNode.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"

using namespace sv;

SVMorphNode::SVMorphNode(SVInstPtr _app)
:SVNode(_app){
    ntype = "SVMorphNode";
}

SVMorphNode::~SVMorphNode() {
}
