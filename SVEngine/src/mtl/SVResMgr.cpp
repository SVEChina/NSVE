//
// SVResMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVResMgr.h"
#include "SVShaderMgr.h"
#include "SVTexMgr.h"
#include "../event/SVEvent.h"

using namespace sv;

SVResMgr::SVResMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
}

SVResMgr::~SVResMgr() {
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
}

void SVResMgr::init() {
    //纹理管理器初始化
    m_tex_mgr = MakeSharedPtr<SVTexMgr>(mApp);
    m_tex_mgr->init();
    //shader程序初始化
    m_shader_mgr = MakeSharedPtr<SVShaderMgr>(mApp);
    m_shader_mgr->init();
}

void SVResMgr::destroy() {
    //纹理析够 析构都要用到渲染模块
    if (m_tex_mgr) {
        m_tex_mgr->destroy();
    }
    //shader析构
    if (m_shader_mgr) {
        m_shader_mgr->destroy();
    }
}

bool SVResMgr::procEvent(SVEventPtr _event) {
    if(_event && _event->eventType>EVN_T_SYS_BEGIN && _event->eventType<EVN_T_SYS_END ) {
        if(_event->eventType == EVN_T_SYS_INIT_RENDERER) {
            //加载默认的资源
            if(m_tex_mgr) {
                m_tex_mgr->loadDefault();
            }
            if(m_shader_mgr) {
                m_shader_mgr->loadDefault();
            }
        }
    }
    return true;
}
