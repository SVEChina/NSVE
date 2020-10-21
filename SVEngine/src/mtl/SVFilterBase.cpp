//
//  SVFilterBase.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "SVFilterBase.h"
#include "../basesys/SVComData.h"
#include "../app/SVGlobalParam.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRTargetMgr.h"

using namespace sv;

SVFilterBase::SVFilterBase(SVInstPtr _app)
:SVGBaseEx(_app){
    m_name = "SVFilterBase";
    m_mtl = nullptr;
    m_surface = MakeSharedPtr<SVSurface>();
    m_target_quene = E_TEX_END;
    m_target_use = E_TEX_END;
    m_target_swap = E_TEX_END;
//    SV_TEXIN m_target_quene;
//    SV_TEXIN m_target_use;
//    SV_TEXIN m_target_swap;
    m_is_pre = false;
}

SVFilterBase::~SVFilterBase(){
    m_target_quene = E_TEX_END;
    m_target_use = E_TEX_END;
    m_mtl = nullptr;
    m_surface = nullptr;
}

bool SVFilterBase::create(){
    return false;
}

void SVFilterBase::destroy() {
}

void SVFilterBase::setMtl(cptr8 _name) {
    if( mApp->getMtlLib() ) {
        m_mtl = mApp->getMtlLib()->getMtl(_name);
    }
}

void SVFilterBase::update(f32 _dt) {
    //构建use-target
    SVRTargetPtr t_use = mApp->getTargetMgr()->getTarget(m_target_use);
    if(!t_use && m_target_use<E_TEX_END) {
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        t_use = mApp->getTargetMgr()->createTarget(m_target_use, t_w, t_h, false, false);
    }
    if(!t_use) {
        return;
    }
    SVRTargetPtr t_target = mApp->getTargetMgr()->getTarget(m_target_quene);
    if(t_target && m_mtl) {
        m_mtl->update(_dt);
        //产生pass 投递到不同的目标
        SVRCmdPassPtr t_pass = MakeSharedPtr<SVRCmdPass>();
        t_pass->setSwapTarget(m_target_swap);
        t_pass->setUseTarget(m_target_use);
        t_pass->setMesh(mApp->getComData()->screenMesh());
        t_pass->setSurface(m_surface);
        t_pass->setMaterial(m_mtl);
        //
        if(m_is_pre) {
            t_target->pushCommandPre(t_pass); //预处理
        }else{
            t_target->pushCommandAfter(t_pass); //后处理
        }
    }
}

//序列化
void SVFilterBase::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue) {
    
}

void SVFilterBase::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
    
}
