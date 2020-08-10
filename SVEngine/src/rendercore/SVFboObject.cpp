//
// SVFboObject.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFboObject.h"
#include "SVRenderScene.h"
#include "SVRenderMgr.h"
#include "SVGL/SVRTexGL.h"
#if defined(SV_IOS) || defined(SV_OSX)
#include "SVMetal/SVRendererMetal.h"
#endif
#include "SVVulkan/SVRendererVK.h"
#include "SVGL/SVRendererGL.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTexMgr.h"
#include "../app/SVInst.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVCameraMgr.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVCameraNode.h"
//

using namespace sv;

SVFboObject::SVFboObject(SVInstPtr _app)
:SVRRes(_app)
,m_link(false){
}

SVFboObject::~SVFboObject() {
}

void SVFboObject::create(SVRendererPtr _renderer){
    SVRRes::create(_renderer);
    if (m_objFBOPtr) {
        m_objFBOPtr->create(_renderer);
    }
}

void SVFboObject::destroy(SVRendererPtr _renderer) {
    if (m_objFBOPtr) {
        m_objFBOPtr->destroy(_renderer);
    }
    SVRRes::destroy(_renderer);
}

void SVFboObject::refresh() {
//    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
//    if (t_tmp) {
//        t_tmp->refresh();
//    }
}

void SVFboObject::setLink(bool _link) {
    m_link = _link;
}

void SVFboObject::bind() {
}

void SVFboObject::clear(){
}

void SVFboObject::unbind() {
}

u32 SVFboObject::getFboID(){
    return 0;
}

u32 SVFboObject::getWidth(){
    return 0;
}

u32 SVFboObject::getHeight(){
//    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
//    if (t_tmp) {
//        return t_tmp->getHeight();
//    }
    return 0;
}

bool SVFboObject::hasDepth(){
//    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
//    if (t_tmp) {
//        return t_tmp->hasDepth();
//    }
    return 0;
}

bool SVFboObject::hasStencil(){
//    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
//    if (t_tmp) {
//        return t_tmp->hasStencil();
//    }
    return 0;
}

void SVFboObject::setProjMat(FMat4 _mat) {
    m_mat_proj = _mat;
    m_mat_vp = m_mat_proj*m_mat_view;
}

void SVFboObject::setViewMat(FMat4 _view) {
    m_mat_view = _view;
    m_mat_vp = m_mat_proj*m_mat_view;
}
