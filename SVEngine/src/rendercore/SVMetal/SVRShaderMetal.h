//
// SVRShaderMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RSHADER_METAL_H
#define SV_RSHADER_METAL_H

#include "../SVRShader.h"
#include "SVRenderDeclare.h"
#include "../../core/SVVertDef.h"

#import <Metal/Metal.h>
#include <vector>

namespace sv {

    /*
     render tech metal
     */

    class SVRShaderMetal : public SVRShader {
    public:
        friend class SVRendererMetal;
        friend class std::shared_ptr<SVRendererMetal> ;

        SVRShaderMetal(SVInstPtr _app);
        
        ~SVRShaderMetal();
        
        void create(SVRendererPtr _renderer);
               
        void destroy(SVRendererPtr _renderer);

        bool active(SVRendererPtr _renderer);
        
    protected:
        MTLVertexDescriptor* _genVertexDsp(VFTYPE _vf);
        
        id<MTLFunction> m_vsf;
        id<MTLFunction> m_gsf;
        id<MTLFunction> m_tscf;
        id<MTLFunction> m_tsdf;
        id<MTLFunction> m_fsf;
        id<MTLFunction> m_csf;
        //
        std::vector< id<MTLSamplerState> > m_vs_sampler_st;
        std::vector< id<MTLSamplerState> > m_fs_sampler_st;
        std::vector< id<MTLSamplerState> > m_gs_sampler_st;
        //
        id<MTLBuffer> m_vs_ubuf;
        id<MTLBuffer> m_fs_ubuf;
        id<MTLBuffer> m_gs_ubuf;
        //
        id<MTLRenderPipelineState> m_pl_state;
    };


}//!namespace sv


#endif //SV_RSHADER_METAL_H
