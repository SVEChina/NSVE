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
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTarget.h"

using namespace sv;

SVPass::SVPass(){
    m_surface = MakeSharedPtr<SVSurface>();
}

SVPass::~SVPass(){
    m_surface = nullptr;
}

void SVPass::update(f32 _dt) {
//    //m_target
//    SVRTargetPtr t_aim_target = ;
//    if(t_aim_target) {
//        //t_aim_target->
//    }
}
