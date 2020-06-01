//
// SVRTechMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTECH_METAL_H
#define SV_RENDERTECH_METAL_H

#include "../SVRTech.h"
#include "SVRenderDeclare.h"
#import <Metal/Metal.h>

namespace sv {

    /*
     render tech metal
     */

    class SVRTechMetal : public SVRTech {
    public:
        SVRTechMetal(SVInstPtr _app);
        
        ~SVRTechMetal();
        
        virtual void build(SVRendererPtr _renderer);
        
        virtual void render(SVRendererPtr _renderer);
        
    protected:
        id<MTLFunction> m_vsf;
        id<MTLFunction> m_gsf;
        id<MTLFunction> m_tscf;
        id<MTLFunction> m_tsdf;
        id<MTLFunction> m_fsf;
        id<MTLFunction> m_csf;
        MTLRenderPipelineDescriptor* m_rp_dsp;
    };


}//!namespace sv


#endif //SV_RENDERTECH_METAL_H
