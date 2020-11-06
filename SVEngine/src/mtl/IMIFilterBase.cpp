//
//  IMIFilterBase.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "IMIFilterBase.h"
#include "../basesys/IMIComData.h"
#include "../app/IMIGlobalParam.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRTarget.h"
#include "../rendercore/IMIRTargetMgr.h"

using namespace imi;

IMIFilterBase::IMIFilterBase(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_name = "IMIFilterBase";
    m_mtl = nullptr;
    m_surface = MakeSharedPtr<IMISurface>();
    m_target_quene = E_TEX_END;
    m_target_use = E_TEX_END;
    m_target_swap = E_TEX_END;
//    IMI_TEXIN m_target_quene;
//    IMI_TEXIN m_target_use;
//    IMI_TEXIN m_target_swap;
    m_is_pre = false;
}

IMIFilterBase::~IMIFilterBase(){
    m_target_quene = E_TEX_END;
    m_target_use = E_TEX_END;
    m_mtl = nullptr;
    m_surface = nullptr;
}

bool IMIFilterBase::create(){
    return false;
}

void IMIFilterBase::destroy() {
}

void IMIFilterBase::setMtl(cptr8 _name) {
    if( mApp->getMtlLib() ) {
        m_mtl = mApp->getMtlLib()->getMtl(_name);
    }
}

void IMIFilterBase::update(f32 _dt) {
    //构建use-target
    IMIRTargetPtr t_use = mApp->getTargetMgr()->getTarget(m_target_use);
    if(!t_use && m_target_use<E_TEX_END) {
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        t_use = mApp->getTargetMgr()->createTarget(m_target_use, t_w, t_h, false, false);
    }
    if(!t_use) {
        return;
    }
    IMIRTargetPtr t_target = mApp->getTargetMgr()->getTarget(m_target_quene);
    if(t_target && m_mtl) {
        m_mtl->update(_dt);
        //产生pass投递到不同的目标
        IMIRCmdPassPtr t_pass = MakeSharedPtr<IMIRCmdPass>();
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
void IMIFilterBase::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue) {
    
}

void IMIFilterBase::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
    
}
