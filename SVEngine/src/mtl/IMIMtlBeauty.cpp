//
// IMIMtlBeauty.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIMtlBeauty.h"
#include "../mtl/IMITexMgr.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

//
IMIMtlBeauty::IMIMtlBeauty(IMIInstPtr _app)
:IMIMtlCore(_app,"beauty") {
    m_lImgW=720;
    m_lImgH=1280;
    m_lSmoothSize=0.5f;
}

IMIMtlBeauty::IMIMtlBeauty(IMIMtlBeauty* _mtl)
:IMIMtlCore(_mtl) {
    m_lImgW=_mtl->m_lImgW;
    m_lImgH=_mtl->m_lImgH;
    m_lSmoothSize=_mtl->m_lSmoothSize;
}

IMIMtlBeauty::~IMIMtlBeauty(){
}

IMIMtlCorePtr IMIMtlBeauty::clone() {
    return PointerSharedPtr<IMIMtlBeauty>(new IMIMtlBeauty(this));
}

void IMIMtlBeauty::_submitMtl(IMIRendererPtr _render) {
    IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("softenStrength", m_lSmoothSize);
//    _render->submitUniformf2("imageSize", m_lImgW,m_lImgH);
}

void IMIMtlBeauty::setSmooth(f32 _smooth) {
    if (_smooth >= 0.0) {
        m_lSmoothSize = clamp(0.0f,_smooth,1.0f);
    }
}

void IMIMtlBeauty::setBGSize(s32 _width, s32 _height) {
    m_lImgW = _width;
    m_lImgH = _height;
}

