//
// SVRenderPath.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderPath.h"
#include "../app/SVInst.h"

using namespace sv;

SVRenderPath::SVRenderPath(SVInstPtr _app)
:SVGBaseEx(_app){
    m_prez = false;
}

SVRenderPath::~SVRenderPath(){
}

void SVRenderPath::openPreZ() {
    //
    m_prez = true;
}

void SVRenderPath::closePreZ() {
    //
    m_prez = false;
}
