//
// SVPass.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVPass.h"
#include "../app/SVInst.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVSurface.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRenderCmd.h"

using namespace sv;

SVPass::SVPass(){
    m_surface = MakeSharedPtr<SVSurface>();
}

SVPass::~SVPass(){
    m_surface = nullptr;
}

void SVPass::update(f32 _dt) {
    SVRCmdPassPtr t_r_pass = MakeSharedPtr<SVRCmdPass>();
    //t_r_pass->setMtl();
    //t_r_pass->setMesh();
    //t_r_pass->setSurface();
    //t_r_pass->setTarget();//SVRTargetPtr _target
    //
    //mApp->getRenderMgr()->
}
