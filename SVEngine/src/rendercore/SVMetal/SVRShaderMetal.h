//
// SVRShaderMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SHADER_METAL_H
#define SV_SHADER_METAL_H

#include "../SVRShader.h"
#include "SVRenderDeclare.h"
#import <Metal/Metal.h>

namespace sv {

    /*
     render tech metal
     */

    class SVRShaderMetal : public SVRShader {
    public:
        SVRShaderMetal(SVInstPtr _app);
        
        ~SVRShaderMetal();
        
        virtual void create(SVRendererPtr _renderer);
                   
        virtual void destroy(SVRendererPtr _renderer);
        
//        virtual void build(SVRendererPtr _renderer);
//
//        virtual void render(SVRendererPtr _renderer);
        
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


#endif //SV_SHADER_METAL_H
