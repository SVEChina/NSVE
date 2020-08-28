//
//  SVFilterBase.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "SVFilterBase.h"
#include "../basesys/SVComData.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTarget.h"

using namespace sv;

SVFilterBase::SVFilterBase(SVInstPtr _app)
:SVGBaseEx(_app){
    m_name = "SVFilterBase";
    m_mtl = nullptr;
    m_surface = MakeSharedPtr<SVSurface>();
    m_target_tex = E_TEX_END;
    m_target_tex_help = E_TEX_END;
    m_is_pre = false;
}

SVFilterBase::~SVFilterBase(){
    m_target_tex = E_TEX_END;
    m_target_tex_help = E_TEX_END;
    m_mtl = nullptr;
    m_surface = nullptr;
}

bool SVFilterBase::create(){
    return false;
}

void SVFilterBase::destroy() {
}

void SVFilterBase::update(f32 _dt) {
    SVRTargetPtr t_target = mApp->getRenderer()->getTarget(m_target_tex);
    if(t_target && m_mtl) {
        //辅助目标
        SVRTargetPtr t_help = mApp->getRenderer()->getTarget(m_target_tex_help);
        if(!t_help && m_target_tex_help<E_TEX_END) {
            s32 t_w = t_target->getTargetDsp()->m_width;
            s32 t_h = t_target->getTargetDsp()->m_height;
            t_help = mApp->getRenderer()->createTarget(m_target_tex_help, t_w, t_h, false, false);
        }
        if(!t_help) {
            return;
        }
        //产生pass 投递到不同的目标
        SVRCmdPassPtr t_pass = MakeSharedPtr<SVRCmdPass>();
        t_pass->setTarget(m_target_tex);
        t_pass->setHelpTarget(m_target_tex_help);
        t_pass->setMesh(mApp->getComData()->screenMesh());
        t_pass->setSurface(m_surface);
        t_pass->setMaterial(m_mtl);
        if(m_is_pre) {
            //预处理
            t_target->pushCommandPre(t_pass);
        }else{
            //后处理
            t_target->pushCommandAfter(t_pass);
        }
    }
}

//序列化
void SVFilterBase::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue) {
    
}

void SVFilterBase::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
    
}
