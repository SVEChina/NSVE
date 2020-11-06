//
// IMIStreamIn.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIStreamIn.h"

using namespace imi;

//
StreamInCore::StreamInCore(IMIInstPtr _app)
:IMIGBaseEx(_app){
//    m_trans = nullptr;
//    m_showNode = nullptr;
//    m_tt = E_TEX_END;
//    m_useGPU = true;
//    m_texResult = nullptr;
//    m_tex0 = nullptr;
//    m_tex1 = nullptr;
//    m_tex2 = nullptr;
}

StreamInCore::~StreamInCore() {
//    m_trans = nullptr;
//    m_showNode = nullptr;
//    m_tt = E_TEX_END;
//    m_texResult = nullptr;
//    m_tex0 = nullptr;
//    m_tex1 = nullptr;
//    m_tex2 = nullptr;
}

void StreamInCore::init(s32 _w,s32 _h,IMI_PIC_FORMATE _fromate,f32 _angle,bool _show) {
//    for(s32 t_tt = E_TEX_INSTREAM ;t_tt<E_TEX_OUTSTREAM; t_tt++ ) {
//        if(!mApp->getRenderer()->getIMITex( IMI_TEXIN(t_tt) ) ){
//            init(_w,_h,_fromate,_angle,_show,IMI_TEXIN(t_tt) );
//            return ;
//        }
//    }
}

void StreamInCore::init(s32 _w,s32 _h,IMI_PIC_FORMATE _fromate,f32 _angle,bool _show,IMI_TEXIN _tex){
//    m_tt = _tex;
//    //创建稳定的合成后的流
//    m_formate = _fromate;
//    m_texResult = mApp->getRenderer()->createIMITex(m_tt,_w,_h,GL_RGBA);
//    //创建输入流
//    if(_fromate == IMI_PF_GRAY8) {
//        //m_gray
//        m_tex0 = mApp->getTexMgr()->createUnctrlTexture(_w,_h,GL_LUMINANCE,GL_LUMINANCE);
//    }else if(_fromate == IMI_PF_YV12) {
//        //m_texY
//        m_tex0 = mApp->getTexMgr()->createUnctrlTexture(_w, _h, GL_LUMINANCE,GL_LUMINANCE);
//        //m_texUV
//        m_tex1 = mApp->getTexMgr()->createUnctrlTexture(_w/2, _h/2,GL_LUMINANCE_ALPHA,GL_LUMINANCE_ALPHA);
//    }else if(_fromate == IMI_PF_I420) {
//        m_tex0 = mApp->getTexMgr()->createUnctrlTexture(_w, _h, GL_LUMINANCE, GL_LUMINANCE);
//        m_tex1 = mApp->getTexMgr()->createUnctrlTexture(_w,_h,  GL_LUMINANCE, GL_LUMINANCE);
//        m_tex2 = mApp->getTexMgr()->createUnctrlTexture(_w, _h, GL_LUMINANCE, GL_LUMINANCE);
//    }else if(_fromate == IMI_PF_NV12) {
//        //m_texY
//        m_tex0 = mApp->getTexMgr()->createUnctrlTexture(_w,  _h, GL_LUMINANCE, GL_LUMINANCE);
//        //m_texUV
//        m_tex1 = mApp->getTexMgr()->createUnctrlTexture(_w / 2,_h / 2, GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA);
//    }else if(_fromate == IMI_PF_NV21) {
//        //m_texY
//        m_tex0 = mApp->getTexMgr()->createUnctrlTexture(_w, _h, GL_LUMINANCE, GL_LUMINANCE);
//        //m_texUV
//        m_tex1 = mApp->getTexMgr()->createUnctrlTexture(_w / 2, _h / 2, GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA);
//    }else if(_fromate == IMI_PF_BGRA) {
//        m_tex0 = mApp->getTexMgr()->createUnctrlTexture(_w,_h,GL_RGBA,GL_RGBA);
//    }else if(_fromate == IMI_PF_RGBA) {
//        m_tex0 = mApp->getTexMgr()->createUnctrlTexture(_w,_h,GL_RGBA,GL_RGBA);
//    }
//    //转换方式
//    if(m_useGPU) {
//        m_trans = MakeSharedPtr<IMITransGPU>(mApp,m_tex0,m_tex1,m_tex2,m_texResult);
//        m_trans->init(_w, _h,_angle,_fromate,m_tt);
//    } else {
//
//    }
//    //
//    if(_show && m_trans) {
//#ifdef IMI_IOS
//        m_showNode = MakeSharedPtr<IMIIOSInstreamNode>(mApp);
//        IMIIOSInstreamNodePtr tmpNode = std::dynamic_pointer_cast<IMIIOSInstreamNode>(m_showNode);
//        if(tmpNode){
//            tmpNode->init(m_tt);
//        }
//#endif
//
//#ifdef IMI_ANDROID
//        m_showNode = MakeSharedPtr<IMISpriteNode>(mApp,(f32)_h,(f32)_w);
//        IMISpriteNodePtr tmpNode = std::dynamic_pointer_cast<IMISpriteNode>(m_showNode);
//        if(tmpNode){
//            tmpNode->setTexture(m_tt);
//            tmpNode->setRSType(RST_SKY);
//        }
//#endif
//
//    }
}

//
void StreamInCore::init(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _w,s32 _h,IMI_PIC_FORMATE _fromate,f32 _angle,bool _show) {
//    for(s32 t_tt = E_TEX_INSTREAM ;t_tt<E_TEX_OUTSTREAM; t_tt++ ) {
//        if(!mApp->getRenderer()->getIMITex( IMI_TEXIN(t_tt) ) ){
//            init(_tex0ID, _tex1ID, _tex2ID,  _w,_h,_fromate,_angle,_show,IMI_TEXIN(t_tt) );
//            return ;
//        }
//    }
}

void StreamInCore::init(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _w,s32 _h,IMI_PIC_FORMATE _fromate,f32 _angle,bool _show,IMI_TEXIN _tex){
//    m_tt = _tex;
//    //创建稳定的合成后的流
//    m_formate = _fromate;
//    m_texResult = mApp->getRenderer()->createIMITex(m_tt,_w,_h,GL_RGBA);
//    //创建输入流
//    if(_fromate == IMI_PF_GRAY8) {
//        //m_gray
//        m_tex0 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex0ID, _w,_h,GL_LUMINANCE,GL_LUMINANCE);
//    }else if(_fromate == IMI_PF_YV12) {
//        //m_texY
//        m_tex0 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex0ID, _w, _h, GL_LUMINANCE,GL_LUMINANCE);
//        //m_texUV
//        m_tex1 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex1ID, _w/2, _h/2,GL_LUMINANCE_ALPHA,GL_LUMINANCE_ALPHA);
//    }else if(_fromate == IMI_PF_I420) {
//        m_tex0 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex0ID, _w, _h, GL_LUMINANCE, GL_LUMINANCE);
//        m_tex1 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex1ID, _w,_h,  GL_LUMINANCE, GL_LUMINANCE);
//        m_tex2 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex2ID, _w, _h, GL_LUMINANCE, GL_LUMINANCE);
//    }else if(_fromate == IMI_PF_NV12) {
//        //m_texY
//        m_tex0 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex0ID, _w,  _h, GL_LUMINANCE, GL_LUMINANCE);
//        //m_texUV
//        m_tex1 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex1ID, _w / 2,_h / 2, GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA);
//    }else if(_fromate == IMI_PF_NV21) {
//        //m_texY
//        m_tex0 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex0ID, _w, _h, GL_LUMINANCE, GL_LUMINANCE);
//        //m_texUV
//        m_tex1 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex1ID, _w / 2, _h / 2, GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA);
//    }else if(_fromate == IMI_PF_BGRA) {
//        m_tex0 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex0ID, _w,_h,GL_RGBA,GL_RGBA);
//    }else if(_fromate == IMI_PF_RGBA) {
//        m_tex0 = mApp->getTexMgr()->createUnctrlTextureWithTexID(_tex0ID, _w,_h,GL_RGBA,GL_RGBA);
//    }
//    //转换方式
//    if(m_useGPU) {
//        m_trans = MakeSharedPtr<IMITransGPU>(mApp,m_tex0,m_tex1,m_tex2,m_texResult);
//        m_trans->init(_w, _h,_angle,_fromate,m_tt);
//    } else {
//
//    }
//    //
//    if(_show && m_trans) {
//#ifdef IMI_IOS
//        m_showNode = MakeSharedPtr<IMIIOSInstreamNode>(mApp);
//        IMIIOSInstreamNodePtr tmpNode = std::dynamic_pointer_cast<IMIIOSInstreamNode>(m_showNode);
//        if(tmpNode){
//            tmpNode->init(m_tt);
//        }
//#endif
//
//#ifdef IMI_ANDROID
//        m_showNode = MakeSharedPtr<IMISpriteNode>(mApp,(f32)_h,(f32)_w);
//        IMISpriteNodePtr tmpNode = std::dynamic_pointer_cast<IMISpriteNode>(m_showNode);
//        if(tmpNode){
//            tmpNode->setTexture(m_tt);
//            tmpNode->setRSType(RST_SKY);
//        }
//#endif
//
//    }
}

void StreamInCore::destroy() {
//    //
//    if(m_showNode) {
//        m_showNode->removeFromParent();
//        m_showNode = nullptr;
//    }
//    m_texResult = nullptr;
//    m_tex0 = nullptr;
//    m_tex1 = nullptr;
//    m_tex2 = nullptr;
//    m_trans = nullptr;
//    m_tt = E_TEX_END;
//    if(mApp->getRenderer()) {
//        //mApp->getRenderer()->destroyIMITex(m_tt);
//    }
}

void StreamInCore::active() {
//    if(m_showNode) {
//        IMIScenePtr t_sc = mApp->getSceneMgr()->getScene();
//        if(t_sc){
//            t_sc->addNode(m_showNode);
//        }
//    }
}

void StreamInCore::unactive() {
//    if(m_showNode) {
//        m_showNode->removeFromParent();
//    }
}

void StreamInCore::update(f32 _dt) {

}

void StreamInCore::pushData(u8* _srcPtr,s32 width,s32 height,s32 pixelFormat,s32 _angle) {
//    if(m_trans) {
//        m_trans->setAngle(_angle);
//    }
//    //
//    if (m_formate == IMI_PF_GRAY8) {
//
//    } else if (m_formate == IMI_PF_YV12) {
//        m_tex0->setTexData(_srcPtr, width * height);
//        m_tex1->setTexData(_srcPtr + width * height, width * height / 2);
//    } else if (m_formate == IMI_PF_I420) {
////        m_tex0->setTexData(_srcPtr, width * m_height);
////        m_tex1->setTexData(_srcPtr+width*height,width*height/2);
////        m_tex2->setTexData(_srcPtr+width*height,width*height/2);
//    } else if (m_formate == IMI_PF_NV12) {
//        m_tex0->setTexData(_srcPtr, width * height);
//        m_tex1->setTexData(_srcPtr + width * height, width * height / 2);
//    } else if (m_formate == IMI_PF_NV21) {
//        m_tex0->setTexData(_srcPtr, width * height);
//        m_tex1->setTexData(_srcPtr + width * height, width * height / 2);
//    } else if (m_formate == IMI_PF_BGRA) {
//        m_tex0->setTexData(_srcPtr, width*height*4);
//    } else if (m_formate == IMI_PF_RGBA) {
//        m_tex0->setTexData(_srcPtr, width*height*4);
//    } else if (m_formate == IMI_PF_RGB) {
//    }
//    
//   _updateTrans();
 }

void StreamInCore::pushTexture(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID,s32 width,s32 height,s32 pixelFormat,s32 _angle){
//    if(m_trans) {
//        m_trans->setAngle(_angle);
//    }
//    //
//    if (m_formate == IMI_PF_GRAY8) {
//        
//    } else if (m_formate == IMI_PF_YV12) {
//        IMITextureInputTexIDPtr t_tex0 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex0);
//        IMITextureInputTexIDPtr t_tex1 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex1);
//        if (t_tex0 && t_tex1) {
//            t_tex0->setTexID(_tex0ID);
//            t_tex1->setTexID(_tex1ID);
//        }
//    } else if (m_formate == IMI_PF_I420) {
//        IMITextureInputTexIDPtr t_tex0 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex0);
//        IMITextureInputTexIDPtr t_tex1 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex1);
//        IMITextureInputTexIDPtr t_tex2 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex2);
//        if (t_tex0 && t_tex1 && t_tex2) {
//            t_tex0->setTexID(_tex0ID);
//            t_tex1->setTexID(_tex1ID);
//            t_tex2->setTexID(_tex2ID);
//        }
//    } else if (m_formate == IMI_PF_NV12) {
//        IMITextureInputTexIDPtr t_tex0 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex0);
//        IMITextureInputTexIDPtr t_tex1 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex1);
//        if (t_tex0 && t_tex1) {
//            t_tex0->setTexID(_tex0ID);
//            t_tex1->setTexID(_tex1ID);
//        }
//    } else if (m_formate == IMI_PF_NV21) {
//        IMITextureInputTexIDPtr t_tex0 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex0);
//        IMITextureInputTexIDPtr t_tex1 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex1);
//        if (t_tex0 && t_tex1) {
//            t_tex0->setTexID(_tex0ID);
//            t_tex1->setTexID(_tex1ID);
//        }
//    } else if (m_formate == IMI_PF_BGRA) {
//        IMITextureInputTexIDPtr t_tex0 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex0);
//        if (t_tex0) {
//            t_tex0->setTexID(_tex0ID);
//        }
//    } else if (m_formate == IMI_PF_RGBA) {
//        IMITextureInputTexIDPtr t_tex0 = DYN_TO_SHAREPTR(IMITextureInputTexID, m_tex0);
//        if (t_tex0) {
//            t_tex0->setTexID(_tex0ID);
//        }
//    } else if (m_formate == IMI_PF_RGB) {
//    }
//    _updateTrans();
}

void StreamInCore::_updateTrans(){
//    //trans render
//    IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//    IMIRCmdTransGPUPtr transCmd = MakeSharedPtr<IMIRCmdTransGPU>(m_trans);
//    if(t_rs){
//        t_rs->pushRenderCmd(RST_SKY, transCmd);
//    }
}

/*
 */
IMIStreamIn::IMIStreamIn(IMIInstPtr _app)
:IMIProcess(_app){
//    m_streamLock = MakeSharedPtr<IMILock>();
}

IMIStreamIn::~IMIStreamIn() {
//    TEXMAP::Iterator it = m_TexMap.begin();
//    while(it!=m_TexMap.end()){
//        StreamInCorePtr t_streamin = it->data;
//        t_streamin->destroy();
//        it++;
//    }
//    m_TexMap.clear();
//    m_streamLock = nullptr;
}

void IMIStreamIn::createInStream(cptr8 _name,s32 _type,IMI_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, bool _show) {
//    if(!mApp->getRenderer()) {
//        return ;
//    }
//    //默认要摘掉
//    m_streamLock->lock();
//    //IMI_PIC_FORMATE
//    StreamInCorePtr t_incore =MakeSharedPtr<StreamInCore>(mApp);
//    t_incore->init(_w,_h,_formate,_angle,_show);
//    m_TexMap.append(_name,t_incore);
//    m_streamLock->unlock();
}

void IMIStreamIn::createInStream(cptr8 _name,s32 _type,IMI_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle,IMI_TEXIN _tex, bool _show){
//    if(!mApp->getRenderer()) {
//        return ;
//    }
//    //默认要摘掉
//    m_streamLock->lock();
//    //IMI_PIC_FORMATE
//    StreamInCorePtr t_incore =MakeSharedPtr<StreamInCore>(mApp);
//    t_incore->init(_w,_h,_formate,_angle,_show,_tex);
//    m_TexMap.append(_name,t_incore);
//    m_streamLock->unlock();
}

void IMIStreamIn::createInTextureStream(cptr8 _name, u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _type,IMI_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, bool _show) {
//    if(!mApp->getRenderer()) {
//        return ;
//    }
//    //默认要摘掉
//    m_streamLock->lock();
//    //IMI_PIC_FORMATE
//    StreamInCorePtr t_incore =MakeSharedPtr<StreamInCore>(mApp);
//    t_incore->init(_tex0ID, _tex1ID, _tex2ID, _w,_h,_formate,_angle,_show);
//    m_TexMap.append(_name,t_incore);
//    m_streamLock->unlock();
}

void IMIStreamIn::destroyInStream(cptr8 _name){
//    TEXMAP::Iterator it = m_TexMap.find(_name);
//    if(it!=m_TexMap.end()){
//        it->data->destroy();
//        m_TexMap.remove(it);
//    }
}

void IMIStreamIn::active(cptr8 _name) {
//    TEXMAP::Iterator it = m_TexMap.find(_name);
//    if(it!=m_TexMap.end()){
//        StreamInCorePtr t_streamin = it->data;
//        t_streamin->active();
//    }
}

void IMIStreamIn::unactive(cptr8 _name) {
//    TEXMAP::Iterator it = m_TexMap.find(_name);
//    if(it!=m_TexMap.end()){
//        StreamInCorePtr t_streamin = it->data;
//        t_streamin->unactive();
//    }
}
void IMIStreamIn::update(f32 _dt) {
//    //转换更新
//    TEXMAP::Iterator it = m_TexMap.begin();
//    while(it!=m_TexMap.end()){
//        StreamInCorePtr t_streamin = it->data;
//        if(t_streamin) {
//            t_streamin->update(_dt);
//        }
//        it++;
//    }
}

//推送相机数据
void IMIStreamIn::pushStreamData(cptr8 _name,u8* _srcPtr,s32 width,s32 height,s32 pixelFormat,s32 _angle){
//    m_streamLock->lock();
//    TEXMAP::Iterator it = m_TexMap.find(_name);
//    if(it!=m_TexMap.end()){
//        StreamInCorePtr t_streamin = it->data;
//        t_streamin->pushData(_srcPtr,width,height,pixelFormat,_angle);
//    }
//    m_streamLock->unlock();
}

//推送相机纹理数据
void IMIStreamIn::pushTextureStream(cptr8 _name, u32 _tex0ID, u32 _tex1ID, u32 _tex2ID,s32 width,s32 height,s32 pixelFormat,s32 _angle){
//    m_streamLock->lock();
//    TEXMAP::Iterator it = m_TexMap.find(_name);
//    if(it!=m_TexMap.end()){
//        StreamInCorePtr t_streamin = it->data;
//        t_streamin->pushTexture(_tex0ID, _tex1ID, _tex2ID, width, height, pixelFormat, _angle);
//    }
//    m_streamLock->unlock();
}
