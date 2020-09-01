//
// SVTransCPU.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVTransCPU.h"

using namespace sv;

SVTransCPU::SVTransCPU(SVInstPtr _app)
:SVTrans(_app){
}

SVTransCPU::~SVTransCPU() {
}

void SVTransCPU::init(s32 _w, s32 _h,f32 _angle,SV_PIC_FORMATE _picformate,SV_TEXIN _tt){
    SVTrans::init(_w, _h, _angle, _picformate,_tt);
}

void SVTransCPU::destroy(){
}

void SVTransCPU::update(f32 dt) {
}

void SVTransCPU::render(){
    
}
