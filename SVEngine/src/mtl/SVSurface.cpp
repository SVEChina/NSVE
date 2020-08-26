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
    m_vs_texs.resize(MAX_TEXUNIT);
    m_fs_texs.resize(MAX_TEXUNIT);
}

SVSurface::~SVSurface() {
    for(s32 i=0;i<MAX_TEXUNIT;i++) {
        m_vs_texs[i] = nullptr;
        m_fs_texs[i] = nullptr;
    }
    m_vs_texs.clear();
    m_fs_texs.clear();
    m_tbl = nullptr;
}

//设置参数
void SVSurface::setParam(cptr8 _name,s32& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,f32& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FVec2& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FVec3& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FVec4& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FMat2& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FMat3& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setParam(cptr8 _name,FMat4& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void SVSurface::setTexture(s32 _chn,SVTexturePtr _tex,s32 _stage) {
    if(_chn>=0 && _chn<MAX_TEXUNIT) {
        if(_stage == 0) {
            m_vs_texs[_chn] = _tex;
        }else if(_stage == 1) {
            m_fs_texs[_chn] = _tex;
        }
    }
}
