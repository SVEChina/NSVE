//
// SVCtxBase.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVCtxBase.h"

using namespace sv;

SVCtxBase::SVCtxBase(SVInstPtr _app)
:SVGBaseEx(_app){
}

SVCtxBase::~SVCtxBase() {
}

bool SVCtxBase::activeContext(SVRendererPtr _renderer){
    return false;
}

bool SVCtxBase::swap(SVRendererPtr _renderer){
    return false;
}
