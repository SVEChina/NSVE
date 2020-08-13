//
// SVARBackgroundMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVARBackgroundMgr.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../work/SVTdCore.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTarget.h"

using namespace sv;

SVARBackgroundMgr::SVARBackgroundMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_enable = false;
    m_subsysType = 0;
    m_ar_target = nullptr;
}

SVARBackgroundMgr::~SVARBackgroundMgr() {
    m_ar_target = nullptr;
}

//
void SVARBackgroundMgr::init() {
}

//
void SVARBackgroundMgr::destroy() {
}

//
void SVARBackgroundMgr::enable() {
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(t_renderer) {
        m_ar_target = t_renderer->createTarget(E_TEX_CAMERA);
        //设置渲染路径
        //t_target->setRenderPath();
        //推送到前向渲染
        mApp->getRenderMgr()->addRTarget(m_ar_target,true);
        m_enable = true;
    }
}

//
void SVARBackgroundMgr::disable() {
    if(m_enable) {
        if(m_ar_target) {
            m_ar_target = nullptr;
        }
        m_enable = false;
    }
}

//
void SVARBackgroundMgr::update(f32 dt) {
    if(m_ar_target) {
        //将相机图片推送到主渲染
        
    }
}
