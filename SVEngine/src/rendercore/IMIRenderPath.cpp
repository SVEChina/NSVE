//
// IMIRenderPath.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRenderPath.h"
#include "../app/IMIInst.h"
#include "../event/IMIEvent.h"
#include "../mtl/IMIShaderMgr.h"
#include "../mtl/IMITexMgr.h"
#include "../rendercore/IMIRTargetMgr.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRTarget.h"

using namespace imi;

IMIRenderPath::IMIRenderPath(IMIInstPtr _app)
:IMISysBase(_app){
    m_prez = false;
    m_has_shadow = false;
    m_target_preZ = nullptr;
}

IMIRenderPath::~IMIRenderPath(){
    m_prez = false;
    m_has_shadow = false;
    m_target_preZ = nullptr;
}

void IMIRenderPath::openPreZ() {
    if(!m_prez) {
        m_prez = true;
        //创建Z-target
        m_target_preZ = mApp->getTargetMgr()->createTarget(E_TEX_DEPTH,false,false);
        if(m_target_preZ) {
            m_target_preZ->pushStreamQuene(E_RSM_SOLID);
            m_target_preZ->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            mApp->getRenderMgr()->addRTarget(m_target_preZ,true);
        }
    }
}

void IMIRenderPath::closePreZ() {
    if(m_prez) {
        m_prez = false;
        mApp->getRenderMgr()->removeRTarget(m_target_preZ);
        m_target_preZ = nullptr;
    }
}

void IMIRenderPath::openShadow() {
    if(!m_has_shadow) {
        m_has_shadow = true;
        //创建Z-target
        m_target_shadow = mApp->getTargetMgr()->createTarget(E_TEX_DEPTH,false,false);
        if(m_target_shadow) {
            m_target_shadow->pushStreamQuene(E_RSM_SOLID);
            m_target_shadow->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            mApp->getRenderMgr()->addRTarget(m_target_shadow,true);
        }
    }
}

void IMIRenderPath::closeShadow() {
    if(m_has_shadow) {
        m_has_shadow = false;
        mApp->getRenderMgr()->removeRTarget(m_target_shadow);
        m_target_shadow = nullptr;
    }
}


//
void IMIRenderPath::procSysEvent(IMIObjectPtr _caller,IMIEventPtr _event) {
    if(_event->eventType == EVN_T_SYS_INIT_RENDERER) {
        //渲染器初始化
        IMIRenderPathPtr t_sender = std::dynamic_pointer_cast<IMIRenderPath>(_caller);
        if(t_sender) {
            t_sender->openPreZ();
        }
    }
}
