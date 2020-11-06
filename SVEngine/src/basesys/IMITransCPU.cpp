//
// IMITransCPU.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMITransCPU.h"

using namespace imi;

IMITransCPU::IMITransCPU(IMIInstPtr _app)
:IMITrans(_app){
}

IMITransCPU::~IMITransCPU() {
}

void IMITransCPU::init(s32 _w, s32 _h,f32 _angle,IMI_PIC_FORMATE _picformate,IMI_TEXIN _tt){
    IMITrans::init(_w, _h, _angle, _picformate,_tt);
}

void IMITransCPU::destroy(){
}

void IMITransCPU::update(f32 dt) {
}

void IMITransCPU::render(){
    
}
