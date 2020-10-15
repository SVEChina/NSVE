//
// SVResMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVResMgr.h"
#include "SVComData.h"
#include "../mtl/SVShaderMgr.h"
#include "../mtl/SVTexMgr.h"
#include "../event/SVEvent.h"
#include "../rendercore/SVRTargetMgr.h"

using namespace sv;

SVResMgr::SVResMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
    m_common_data = nullptr;
    m_target_mgr = nullptr;
}

SVResMgr::~SVResMgr() {
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
    m_common_data = nullptr;
    m_target_mgr = nullptr;
}

void SVResMgr::init() {
    //引擎需要的静态数据
    m_common_data = MakeSharedPtr<SVComData>(mApp);
    m_common_data->init();
    //纹理管理器初始化
    m_tex_mgr = MakeSharedPtr<SVTexMgr>(mApp);
    m_tex_mgr->init();
    //shader程序初始化
    m_shader_mgr = MakeSharedPtr<SVShaderMgr>(mApp);
    m_shader_mgr->init();
    //target
    m_target_mgr = MakeSharedPtr<SVRTargetMgr>(mApp);
    m_target_mgr->init();
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
    if(m_target_mgr) {
        m_target_mgr->destroy();
    }
}

void SVResMgr::renderCache() {
    
}

//
void SVResMgr::procSysEvent(SVObjectPtr _caller,SVEventPtr _event) {
    if(_event->eventType == EVN_T_SYS_INIT_RENDERER) {
        //渲染器初始化
        SVResMgrPtr t_sender = dynamic_pointer_cast<SVResMgr>(_caller);
        if(t_sender) {
            if(t_sender->m_shader_mgr) {
                t_sender->m_shader_mgr->loadDefault();
            }
            if(t_sender->m_tex_mgr) {
                t_sender->m_tex_mgr->loadDefault();
            }
            if(t_sender->m_target_mgr) {
                t_sender->m_target_mgr->loadDefault();
            }
        }
    }
}
