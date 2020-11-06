//
// IMIOpRender.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpRender.h"
#include "../app/IMIInst.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMICameraMgr.h"
#include "../basesys/IMIConfig.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMICameraNode.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRTarget.h"
#include "../rendercore/IMIGL/IMIRendererGL.h"


#ifdef IMI_IOS


#endif

#ifdef IMI_OSX

#endif

#ifdef IMI_ANDROID


#endif

#ifdef IMI_WIN



#endif

using namespace imi;


//重置渲染器内部大小
IMIOpResizeRenderder::IMIOpResizeRenderder(IMIInstPtr _app,s32 _w,s32 _h)
: IMIOpBase(_app)
, m_width(_w)
, m_height(_h){
}

void IMIOpResizeRenderder::_process(float dt) {
    //need write
    IMIRendererPtr t_renderer = mApp->getRenderer();
    if(t_renderer){
        t_renderer->resize(m_width,m_height);
//        IMICameraNodePtr t_camera = mApp->m_global_mgr->m_camera_mgr->getMainCamera();
//        if(t_camera){
//            t_camera->resetSize(m_width, m_height);
//        }
//        IMICameraNodePtr t_uiCamera = mApp->m_global_mgr->m_camera_mgr->getUICamera();
//        if(t_uiCamera){
//            t_uiCamera->resetSize(m_width, m_height);
//        }
    }
}

//设置渲染目标
IMIOpSetRenderTarget::IMIOpSetRenderTarget(IMIInstPtr _app)
        : IMIOpBase(_app) {
}

void IMIOpSetRenderTarget::setTargetParam(s32 _w, s32 _h, u32 _frameID, u32 _colorid, bool _mirror) {
    m_width = _w;
    m_height = _h;
    m_mirror = _mirror;
    m_frameID = _frameID;
    m_colorID = _colorid;
}

void IMIOpSetRenderTarget::_process(f32 dt) {
}

//
IMIOpSetRenderTextureTarget::IMIOpSetRenderTextureTarget(IMIInstPtr _app)
        : IMIOpBase(_app) {
}

void IMIOpSetRenderTextureTarget::setTargetParam(s32 _w, s32 _h, u32 _textureId, bool _mirror) {
    m_width=_w;
    m_height=_h;
    m_mirror = _mirror;
    m_texId=_textureId;
}

void IMIOpSetRenderTextureTarget::_process(f32 dt) {
}

IMIOpSetRenderMirror::IMIOpSetRenderMirror(IMIInstPtr _app)
: IMIOpBase(_app){
    
}

void IMIOpSetRenderMirror::setTargetParam(bool _mirror){
    m_mirror = _mirror;
}

void IMIOpSetRenderMirror::_process(f32 dt){
    mApp->m_config.mirror = m_mirror;
}

