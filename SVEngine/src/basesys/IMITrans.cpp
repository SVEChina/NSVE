//
// IMITrans.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMITrans.h"

using namespace imi;

IMITrans::IMITrans(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_width = 0;
    m_height = 0;
    m_picformate = IMI_PF_RGBA;
    m_angle = 0;
}

IMITrans::~IMITrans() {
}

void IMITrans::init(s32 _w, s32 _h,f32 _angle,IMI_PIC_FORMATE _picformate,IMI_TEXIN _tt){
    m_width = _w;
    m_height = _h;
    m_picformate = _picformate;
    m_angle = _angle;
    m_texTT = _tt;
}

void IMITrans::setAngle(f32 _angle){
    m_angle=_angle;
}

void IMITrans::destroy(){
}

void IMITrans::update(f32 dt) {
    
}

void IMITrans::render() {
    
}
