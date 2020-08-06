//
// SVSurface.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVSurface.h"

using namespace sv;

SVSurface::SVSurface() {
    m_tbl = MakeSharedPtr<SVParamTbl>();
    m_texpool.resize(MAX_TEXUNIT);
}

SVSurface::~SVSurface() {
    for(s32 i=0;i<MAX_TEXUNIT;i++) {
        m_texpool[i] = nullptr;
    }
    m_tbl = nullptr;
}

//设置参数
void SVSurface::setParam(cptr8 _name,s32 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,f32 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FVec2 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FVec3 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FVec4 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FMat2 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FMat3 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FMat4 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setTexture(s32 _chn,SVTexturePtr _tex) {
    if(_chn>=0 && _chn<MAX_TEXUNIT) {
        m_texpool[_chn] = _tex;
    }
}
