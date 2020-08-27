//
// SVRTex.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTex.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVRenderer.h"

using namespace sv;

SVRTex::SVRTex(SVInstPtr _app)
:SVRRes(_app){
    m_msaa = 0;
    m_texLock = MakeSharedPtr<SVLockSpin>();
    m_data = nullptr;
    for(s32 i=0;i<6;i++) {
        m_cube_data[i] = nullptr;
    }
}

SVRTex:: ~SVRTex(){
    m_data = nullptr;
    for(s32 i=0;i<6;i++) {
        m_cube_data[i] = nullptr;
    }
    m_texLock = nullptr;
}

void SVRTex::create(SVRendererPtr _renderer) {}

void SVRTex::destroy(SVRendererPtr _renderer) {}

void SVRTex::resize(s32 _w,s32 _h) {}

void SVRTex::commit() {}

void SVRTex::swap(SVRTexPtr _rtex) {}

void SVRTex::setTexData(SVDataSwapPtr _data){
    m_data = _data;
}

void SVRTex::setTexCubeData(SVDataSwapPtr _data,s32 _index) {
    if(_index>=0 && _index<6) {
        m_cube_data[_index] = _data;
    }
}
