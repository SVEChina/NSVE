//
// SVGameReady.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVGameReady.h"

using namespace sv;

SVGameReady::SVGameReady(SVInstPtr _app)
:SVGamePart(_app) {
}

SVGameReady::~SVGameReady() {
}

void SVGameReady::init() {
}

void SVGameReady::destroy() {
}

void SVGameReady::update(f32 _dt) {
    
}

bool SVGameReady::isEnd(){
    return true;
}
