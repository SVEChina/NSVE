//
// IMILightMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMILightSys.h"
#include "../work/IMITdCore.h"
#include "../basesys/IMICameraNode.h"

using namespace imi;

IMILightSys::IMILightSys(IMIInstPtr _app)
:IMISysBase(_app) {
    m_subsysType = 7;
}

IMILightSys::~IMILightSys() {
}

void IMILightSys::init() {
    m_g_ambient = FVec3(0.2f,0.2f,0.2f);
    m_g_diffuse = FVec3(0.6f,0.6f,0.6f);
    m_g_specular = FVec3(1.0f,1.0f,1.0f);
    m_g_direction = FVec3(1.0f,1.0f,0.0f);
    m_g_diffuse_sc = 1.0f;
    s32 m_sw = mApp->m_global_param.sv_width;
    s32 m_sh = mApp->m_global_param.sv_height;
    m_pLightCamera = MakeSharedPtr<IMICameraNode>(mApp);
    //m_pLightCamera->resetSize(m_sw,m_sh);
//    m_uiLock = MakeSharedPtr<IMILock>();
//    m_pUIRoot = MakeSharedPtr<IMINode>(mApp);
}

IMICameraNodePtr IMILightSys::getCamera(){
    return m_pLightCamera;
}

void IMILightSys::destroy() {
    //m_pUIRoot = nullptr;
    m_pLightCamera = nullptr;
}

void IMILightSys::update(f32 dt) {
     m_pLightCamera->update(dt);
}
