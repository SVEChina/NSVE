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

using namespace sv;

//
SVRTarget::SVRTarget(SVInstPtr _app)
:SVGBaseEx(_app)
,m_fbo(nullptr){
}

SVRTarget::~SVRTarget() {
    m_fbo = nullptr;
}

void SVRTarget::resize(s32 _width,s32 _height) {
    if( m_target_dsp.m_width!=_width ||
       m_target_dsp.m_height!=_height) {
        //
        m_target_dsp.m_width = _width;
        m_target_dsp.m_height = _height;
        //
        SVDispatch::dispatchTargetResize(mApp,std::dynamic_pointer_cast<SVRTarget>( shareObject() ) );
    }
}

void SVRTarget::render(SVRendererPtr _renderer) {
    if(m_fbo) {
        m_fbo->bind(_renderer);
        for(s32 i=0;i<m_stream_pool.size();i++) {
            m_stream_pool[i]->render(_renderer,std::dynamic_pointer_cast<SVRTarget>(shareObject()));
        }
        m_fbo->unbind(_renderer);
    }
}

void SVRTarget::pushRenderCommand(SVRenderCmdPtr _rcmd,SV_RSTREAM_TYPE _rstype) {
    //命令身上肯定带属性，才能丢到不同的路径当中啊,
    //到底要推入到哪个流中？
    
}

void SVRTarget::clearRenderCommand() {
    
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

