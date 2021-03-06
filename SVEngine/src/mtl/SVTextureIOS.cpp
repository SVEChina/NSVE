//
// SVTextureIOS.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#include "SVTextureIOS.h"
#include "../rendercore/SVGL/SVRTexGL.h"
#include "../app/SVInst.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVGL/SVRendererGL.h"

using namespace sv;

SVTextureIOS::SVTextureIOS(SVInstPtr _app)
:SVTexture(_app) {
}

SVTextureIOS::~SVTextureIOS() {
}

void SVTextureIOS::init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dateformate, bool _enableMipMap){
    m_name = _name;
//    m_width = _width;
//    m_height = _height;
//    m_type = _type;
//    m_informate = _informate;
//    m_dataformate = _dateformate;
}


void SVTextureIOS::create(SVRendererPtr _renderer){
//    SVRRes::create(_renderer);
//    if (!m_bCreated) {
//        m_bCreated = true;
//        SVRendererPtr t_renderBasePtr = mApp->getRenderer();
//        SVRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<SVRendererGL>(t_renderBasePtr);
//        if (t_renderGLPtr) {
//            //渲染器类型E_RENDERER_GLES,
//            m_restex = MakeSharedPtr<SVRTexGLiOS>(mApp)  ;
//        }
//        
//        if (m_restex) {
//            m_restex->setname(m_name);
//            m_restex->settype(m_type);
//            m_restex->setwidth(m_width);
//            m_restex->setheight(m_height);
//            m_restex->setinformate(m_informate);
//            m_restex->setdataformate(m_dataformate);
//            m_restex->create(_renderer);
//        }
//    }
}

void SVTextureIOS::destroy(SVRendererPtr _renderer){
//    if (m_restex) {
//        m_restex->destroy(_renderer);
//    }
//    SVRRes::destroy(_renderer);
}

void SVTextureIOS::pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate){
#ifdef SV_IOS
//    SVRTexGLiOSPtr t_tmp = std::dynamic_pointer_cast<SVRTexGLiOS>(m_restex);
//    if (t_tmp) {
//        t_tmp->pushData(_srcPtr, _w, _h, _pixelformate);
//    }
#endif
}

void SVTextureIOS::fetchData(u8* _dstPtr,s32 _w,s32 _h) {
#ifdef SV_IOS
//    SVRTexGLiOSPtr t_tmp = std::dynamic_pointer_cast<SVRTexGLiOS>(m_restex);
//    if (t_tmp) {
//        t_tmp->fetchData(_dstPtr, _w, _h);
//    }
#endif
}
