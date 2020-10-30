//
// SVRenderPath.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderPath.h"
#include "../app/SVInst.h"
#include "../event/SVEvent.h"
#include "../mtl/SVShaderMgr.h"
#include "../mtl/SVTexMgr.h"
#include "../rendercore/SVRTargetMgr.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRTarget.h"

using namespace sv;

SVRenderPath::SVRenderPath(SVInstPtr _app)
:SVSysBase(_app){
    m_prez = false;
    m_target_preZ = nullptr;
}

SVRenderPath::~SVRenderPath(){
    m_target_preZ = nullptr;
}

void SVRenderPath::openPreZ() {
    if(!m_prez) {
        m_prez = true;
        //创建Z-target
        m_target_preZ = mApp->getTargetMgr()->createTarget(E_TEX_DEPTH,true,true);
        if(m_target_preZ) {
            m_target_preZ->pushStreamQuene(E_RSM_SOLID);
            m_target_preZ->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            mApp->getRenderMgr()->addRTarget(m_target_preZ,true);
        }
    }
}

void SVRenderPath::closePreZ() {
    if(m_prez) {
        m_prez = false;
        mApp->getRenderMgr()->removeRTarget(m_target_preZ);
        m_target_preZ = nullptr;
    }
}


//
void SVRenderPath::procSysEvent(SVObjectPtr _caller,SVEventPtr _event) {
    if(_event->eventType == EVN_T_SYS_INIT_RENDERER) {
        //渲染器初始化
        SVRenderPathPtr t_sender = std::dynamic_pointer_cast<SVRenderPath>(_caller);
        if(t_sender) {
            t_sender->openPreZ();
        }
    }
}
