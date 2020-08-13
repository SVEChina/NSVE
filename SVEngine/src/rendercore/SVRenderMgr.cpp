//
// SVRenderMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderMgr.h"
#include "SVRenderCmd.h"
#include "SVRenderStream.h"
#include "SVRTarget.h"
#include "SVRenderer.h"
#include "../app/SVInst.h"
#include "../env/SVCtxBase.h"
#include "../work/SVTdCore.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtlCore.h"
#include "../basesys/SVConfig.h"
#include "../basesys/SVComData.h"

using namespace sv;

SVRenderMgr::SVRenderMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    m_renderEnv = nullptr;
    m_mainRT = nullptr;
    m_preRT.clear();
    m_afterRT.clear();
    m_renderLock = MakeSharedPtr<SVLockSpin>();
    m_logicLock = MakeSharedPtr<SVLockSpin>();
    m_adaptMode = 0;
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
}

SVRenderMgr::~SVRenderMgr() {
    m_logicLock = nullptr;
    m_renderLock = nullptr;
    m_renderEnv = nullptr;
    m_mainRT = nullptr;
}

void SVRenderMgr::init() {
    m_stream_create = MakeSharedPtr<SVRenderStream>();
    m_stream_destroy = MakeSharedPtr<SVRenderStream>();
}

void SVRenderMgr::destroy() {
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
    clear();
}

void SVRenderMgr::resize(s32 _w,s32 _h) {
    m_renderLock->lock();
    //
    
    //
    m_renderLock->unlock();
}

void SVRenderMgr::setMainRT(SVRTargetPtr _rt) {
    m_mainRT = _rt;
}

SVRTargetPtr SVRenderMgr::getMainRT() {
    return m_mainRT;
}

void SVRenderMgr::addRTarget(SVRTargetPtr _rt,bool _pre) {
    //增加Target
    if(_pre) {
        m_preRT.append(_rt);
    }else{
        m_afterRT.append(_rt);
    }
}

void SVRenderMgr::delRTarget(SVRTargetPtr _rt) {
    //删除RTarget
}

SVRTargetPtr SVRenderMgr::getRTarget(cptr8 _name) {
    return nullptr;
}

//只关心渲染，不应该关心环境的切换 环境放到外面去调用
//这边应该又个渲染路径（RPath）的概念
void SVRenderMgr::render(){
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(!t_renderer){
        return;
    }
    m_renderLock->lock();
    if( mApp->m_ctx && mApp->m_ctx->activeContext(t_renderer) ) {
        //激活,创建流
        if(m_stream_create) {
            m_stream_create->render(t_renderer,m_mainRT);
        }
        //前向RT
        for(s32 i=0;i<m_preRT.size();i++) {
            m_preRT[i]->render( t_renderer);
        }
        //中间RT
        if( m_mainRT ) {
            m_mainRT->render( t_renderer);
        }
        //后向RT
        for(s32 i=0;i<m_afterRT.size();i++) {
            m_afterRT[i]->render(  t_renderer);
        }
        //销毁流
        if(m_stream_destroy) {
            m_stream_destroy->render( t_renderer,m_mainRT);
        }
        //
        mApp->m_ctx->swap(t_renderer);
    }
    m_renderLock->unlock();
}

void SVRenderMgr::_sort() {
    //前向与后向都需要排序
}

void SVRenderMgr::_adapt() {
}

void SVRenderMgr::clear() {
}

//这里相当于准备数据
void SVRenderMgr::swapData(){
}

void SVRenderMgr::pushRCmdCreate(SVRenderCmdPtr _rcmd){
    m_logicLock->lock();
    if(_rcmd && m_stream_create){
        m_stream_create->addRenderCmd(_rcmd);
    }
    m_logicLock->unlock();
}

void SVRenderMgr::pushRCmdDestory(SVRenderCmdPtr _rcmd){
    m_logicLock->lock();
    if(_rcmd && m_stream_destroy){
        m_stream_destroy->addRenderCmd(_rcmd);
    }
    m_logicLock->unlock();
}

void SVRenderMgr::pushRCmd(SVRenderCmdPtr _rcmd,SV_RSTREAM_TYPE _rstype) {
    if(m_mainRT) {
        //这里要传渲染类别啊
        m_mainRT->pushRenderCommand(_rcmd,_rstype);
    }
}
