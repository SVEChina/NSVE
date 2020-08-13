//
// SVPass.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVPass.h"
#include "../app/SVInst.h"
#include "../basesys/SVComData.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVSurface.h"
#include "../mtl/SVMtlLib.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRenderCmd.h"

using namespace sv;

SVPass::SVPass(SVInstPtr _inst)
:SVGBaseEx(_inst){
    m_surface = MakeSharedPtr<SVSurface>();
}

SVPass::~SVPass(){
    m_surface = nullptr;
}

void SVPass::update(f32 _dt) {
    SVRTargetPtr t_target = nullptr; //m_target
    SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl(m_mtl_name.c_str());
    if(t_mtl && t_target) {
        SVRCmdPassPtr t_r_pass = MakeSharedPtr<SVRCmdPass>();
        t_r_pass->setMesh( mApp->getComData()->screenMesh() );
        t_r_pass->setMaterial(t_mtl);
        t_r_pass->setSurface( m_surface );
        t_r_pass->setTarget(t_target);
        //mApp->getRenderMgr()->
    }
}
