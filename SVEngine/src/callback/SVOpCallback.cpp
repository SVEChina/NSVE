//
// SVOpCallback.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVOpCallback.h"

using namespace sv;

SVOpCallback::SVOpCallback(SVInstPtr _app)
:SVCallbackBase(_app) {
}

SVOpCallback::~SVOpCallback() {
}

void SVOpCallback::opBegin(SVOpBase* _op){
}

void SVOpCallback::opEnd(SVOpBase* _op){
    
}

