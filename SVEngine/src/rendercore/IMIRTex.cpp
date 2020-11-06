//
// IMIRTex.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRTex.h"
#include "../app/IMIInst.h"
#include "../work/IMITdCore.h"
#include "../base/IMIResDsp.h"
#include "IMIRenderer.h"

using namespace imi;

IMIRTex::IMIRTex(IMIInstPtr _app)
:IMIRRes(_app){
    m_texture_dsp = nullptr;
    m_msaa = 0;
    m_texLock = MakeSharedPtr<IMILockSpin>();
}

IMIRTex:: ~IMIRTex(){
    m_texture_dsp = nullptr;
    m_texLock = nullptr;
}

void IMIRTex::load(IMIRendererPtr _renderer,IMITextureDsp* _tex_dsp) {
    m_texture_dsp = _tex_dsp;
}

void IMIRTex::unload() {
}

void IMIRTex::resize() {
}

void IMIRTex::commit() {
}

void IMIRTex::setTexData(IMIDataSwapPtr _data){
    if(m_texture_dsp) {
        m_texture_dsp->m_pData[0] = _data;
    }
}

void IMIRTex::setTexCubeData(IMIDataSwapPtr _data,s32 _index) {
    if(m_texture_dsp && _index>=0 && _index<6 ) {
        m_texture_dsp->m_pData[_index] = _data;
    }
}
