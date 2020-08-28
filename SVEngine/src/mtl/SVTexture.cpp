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
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRenderMgr.h"
#include "../work/SVTdCore.h"
#include "../base/SVDataSwap.h"
//#include "../rendercore/SVGL/SVRTexGL.h"
//#include "../rendercore/SVGL/SVRendererGL.h"
//#include "../rendercore/SVVulkan/SVRendererVK.h"

using namespace sv;

SVTexture::SVTexture(SVInstPtr _app)
: SVGBaseEx(_app) {
    m_lock = MakeSharedPtr<SVLockSpin>();
    m_name = "";
    m_restex = nullptr;
    for(s32 i=0;i<6;i++) {
        m_pData[i] = nullptr;
    }
}

SVTexture::~SVTexture() {
    m_lock = nullptr;
    m_restex = nullptr;
    for(s32 i=0;i<6;i++) {
        m_pData[i] = nullptr;
    }
}

void SVTexture::init(SVTextureDsp& _param) {
    m_texture_dsp = _param;
    setTexData(nullptr);
}

void SVTexture::init(SVTextureDsp& _param,SVDataSwapPtr _data) {
    m_texture_dsp = _param;
    setTexData(_data);
}

//
void SVTexture::destroy(){
    for(s32 i=0;i<6;i++) {
        m_pData[i] = nullptr;
    }
}

//
void SVTexture::resize(s32 _w,s32 _h) {
    if(m_texture_dsp.m_width == _w && m_texture_dsp.m_height == _h) {
        return ;
    }
    //
    m_texture_dsp.m_width = _w;
    m_texture_dsp.m_height = _h;
    if(m_restex) {
        m_restex->resize();
    }
}

SVTextureDsp* SVTexture::getTextureDsp() {
    return &m_texture_dsp;
}

SVDataSwapPtr SVTexture::getTextureData() {
    return m_pData[0];
}

SVDataSwapPtr SVTexture::getTextureCubeData(s32 _index) {
    if(_index>=0 && _index<6) {
        return m_pData[_index];
    }
    return nullptr;
}

void SVTexture::lockData() {
    if(m_lock) {
        m_lock->lock();
    }
}

void SVTexture::unlockData() {
    if(m_lock) {
        m_lock->unlock();
    }
}

void SVTexture::setTexData(SVDataSwapPtr _data){
    //更新纹理数据
    lockData();
    m_pData[0] = _data;
    unlockData();
}

void SVTexture::setTexCubeData(SVDataSwapPtr _data,s32 _index){
    //更新纹理数据
    lockData();
    if(_index>=0 && _index<6) {
        m_pData[_index] = _data;
    }
    unlockData();
}

void SVTexture::bindRes(SVRTexPtr _res) {
    m_restex = _res;
}

void SVTexture::unbindRes() {
    m_restex = nullptr;
}

SVRTexPtr SVTexture::getResTex(){
    return m_restex;
}

void SVTexture::swap(SVTexturePtr _tex) {
    if(_tex && m_restex) {
        m_restex->swap(_tex->getResTex());
    }
}
