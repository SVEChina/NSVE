//
// IMIRTarget.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRTarget.h"
#include "IMIRFbo.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../basesys/IMICameraNode.h"
#include "IMIRenderMgr.h"
#include "IMIRenderStream.h"
#include "IMIRenderer.h"

using namespace imi;

//
IMIRTarget::IMIRTarget(IMIInstPtr _app,IMI_TEXIN _id)
:IMIGBaseEx(_app)
,m_target_id(_id)
,m_rfbo_id(-1)
,m_camera(nullptr){
    m_auto = true;
    m_cmdNum = 0;
    m_stream_pool.resize(E_RSM_MAX);
    for(s32 i=0;i<E_RSM_MAX;i++) {
        m_stream_pool[i] = MakeSharedPtr<IMIRenderStream>();
        m_stream_pool[i]->setValid(false);
    }
    m_stream_pre = MakeSharedPtr<IMIRenderStream>();
    m_stream_after = MakeSharedPtr<IMIRenderStream>();
}

IMIRTarget::~IMIRTarget() {
    m_stream_pre = nullptr;
    m_stream_after = nullptr;
    for(s32 i=0;i<E_RSM_MAX;i++) {
        m_stream_pool[i] = nullptr;
    }
    m_stream_pool.clear();
    m_camera = nullptr;
    m_rfbo_id = -1;
}

IMIRTargetPtr IMIRTarget::share() {
    return std::dynamic_pointer_cast<IMIRTarget>( shareObject() );
}

void IMIRTarget::dispatch() {
    IMIDispatch::dispatchTargetCreate(mApp, share());
}

void IMIRTarget::setClearColor(f32 _r,f32 _g,f32 _b,f32 _a) {
    m_target_dsp.m_color_r = _r;
    m_target_dsp.m_color_g = _g;
    m_target_dsp.m_color_b = _b;
    m_target_dsp.m_color_a = _a;
}

void IMIRTarget::setDepth(f32 _value) {
    m_target_dsp.m_depth_value = _value;
}

void IMIRTarget::setStencil(s32 _value) {
    m_target_dsp.m_stencil_value = _value;
}

void IMIRTarget::resize(s32 _width,s32 _height) {
    if(m_auto) {
        if( m_target_dsp.m_width!=_width ||
            m_target_dsp.m_height!=_height) {
            m_target_dsp.m_width = _width;
            m_target_dsp.m_height = _height;
            IMIDispatch::dispatchTargetResize(mApp,share());
        }
    }
}

void IMIRTarget::render(IMIRendererPtr _renderer) {
    if( m_rfbo_id>=0 ) {
        _renderer->setCurTarget( share() );
        //
        if(m_stream_pre) {
           m_stream_pre->render(_renderer,share());
        }
        if(m_cmdNum>0) {
            _renderer->bindTarget(m_rfbo_id);
            for(s32 i=0;i<m_stream_quene.size();i++) {
                s32 t_s_id = m_stream_quene[i];
                if(m_stream_pool[t_s_id]) {
                     m_stream_pool[t_s_id]->render(_renderer,share() );
                }
            }
            _renderer->unbindTarget(m_rfbo_id);
            m_cmdNum = 0;
        }
        //
        if(m_stream_after) {
           m_stream_after->render(_renderer,share());
        }
        _renderer->setCurTarget(nullptr);
    }
}

//推送流序
void IMIRTarget::pushStreamQuene(IMI_RSTREAM _rstream) {
    for(s32 i=0;i<m_stream_quene.size();i++) {
        if(m_stream_quene[i] == _rstream) {
            return ;    // 防止重复推入
        }
    }
    if(_rstream>=0 && _rstream<E_RSM_MAX) {
        m_stream_quene.push_back(_rstream);
        m_stream_pool[_rstream]->setValid(true);
    }
}

//清理流序
void IMIRTarget::clearStreamQuene() {
    for(s32 i=0;i<E_RSM_MAX;i++) {
        m_stream_pool[i] = MakeSharedPtr<IMIRenderStream>();
        m_stream_pool[i]->setValid(false);
    }
    m_stream_quene.clear();
}

void IMIRTarget::pushCommandPre(IMIRenderCmdPtr _rcmd) {
    if(m_stream_pre && _rcmd) {
        m_stream_pre->addRenderCmd(_rcmd);
    }
}

void IMIRTarget::pushCommandAfter(IMIRenderCmdPtr _rcmd) {
    if(m_stream_after && _rcmd) {
        m_stream_after->addRenderCmd(_rcmd);
    }
}

void IMIRTarget::pushCommand(IMIRenderCmdPtr _rcmd,IMI_RSTREAM _rstype) {
    //判断restype是否有效
    if( m_stream_pool[_rstype] && m_stream_pool[_rstype]->isValid() ) {
        m_stream_pool[_rstype]->addRenderCmd(_rcmd);
        m_cmdNum++;
    }
}

void IMIRTarget::clearCommand() {
    if(m_stream_pre) {
        m_stream_pre->clearRenderCmd();
    }
    if(m_stream_after) {
        m_stream_pre->clearRenderCmd();
    }
    for(s32 i=0;i<m_stream_quene.size();i++) {
        s32 t_s_id = m_stream_quene[i];
        if(m_stream_pool[t_s_id]) {
            m_stream_pool[t_s_id]->clearRenderCmd();
        }
    }
}

void IMIRTarget::bindCamera(IMICameraNodePtr _camera) {
    m_camera = _camera;
    if(m_camera) {
        m_camera->setSize(m_target_dsp.m_width, m_target_dsp.m_height);
    }
}

FMat4 IMIRTarget::viewMat() {
    FMat4 t_mat;
    if(m_camera) {
        t_mat = m_camera->viewMat();
    }else{
        t_mat.setIdentity();
    }
    return t_mat;
}

FMat4 IMIRTarget::projMat(){
    FMat4 t_mat;
    if(m_camera) {
        t_mat = m_camera->projectMat();
    }else{
        t_mat.setIdentity();
    }
    return t_mat;
}

FMat4 IMIRTarget::vpMat(){
    FMat4 t_mat;
    if(m_camera) {
        t_mat = m_camera->vpMat();
    }else{
        t_mat.setIdentity();
    }
    return t_mat;
}

void IMIRTarget::bindRes(s32 _instid) {
    m_rfbo_id = _instid;
}

void IMIRTarget::unbindRes() {
    m_rfbo_id = -1;
}

IMIRFboPtr IMIRTarget::getResFbo() {
    if( mApp->getRenderer() ) {
        return mApp->getRenderer()->getResFbo(m_rfbo_id);
    }
    return nullptr;
}
