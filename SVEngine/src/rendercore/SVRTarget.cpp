//
// SVRTarget.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTarget.h"
#include "SVRFbo.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "SVRenderMgr.h"
#include "SVRenderStream.h"
#include "SVRenderer.h"

using namespace sv;

//
SVRTarget::SVRTarget(SVInstPtr _app)
:SVGBaseEx(_app)
,m_fbo(nullptr){
    m_stream_pool.resize(E_RSM_MAX);
    for(s32 i=0;i<E_RSM_MAX;i++) {
        m_stream_pool[i] = MakeSharedPtr<SVRenderStream>();
    }
}

SVRTarget::~SVRTarget() {
    for(s32 i=0;i<E_RSM_MAX;i++) {
        m_stream_pool[i] = nullptr;
    }
    m_stream_pool.clear();
    m_fbo = nullptr;
}

SVRTargetPtr SVRTarget::share() {
    return std::dynamic_pointer_cast<SVRTarget>( shareObject() );
}

void SVRTarget::setRenderPath() {
    m_stream_quene.push_back(E_RSM_SOLID);
    m_stream_pool[E_RSM_SOLID]->setValid();
}

void SVRTarget::resize(s32 _width,s32 _height) {
    if( m_target_dsp.m_width!=_width ||
        m_target_dsp.m_height!=_height) {
        //
        m_target_dsp.m_width = _width;
        m_target_dsp.m_height = _height;
        //
        SVDispatch::dispatchTargetResize(mApp,share());
    }
}

void SVRTarget::render(SVRendererPtr _renderer) {
    if(m_fbo) {
        _renderer->setCurTarget( share() );
        m_fbo->bind(_renderer);
        for(s32 i=0;i<m_stream_quene.size();i++) {
            s32 t_s_id = m_stream_quene[i];
            if(m_stream_pool[t_s_id]) {
                 m_stream_pool[t_s_id]->render(_renderer,share() );
            }
        }
        m_fbo->unbind(_renderer);
        _renderer->setCurTarget(nullptr);
    }
}

void SVRTarget::pushRenderCommand(SVRenderCmdPtr _rcmd,SV_RSTREAM_TYPE _rstype) {
    //判断restype是否有效
    if( m_stream_pool[_rstype] && m_stream_pool[_rstype]->isValid() ) {
        m_stream_pool[_rstype]->addRenderCmd(_rcmd);
    }
}

void SVRTarget::clearRenderCommand() {
    for(s32 i=0;i<m_stream_quene.size();i++) {
        s32 t_s_id = m_stream_quene[i];
        if(m_stream_pool[t_s_id]) {
            m_stream_pool[t_s_id]->clearRenderCmd();
        }
    }
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

