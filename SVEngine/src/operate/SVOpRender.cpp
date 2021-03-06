//
// SVOpRender.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVOpRender.h"
#include "../app/SVInst.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVCameraMgr.h"
#include "../basesys/SVConfig.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVCameraNode.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVGL/SVRendererGL.h"
#include "../rendercore/SVVulkan/SVRendererVK.h"

#if defined(SV_IOS) || defined(SV_OSX)
#include "../rendercore/SVMetal/SVRendererMetal.h"
#endif


#ifdef SV_IOS


#endif

#ifdef SV_OSX

#endif

#ifdef SV_ANDROID


#endif

#ifdef SV_WIN



#endif

using namespace sv;


//重置渲染器内部大小
SVOpResizeRenderder::SVOpResizeRenderder(SVInstPtr _app,s32 _w,s32 _h)
: SVOpBase(_app)
, m_width(_w)
, m_height(_h){
}

void SVOpResizeRenderder::_process(float dt) {
    //need write
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(t_renderer){
        t_renderer->resize(m_width,m_height);
//        SVCameraNodePtr t_camera = mApp->m_global_mgr->m_camera_mgr->getMainCamera();
//        if(t_camera){
//            t_camera->resetSize(m_width, m_height);
//        }
//        SVCameraNodePtr t_uiCamera = mApp->m_global_mgr->m_camera_mgr->getUICamera();
//        if(t_uiCamera){
//            t_uiCamera->resetSize(m_width, m_height);
//        }
    }
}

//设置渲染目标
SVOpSetRenderTarget::SVOpSetRenderTarget(SVInstPtr _app)
        : SVOpBase(_app) {
}

void SVOpSetRenderTarget::setTargetParam(s32 _w, s32 _h, u32 _frameID, u32 _colorid, bool _mirror) {
    m_width = _w;
    m_height = _h;
    m_mirror = _mirror;
    m_frameID = _frameID;
    m_colorID = _colorid;
}

void SVOpSetRenderTarget::_process(f32 dt) {
}

//
SVOpSetRenderTextureTarget::SVOpSetRenderTextureTarget(SVInstPtr _app)
        : SVOpBase(_app) {
}

void SVOpSetRenderTextureTarget::setTargetParam(s32 _w, s32 _h, u32 _textureId, bool _mirror) {
    m_width=_w;
    m_height=_h;
    m_mirror = _mirror;
    m_texId=_textureId;
}

void SVOpSetRenderTextureTarget::_process(f32 dt) {
}

SVOpSetRenderMirror::SVOpSetRenderMirror(SVInstPtr _app)
: SVOpBase(_app){
    
}

void SVOpSetRenderMirror::setTargetParam(bool _mirror){
    m_mirror = _mirror;
}

void SVOpSetRenderMirror::_process(f32 dt){
    mApp->m_config.mirror = m_mirror;
}

