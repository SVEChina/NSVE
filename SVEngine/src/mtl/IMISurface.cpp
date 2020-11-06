//
// IMISurface.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMISurface.h"

using namespace imi;

IMISurface::IMISurface() {
    m_tbl = MakeSharedPtr<IMIParamTbl>();
    m_vs_texs.resize(MAX_TEXUNIT);
    m_fs_texs.resize(MAX_TEXUNIT);
    m_tex_pool.clear();
}

IMISurface::~IMISurface() {
    for(s32 i=0;i<MAX_TEXUNIT;i++) {
        m_vs_texs[i] = nullptr;
        m_fs_texs[i] = nullptr;
    }
    m_vs_texs.clear();
    m_fs_texs.clear();
    m_tbl = nullptr;
}

//设置参数
void IMISurface::setParam(cptr8 _name,s32 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void IMISurface::setParam(cptr8 _name,f32 _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void IMISurface::setParam(cptr8 _name,FVec2& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void IMISurface::setParam(cptr8 _name,FVec3& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void IMISurface::setParam(cptr8 _name,FVec4& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void IMISurface::setParam(cptr8 _name,FMat2& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void IMISurface::setParam(cptr8 _name,FMat3& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

void IMISurface::setParam(cptr8 _name,FMat4& _value) {
    if(m_tbl) {
        m_tbl->setParam(_name, _value);
    }
}

//
void IMISurface::setParamArray(cptr8 _name,s32* _value,s32 _cnt) {
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setParamArray(cptr8 _name,f32* _value,s32 _cnt) {
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setParamArray(cptr8 _name,FVec2* _value,s32 _cnt){
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setParamArray(cptr8 _name,FVec3* _value,s32 _cnt){
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setParamArray(cptr8 _name,FVec4* _value,s32 _cnt){
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setParamArray(cptr8 _name,FMat2* _value,s32 _cnt){
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setParamArray(cptr8 _name,FMat3* _value,s32 _cnt){
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setParamArray(cptr8 _name,FMat4* _value,s32 _cnt){
    if(m_tbl) {
        m_tbl->setParamArray(_name, _value,_cnt);
    }
}

void IMISurface::setTexture(s32 _stage,s32 _chn,IMITexturePtr _tex) {
    if(_chn>=0 && _chn<MAX_TEXUNIT) {
        if(_stage == 0) {
            m_vs_texs[_chn] = _tex;
        }else if(_stage == 1) {
            m_fs_texs[_chn] = _tex;
        }
    }
}

IMITexturePtr IMISurface::getTexture(s32 _stage,s32 _chn) {
    if(_stage == 0) {
        if(_chn<m_vs_texs.size() ) {
            return m_vs_texs[_chn];
        }
    }else if(_stage == 1) {
        if(_chn<m_fs_texs.size() ) {
            return m_fs_texs[_chn];
        }
    }
    return nullptr;
}

void IMISurface::setTexture(cptr8 _name,IMITexturePtr _tex) {
    if(_tex && _name) {
        m_tex_pool[_name] = _tex;
    }
}

IMITexturePtr IMISurface::getTexture(cptr8 _name) {
    TEXPOOL::iterator it = m_tex_pool.find(_name);
    if(it!=m_tex_pool.end()) {
        return it->second;
    }
    return nullptr;
}

void IMISurface::setSamplerParam(cptr8 _name,s32 _type,s32 _param) {
    
}
