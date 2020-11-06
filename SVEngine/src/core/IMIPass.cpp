//
// IMIPass.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIPass.h"
#include "../app/IMIInst.h"
#include "../basesys/IMIComData.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMISurface.h"
#include "../mtl/IMIMtlLib.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRTarget.h"
#include "../rendercore/IMIRenderCmd.h"

using namespace imi;

IMIPass::IMIPass(IMIInstPtr _inst)
:IMIGBaseEx(_inst){
    m_target = nullptr;
    m_surface = MakeSharedPtr<IMISurface>();
}

IMIPass::~IMIPass(){
    m_target = nullptr;
    m_surface = nullptr;
}

void IMIPass::bindTarget(IMIRTargetPtr _target) {
    m_target = _target;
}

void IMIPass::unbindTarget() {
    m_target = nullptr;
}

void IMIPass::update(f32 _dt) {
    IMIMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl(m_mtl_name.c_str());
    if(t_mtl && m_target) {
        t_mtl->update(_dt);
        IMIRCmdPassPtr t_r_pass = MakeSharedPtr<IMIRCmdPass>();
        t_r_pass->setMesh( mApp->getComData()->screenMesh() );
        t_r_pass->setMaterial(t_mtl);
        t_r_pass->setSurface( m_surface );
        //t_r_pass->setTarget(m_target);
    }
}
