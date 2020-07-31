//
// SVRDPStateMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRDPStateMetal.h"
#include "SVRendererMetal.h"
#include "../../mtl/SVShader.h"
#include "../../app/SVInst.h"
#include "../../file/SVFileMgr.h"

using namespace sv;

SVRDPStateMetal::SVRDPStateMetal(SVInstPtr _app)
:SVRDPState(_app){
}

SVRDPStateMetal::~SVRDPStateMetal() {
}

void SVRDPStateMetal::create(SVRendererPtr _renderer) {
}
           
void SVRDPStateMetal::destroy(SVRendererPtr _renderer) {
}

bool SVRDPStateMetal::active(SVRendererPtr _render) {
    return true;
}
