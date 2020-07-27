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
    m_bEnableMipMap = false;
    m_restex = nullptr;
    m_pData = nullptr;
}

SVTexture::~SVTexture() {
    m_lock = nullptr;
    m_pData = nullptr;
    m_restex = nullptr;
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
//    if (m_restex) {
//        m_restex->destroy(_renderer);
//    }
}

SVTextureDsp* SVTexture::getTextureDsp() {
    return &m_texture_dsp;
}

SVDataSwapPtr SVTexture::getTextureData() {
    return m_pData;
}

SVDataSwapPtr SVTexture::getTextureCubeData(s32 _index) {
    if(_index>=0 && _index<6) {
        return m_cubData[_index];
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
    m_pData = _data;
    unlockData();
}

bool SVTexture::getbLoad(){
//    if (m_restex) {
//        return m_restex->getbLoad();
//    }
    return 0;
}

void SVTexture::_updateData(){
//    if (m_restex && m_bData) {
//        m_restex->setTexData(m_pData->getData(), m_pData->getSize());
//        m_pData->reback();
//        m_bData = false;
//    }
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
