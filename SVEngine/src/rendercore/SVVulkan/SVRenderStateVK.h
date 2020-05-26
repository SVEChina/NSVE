//
// SVRenderStateVK.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERSTATE_VK_H
#define SV_RENDERSTATE_VK_H

#include "../SVRenderState.h"
#include "../../core/SVVertDef.h"

//渲染状态 主要用于 状态重复调用的控制

namespace sv {
    
    
        
        class SVRenderStateVK : public SVRenderState {
        public:
            SVRenderStateVK(SVInst* _app);
            
            ~SVRenderStateVK();
            
            
        };
        
    
    
}//!namespace sv




#endif //SV_RENDERSTATE_VK_H
