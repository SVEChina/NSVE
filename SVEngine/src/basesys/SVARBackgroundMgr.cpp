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
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"

using namespace sv;

SVARBackgroundMgr::SVARBackgroundMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_enable = false;
    m_method = 0;
    m_subsysType = 0;
    m_ar_target = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
}

SVARBackgroundMgr::~SVARBackgroundMgr() {
    m_ar_target = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
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
        m_ar_target = t_renderer->createTarget(E_TEX_CAMERA,false,false);
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
        //将AR-相机图片渲染到主目标上
    }
}

//文件纹理方式
void SVARBackgroundMgr::setInputCameraTex(cptr8 _fname) {
    m_method = 1;
    m_tex0 = mApp->getTexMgr()->getTexture(_fname);
}

//数据纹理方式
void SVARBackgroundMgr::setInputCameraTex(SVDataSwapPtr _data,s32 _formate) {
    m_method = 2;
}

//其他方式，例如共享纹理方式
void SVARBackgroundMgr::setInputCameraTex(s32 _texid) {
    m_method = 3;
}
