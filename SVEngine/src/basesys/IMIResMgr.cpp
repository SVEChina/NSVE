//
// IMIResMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIResMgr.h"
#include "IMIComData.h"
#include "../mtl/IMIShaderMgr.h"
#include "../mtl/IMITexMgr.h"
#include "../event/IMIEvent.h"
#include "../rendercore/IMIRTargetMgr.h"

using namespace imi;

IMIResMgr::IMIResMgr(IMIInstPtr _app)
:IMISysBase(_app) {
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
    m_common_data = nullptr;
    m_target_mgr = nullptr;
}

IMIResMgr::~IMIResMgr() {
    m_shader_mgr = nullptr;
    m_tex_mgr = nullptr;
    m_common_data = nullptr;
    m_target_mgr = nullptr;
}

void IMIResMgr::init() {
    //引擎需要的静态数据
    m_common_data = MakeSharedPtr<IMIComData>(mApp);
    m_common_data->init();
    //纹理管理器初始化
    m_tex_mgr = MakeSharedPtr<IMITexMgr>(mApp);
    m_tex_mgr->init();
    //shader程序初始化
    m_shader_mgr = MakeSharedPtr<IMIShaderMgr>(mApp);
    m_shader_mgr->init();
    //target
    m_target_mgr = MakeSharedPtr<IMIRTargetMgr>(mApp);
    m_target_mgr->init();
}

void IMIResMgr::destroy() {
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

void IMIResMgr::renderCache() {
    //shader析构
    if (m_shader_mgr) {
        //m_shader_mgr->();
    }
    if(m_target_mgr) {
        //m_target_mgr->();
    }
}

//
void IMIResMgr::procSysEvent(IMIObjectPtr _caller,IMIEventPtr _event) {
    if(_event->eventType == EVN_T_SYS_INIT_RENDERER) {
        //渲染器初始化
        IMIResMgrPtr t_sender = dynamic_pointer_cast<IMIResMgr>(_caller);
        if(t_sender) {
            if(t_sender->m_common_data) {
                t_sender->m_common_data->loadDefault();
            }
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
