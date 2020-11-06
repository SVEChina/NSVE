//
// IMIRenderMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRenderMgr.h"
#include "IMIRenderCmd.h"
#include "IMIRenderStream.h"
#include "IMIRTarget.h"
#include "IMIRenderer.h"
#include "../app/IMIInst.h"
#include "../env/IMICtxBase.h"
#include "../work/IMITdCore.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIMtlCore.h"
#include "../basesys/IMIConfig.h"
#include "../basesys/IMIComData.h"
#include "../basesys/IMICameraMgr.h"

using namespace imi;

IMIRenderMgr::IMIRenderMgr(IMIInstPtr _app)
:IMIGBaseEx(_app) {
    m_mainRT = nullptr;
    m_preRT.clear();
    m_afterRT.clear();
    m_render_lock = MakeSharedPtr<IMILockSpin>();
    m_logic_lock = MakeSharedPtr<IMILockSpin>();
    m_adaptMode = 0;
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
}

IMIRenderMgr::~IMIRenderMgr() {
    m_logic_lock = nullptr;
    m_render_lock = nullptr;
    m_mainRT = nullptr;
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
}

void IMIRenderMgr::init() {
    m_stream_create = MakeSharedPtr<IMIRenderStream>();
    m_stream_destroy = MakeSharedPtr<IMIRenderStream>();
}

void IMIRenderMgr::destroy() {
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
}

void IMIRenderMgr::registRenderHelper(IMISysBasePtr _sys) {
    RENDERHELPPOOL::iterator it = m_render_help_pool.begin();
    while (it!=m_render_help_pool.end()) {
        if( (*it) == _sys) {
            return ;
        }
        it++;
    }
    m_render_help_pool.push_back(_sys);
}

void IMIRenderMgr::unRegistRenderHelper(IMISysBasePtr _sys) {
    RENDERHELPPOOL::iterator it = m_render_help_pool.begin();
    while (it!=m_render_help_pool.end()) {
        if( (*it) == _sys) {
            m_render_help_pool.erase(it);
            return ;
        }
        it++;
    }
}

void IMIRenderMgr::clearRenderHelper() {
    m_render_help_pool.clear();
}

void IMIRenderMgr::resize(s32 _w,s32 _h) {
    m_render_lock->lock();
    //自动的target需要resize
    //
    m_render_lock->unlock();
}

void IMIRenderMgr::setMainRT(IMIRTargetPtr _rt) {
    //设置主RT,绑定主相机
    m_mainRT = _rt;
    if(m_mainRT) {
        m_mainRT->bindCamera(mApp->getCameraMgr()->getMainCamera());
    }
}

IMIRTargetPtr IMIRenderMgr::getMainRT() {
    return m_mainRT;
}

void IMIRenderMgr::addRTarget(IMIRTargetPtr _rt,bool _pre) {
    //增加Target
    if(_pre) {
        m_preRT.append(_rt);
    }else{
        m_afterRT.append(_rt);
    }
}

void IMIRenderMgr::removeRTarget(IMIRTargetPtr _rt) {
    //删除RTarget
}

//只关心渲染，不应该关心环境的切换 环境放到外面去调用
//这边应该又个渲染路径（RPath）的概念
void IMIRenderMgr::render(){
    IMIRendererPtr t_renderer = mApp->getRenderer();
    if(!t_renderer){
        return;
    }
    m_render_lock->lock();
    if( mApp->m_ctx && mApp->m_ctx->activeContext(t_renderer) ) {
        //渲染cache部分
        _renderCache();
        //cmd-创建流
        if(m_stream_create) {
            m_stream_create->render(t_renderer,m_mainRT);
        }
        //前向RT
        for(s32 i=0;i<m_preRT.size();i++) {
            m_preRT[i]->render(t_renderer);
        }
        //主RT
        if( m_mainRT ) {
            m_mainRT->render(t_renderer);
        }
        //后向RT
        for(s32 i=0;i<m_afterRT.size();i++) {
            m_afterRT[i]->render(t_renderer);
        }
        //cmd-销毁流
        if(m_stream_destroy) {
            m_stream_destroy->render(t_renderer,m_mainRT);
        }
        //交换
        mApp->m_ctx->swap(t_renderer);
    }
    m_render_lock->unlock();
}

void IMIRenderMgr::_renderCache() {
    //渲染cache部分，这里最好走回调
    for(s32 i=0;i<m_render_help_pool.size();i++) {
        m_render_help_pool[i]->renderCache();
    }
}

void IMIRenderMgr::_sort() {
    //前向与后向都需要排序
}

void IMIRenderMgr::_adapt() {
}

void IMIRenderMgr::pushRCmdCreate(IMIRenderCmdPtr _rcmd){
    m_logic_lock->lock();
    if(_rcmd && m_stream_create){
        m_stream_create->addRenderCmd(_rcmd);
    }
    m_logic_lock->unlock();
}

void IMIRenderMgr::pushRCmdDestory(IMIRenderCmdPtr _rcmd){
    m_logic_lock->lock();
    if(_rcmd && m_stream_destroy){
        m_stream_destroy->addRenderCmd(_rcmd);
    }
    m_logic_lock->unlock();
}

void IMIRenderMgr::pushRCmd(IMIRenderCmdPtr _rcmd,IMI_RSTREAM _rstype) {
    if(m_mainRT) {
        //这里要传渲染类别啊
        m_mainRT->pushCommand(_rcmd,_rstype);
    }
}
