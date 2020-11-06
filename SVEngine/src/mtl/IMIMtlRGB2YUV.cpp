//
// IMIMtlRGB2YUV.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIMtlRGB2YUV.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

IMIMtlRGB2YUV::IMIMtlRGB2YUV(IMIInstPtr _app, IMI_OUTSTEAMFORMATE formate)
:IMIMtlCore(_app,"rgb2yuvnv21") {
    if (formate == IMI_OUT_STEAM_RGB2YUVNV21) {
        //reloadShader("rgb2yuvnv21");
    }
    if (formate == IMI_OUT_STEAM_RGB2YUVNV12) {
        //reloadShader("rgb2yuvnv12");
    }
    if (formate == IMI_OUT_STEAM_RGB2YUVYV12) {
        //reloadShader("rgb2yuvyv12");
    }
    if (formate == IMI_OUT_STEAM_RGB2YUVI420) {
        //reloadShader("rgb2yuvi420");
    }
}

IMIMtlRGB2YUV::IMIMtlRGB2YUV(IMIMtlRGB2YUV *_mtl)
:IMIMtlCore(_mtl){
    m_tex_w = _mtl->m_tex_w;
    m_tex_h = _mtl->m_tex_h;
}

IMIMtlRGB2YUV::~IMIMtlRGB2YUV() {
}

IMIMtlCorePtr IMIMtlRGB2YUV::clone() {
    return PointerSharedPtr<IMIMtlRGB2YUV>(new IMIMtlRGB2YUV(this));
}

void IMIMtlRGB2YUV::setTex(f32 _w, f32 _h) {
    m_tex_w = _w;
    m_tex_h = _h;
}

void IMIMtlRGB2YUV::_submitMtl(IMIRendererPtr _render) {
//    _render->submitUniformf("width", m_tex_w);
//    _render->submitUniformf("height", m_tex_h);
}

