//
// SVRTex.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTex.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "../base/SVResDsp.h"
#include "SVRenderer.h"

using namespace sv;

SVRTex::SVRTex(SVInstPtr _app)
:SVRRes(_app){
    m_texture_dsp = nullptr;
    m_msaa = 0;
    m_texLock = MakeSharedPtr<SVLockSpin>();
}

SVRTex:: ~SVRTex(){
    m_texture_dsp = nullptr;
    m_texLock = nullptr;
}

void SVRTex::load(SVRendererPtr _renderer,SVTextureDsp* _tex_dsp) {
    m_texture_dsp = _tex_dsp;
}

void SVRTex::unload() {
}

void SVRTex::resize() {
}

void SVRTex::commit() {
}

void SVRTex::setTexData(SVDataSwapPtr _data){
    if(m_texture_dsp) {
        m_texture_dsp->m_pData[0] = _data;
    }
}

void SVRTex::setTexCubeData(SVDataSwapPtr _data,s32 _index) {
    if(m_texture_dsp && _index>=0 && _index<6 ) {
        m_texture_dsp->m_pData[_index] = _data;
    }
}
