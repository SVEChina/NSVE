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
#include "../basesys/SVCameraMgr.h"

using namespace sv;

SVRenderMgr::SVRenderMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    m_mainRT = nullptr;
    m_preRT.clear();
    m_afterRT.clear();
    m_render_lock = MakeSharedPtr<SVLockSpin>();
    m_logic_lock = MakeSharedPtr<SVLockSpin>();
    m_adaptMode = 0;
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
}

SVRenderMgr::~SVRenderMgr() {
    m_logic_lock = nullptr;
    m_render_lock = nullptr;
    m_mainRT = nullptr;
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
}

void SVRenderMgr::init() {
    m_stream_create = MakeSharedPtr<SVRenderStream>();
    m_stream_destroy = MakeSharedPtr<SVRenderStream>();
}

void SVRenderMgr::destroy() {
    m_stream_create = nullptr;
    m_stream_destroy = nullptr;
}

void SVRenderMgr::registRenderHelper(SVSysBasePtr _sys) {
    RENDERHELPPOOL::iterator it = m_render_help_pool.begin();
    while (it!=m_render_help_pool.end()) {
        if( (*it) == _sys) {
            return ;
        }
        it++;
    }
    m_render_help_pool.push_back(_sys);
}

void SVRenderMgr::unRegistRenderHelper(SVSysBasePtr _sys) {
    RENDERHELPPOOL::iterator it = m_render_help_pool.begin();
    while (it!=m_render_help_pool.end()) {
        if( (*it) == _sys) {
            m_render_help_pool.erase(it);
            return ;
        }
        it++;
    }
}

void SVRenderMgr::clearRenderHelper() {
    m_render_help_pool.clear();
}

void SVRenderMgr::resize(s32 _w,s32 _h) {
    m_render_lock->lock();
    //自动的target需要resize
    //
    m_render_lock->unlock();
}

void SVRenderMgr::setMainRT(SVRTargetPtr _rt) {
    //设置主RT,绑定主相机
    m_mainRT = _rt;
    if(m_mainRT) {
        m_mainRT->bindCamera(mApp->getCameraMgr()->getMainCamera());
    }
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

void SVRenderMgr::removeRTarget(SVRTargetPtr _rt) {
    //删除RTarget
}

//只关心渲染，不应该关心环境的切换 环境放到外面去调用
//这边应该又个渲染路径（RPath）的概念
void SVRenderMgr::render(){
    SVRendererPtr t_renderer = mApp->getRenderer();
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

void SVRenderMgr::_renderCache() {
    //渲染cache部分，这里最好走回调
    for(s32 i=0;i<m_render_help_pool.size();i++) {
        m_render_help_pool[i]->renderCache();
    }
}

void SVRenderMgr::_sort() {
    //前向与后向都需要排序
}

void SVRenderMgr::_adapt() {
}

void SVRenderMgr::pushRCmdCreate(SVRenderCmdPtr _rcmd){
    m_logic_lock->lock();
    if(_rcmd && m_stream_create){
        m_stream_create->addRenderCmd(_rcmd);
    }
    m_logic_lock->unlock();
}

void SVRenderMgr::pushRCmdDestory(SVRenderCmdPtr _rcmd){
    m_logic_lock->lock();
    if(_rcmd && m_stream_destroy){
        m_stream_destroy->addRenderCmd(_rcmd);
    }
    m_logic_lock->unlock();
}

void SVRenderMgr::pushRCmd(SVRenderCmdPtr _rcmd,SV_RSTREAM _rstype) {
    if(m_mainRT) {
        //这里要传渲染类别啊
        m_mainRT->pushCommand(_rcmd,_rstype);
    }
}
