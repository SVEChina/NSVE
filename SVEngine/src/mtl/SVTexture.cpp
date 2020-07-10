//
// SVTexture.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVTexture.h"
#include "../mtl/SVTexMgr.h"
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
    m_pData = MakeSharedPtr<SVDataSwap>();
}

SVTexture::~SVTexture() {
    m_pData = nullptr;
    m_objTexPtr = nullptr;
    m_bCreated = false;
}

//void SVTexture::create(SVRendererPtr _renderer){
//    SV_LOG_INFO("texture create id %d \n",m_uid);
////    SVRRes::create(_renderer);
////    if (!m_bCreated) {
////        m_bCreated = true;
////        SVRendererPtr t_renderBasePtr = mApp->getRenderer();
////        SVRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<SVRendererGL>(t_renderBasePtr);
////        if (t_renderGLPtr) {
////            //渲染器类型E_RENDERER_GLES,
////            m_objTexPtr = MakeSharedPtr<SVRGLTex>(mApp);
////        }
////        SVRendererVKPtr t_rendeVKPtr = std::dynamic_pointer_cast<SVRendererVK>(t_renderBasePtr);
////        if (t_rendeVKPtr) {
////            //渲染器类型E_RENDERER_VUNKAN,
////            //m_objTexPtr = MakeSharedPtr<SVRGLTex>(mApp);
////        }
////#if defined(SV_IOS) || defined(SV_OSX)
//////        SVRendererMetalPtr t_rendeMetalPtr = std::dynamic_pointer_cast<SVRendererMetal>(t_renderBasePtr);
//////        if (t_rendeMetalPtr) {
//////            //渲染器类型E_RENDERER_METAL,
//////            m_objTexPtr = MakeSharedPtr<SVRMetalTex>(mApp);
//////        }
////#endif
////        if (m_objTexPtr) {
////            m_objTexPtr->setname(m_name);
////            m_objTexPtr->settype(m_type);
////            m_objTexPtr->setwidth(m_width);
////            m_objTexPtr->setheight(m_height);
////            m_objTexPtr->setinformate(m_informate);
////            m_objTexPtr->setdataformate(m_dataformate);
////            m_objTexPtr->setEnableMipMap(m_bEnableMipMap);
////            _updateData();
////            m_objTexPtr->create(t_renderBasePtr);
////        }
////    }
//}

void SVTexture::init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dateformate, bool _enableMipMap){
    m_name = _name;
    m_width = _width;
    m_height = _height;
    m_type = _type;
    m_informate = _informate;
    m_dataformate = _dateformate;
    m_bEnableMipMap = _enableMipMap;
}

//
void SVTexture::destroy(){
//    if (m_objTexPtr) {
//        m_objTexPtr->destroy(_renderer);
//    }
}

void SVTexture::setTexData(void *_data, s32 _len){
    if (_data && _len > 0) {
        m_bData = true;
        m_pData->writeData(_data, _len);
        _updateData();
    }
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
