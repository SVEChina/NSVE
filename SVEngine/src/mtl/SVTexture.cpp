//
// SVTexture.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#include "SVTexture.h"
#include "../work/SVTdCore.h"
#include "../app/SVDispatch.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "../base/SVDataSwap.h"
#include "../rendercore/SVRenderer.h"

using namespace sv;

SVTexture::SVTexture(SVInstPtr _app)
:SVGBaseEx(_app) {
    m_lock = MakeSharedPtr<SVLockSpin>();
    m_name = "";
    m_tex_pool_id = -1;
    for(s32 i=0;i<6;i++) {
        m_texture_dsp.m_pData[i] = nullptr;
    }
}

SVTexture::~SVTexture() {
    m_lock = nullptr;
    m_tex_pool_id = -1;
    for(s32 i=0;i<6;i++) {
        m_texture_dsp.m_pData[i] = nullptr;
    }
}

void SVTexture::init(SVTextureDsp& _dsp) {
    m_texture_dsp = _dsp;
    setTexData(nullptr);
}

void SVTexture::init(SVTextureDsp& _dsp,SVDataSwapPtr _data) {
    m_texture_dsp = _dsp;
    setTexData(_data);
}

void SVTexture::destroy(){
    for(s32 i=0;i<6;i++) {
        m_texture_dsp.m_pData[i] = nullptr;
    }
}

void SVTexture::resize(s32 _w,s32 _h) {
    if(m_texture_dsp.m_width == _w && m_texture_dsp.m_height == _h) {
        return ;
    }
    m_texture_dsp.m_width = _w;
    m_texture_dsp.m_height = _h;
//    if(m_restex) {
//        m_restex->resize();
//    }
}

SVDataSwapPtr SVTexture::getTextureData() {
    return m_texture_dsp.m_pData[0];
}

SVDataSwapPtr SVTexture::getTextureCubeData(s32 _index) {
    if(_index>=0 && _index<6) {
        return m_texture_dsp.m_pData[_index];
    }
    return nullptr;
}

void SVTexture::setTexData(SVDataSwapPtr _data){
    m_lock->lock();
    m_texture_dsp.m_pData[0] = _data;
    m_lock->unlock();
}

void SVTexture::setTexCubeData(SVDataSwapPtr _data,s32 _index){
    m_lock->lock();
    if(_index>=0 && _index<6) {
        m_texture_dsp.m_pData[_index] = _data;
    }
    m_lock->unlock();
}

void SVTexture::bindRes(s32 _instid) {
    m_tex_pool_id = _instid;
}

void SVTexture::unbindRes() {
    m_tex_pool_id = -1;
}

SVRTexPtr SVTexture::getResTex(){
    if(mApp->getRenderer() ) {
        return mApp->getRenderer()->getResTexture( m_tex_pool_id );
    }
    return nullptr;
}

void SVTexture::swap(SVTexturePtr _tex) {
    SVRTexPtr t_res_tex = getResTex();
    if(_tex && t_res_tex) {
        t_res_tex->swap(_tex->getResTex());
    }
}
