//
// SVRTarget.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTarget.h"
#include "SVRenderScene.h"
#include "../app/SVInst.h"
#include "SVRenderMgr.h"
#include "SVGL/SVRResGL.h"
#include "SVGL/SVRendererGL.h"
#if defined(SV_IOS) || defined(SV_OSX)
#include "SVMetal/SVRendererMetal.h"
#endif
#include "SVVulkan/SVRendererVK.h"

using namespace sv;

//
SVRTarget::SVRTarget(SVInstPtr _app)
:SVGBaseEx(_app)
,m_order(0){
}

SVRTarget::~SVRTarget() {
}

//void SVRTarget::create(SVRendererPtr _renderer) {
////    SVRObjBase::create(_renderer);
////    SVRendererPtr t_renderBasePtr = mApp->getRenderer();
////    SVRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<SVRendererGL>(t_renderBasePtr);
////    if (t_renderGLPtr) {
////        //渲染器类型E_RENDERER_GLES,
////        m_objFBOPtr = MakeSharedPtr<SVResGLRenderTarget>(mApp, m_w, m_h, m_depth, m_stencil);
////
////    }
////    SVRendererVKPtr t_rendeVKPtr = std::dynamic_pointer_cast<SVRendererVK>(t_renderBasePtr);
////    if (t_rendeVKPtr) {
////        //渲染器类型E_RENDERER_VUNKAN,
////
////    }
//////    SVRendererMetalPtr t_rendeMetalPtr = std::dynamic_pointer_cast<SVRendererMetal>(
//////            t_renderBasePtr);
//////    if (t_rendeMetalPtr) {
//////        //渲染器类型E_RENDERER_METAL,
//////    }
////    if (m_objFBOPtr) {
////        m_objFBOPtr->create(_renderer);
////    }
//}
//
//void SVRTarget::destroy(SVRendererPtr _renderer) {
//////    if (m_objFBOPtr) {
//////        m_objFBOPtr->destroy(_renderer);
//////    }
////    SVRObjBase::destroy(_renderer);
//}

void SVRTarget::render() {
    //设置目标
    _preRender();
    //渲染
    _render();
    //解锁目标
    _afterRender();
}

void SVRTarget::_preRender() {
    
}

void SVRTarget::_render() {
    
}

void SVRTarget::_afterRender() {
    
}

