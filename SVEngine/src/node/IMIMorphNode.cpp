//
// IMIMorphNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIMorphNode.h"
#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIScene.h"

using namespace imi;

IMIMorphNode::IMIMorphNode(IMIInstPtr _app)
:IMINode(_app){
    ntype = "IMIMorphNode";
}

IMIMorphNode::~IMIMorphNode() {
}
