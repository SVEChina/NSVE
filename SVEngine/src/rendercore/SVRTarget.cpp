//
// SVRTarget.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTarget.h"
#include "SVRFbo.h"
#include "../app/SVInst.h"
#include "SVRenderMgr.h"

using namespace sv;

//
SVRTarget::SVRTarget(SVInstPtr _app)
:SVGBaseEx(_app)
,m_fbo(nullptr){
}

SVRTarget::~SVRTarget() {
    m_fbo = nullptr;
}

void SVRTarget::render(SVRendererPtr _renderer) {
    if(m_fbo) {
        m_fbo->bind(_renderer);
        //设置目标
        _preRender(_renderer);
        //渲染
        _render(_renderer);
        //解锁目标
        _afterRender(_renderer);
        //
        m_fbo->unbind(_renderer);
    }
}

void SVRTarget::_preRender(SVRendererPtr _renderer) {
}

void SVRTarget::_render(SVRendererPtr _renderer) {
    //
}

void SVRTarget::_afterRender(SVRendererPtr _renderer) {
    //
}

void SVRTarget::bindRes(SVRFboPtr _res) {
    m_fbo = _res;
}

void SVRTarget::unbindRes() {
    m_fbo = nullptr;
}

SVRFboPtr SVRTarget::getResFbo() {
    return m_fbo;
}

