//
// SVRenderState.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERSTATE_H
#define SV_RENDERSTATE_H

#include "../base/SVGBase.h"

//渲染状态 主要用于 状态重复调用的控制

namespace sv {
    
    
        
        class SVRenderState: public SVGBaseEx {
        public:
            SVRenderState(SVInstPtr _app);
            
            ~SVRenderState();
            
            virtual void resetState(){};
            
            u32 m_shaderID;
        };
        
    
    
}//!namespace sv




#endif //SV_RENDERSTATE_H
