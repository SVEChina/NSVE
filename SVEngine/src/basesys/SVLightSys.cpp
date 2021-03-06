//
// SVLightMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVLightSys.h"
#include "../work/SVTdCore.h"
#include "../basesys/SVCameraNode.h"

using namespace sv;

SVLightSys::SVLightSys(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 7;
}

SVLightSys::~SVLightSys() {
}

void SVLightSys::init() {
    m_g_ambient = FVec3(0.2f,0.2f,0.2f);
    m_g_diffuse = FVec3(0.6f,0.6f,0.6f);
    m_g_specular = FVec3(1.0f,1.0f,1.0f);
    m_g_direction = FVec3(1.0f,1.0f,0.0f);
    m_g_diffuse_sc = 1.0f;
    s32 m_sw = mApp->m_global_param.sv_width;
    s32 m_sh = mApp->m_global_param.sv_height;
    m_pLightCamera = MakeSharedPtr<SVCameraNode>(mApp);
    //m_pLightCamera->resetSize(m_sw,m_sh);
//    m_uiLock = MakeSharedPtr<SVLock>();
//    m_pUIRoot = MakeSharedPtr<SVNode>(mApp);
}

SVCameraNodePtr SVLightSys::getCamera(){
    return m_pLightCamera;
}

void SVLightSys::destroy() {
    //m_pUIRoot = nullptr;
    m_pLightCamera = nullptr;
}

void SVLightSys::update(f32 dt) {
     m_pLightCamera->update(dt);
}
