//
// SVRenderState.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#include "SVRenderState.h"
#include "SVRTarget.h"
#include "../app/SVInst.h"
#include "../basesys/SVSceneMgr.h"

using namespace sv;

SVRenderState::SVRenderState(SVInst *_app)
:SVGBase(_app){
    m_shaderID = 0;
}

SVRenderState::~SVRenderState() {
}
