//
// SVTexture.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVTexture.h"
#include "../app/SVDispatch.h"
#include "../app/SVInst.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRenderMgr.h"
#include "../work/SVTdCore.h"
#include "../base/SVDataSwap.h"
//
#include "../rendercore/SVGL/SVRTexGL.h"
#include "../rendercore/SVGL/SVRendererGL.h"
//
#include "../rendercore/SVVulkan/SVRendererVK.h"

using namespace sv;

SVTexture::SVTexture(SVInstPtr _app)
: SVGBaseEx(_app) {
    m_name = "";
    m_bData = false;
    m_bEnableMipMap = false;
    m_bCreated = false;
    m_width = 0;
    m_height = 0;
    m_type = GL_TEXTURE_2D;
    m_informate = GL_RGBA;
    m_dataformate = GL_RGBA;
    m_objTexPtr = nullptr;
    m_pData = nullptr;
}

SVTexture::~SVTexture() {
    m_pData = nullptr;
    m_objTexPtr = nullptr;
    m_bCreated = false;
}

void SVTexture::init(SVTexParam& _param) {
    m_param = _param;
    m_pData = nullptr;
}

void SVTexture::init(SVTexParam& _param,SVDataSwapPtr _data) {
    m_param = _param;
    m_pData = _data;
}

//
void SVTexture::destroy(){
//    if (m_objTexPtr) {
//        m_objTexPtr->destroy(_renderer);
//    }
}

void SVTexture::setTexData(SVDataSwapPtr _data){
    //更新纹理数据
    m_pData = _data;
//    if (_data && _len > 0) {
//        m_bData = true;
//        m_pData->writeData(_data, _len);
//        _updateData();
//    }
}

void SVTexture::commit(){
    if (m_objTexPtr) {
        m_objTexPtr->commit();
    }
}

bool SVTexture::getbLoad(){
    if (m_objTexPtr) {
        return m_objTexPtr->getbLoad();
    }
    return 0;
}

void SVTexture::_updateData(){
    if (m_objTexPtr && m_bData) {
        m_objTexPtr->setTexData(m_pData->getData(), m_pData->getSize());
        m_pData->reback();
        m_bData = false;
    }
}

SVRTexPtr SVTexture::getResTex(){
    return m_objTexPtr;
}
