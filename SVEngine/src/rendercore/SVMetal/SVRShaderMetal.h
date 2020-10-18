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
    
    struct SamplerDsp;

    class SVRShaderMetal : public SVRShader {
    public:
        friend class SVRendererMetal;
        friend class std::shared_ptr<SVRendererMetal> ;

        SVRShaderMetal(SVInstPtr _app);
        
        ~SVRShaderMetal();
        
        void load(SVRendererPtr _renderer,ShaderDsp* _shader_dsp);
               
        void unload();

        bool active(SVRendererPtr _renderer);
        
        void submitParamTbl(SVRendererPtr _renderer);
        
    protected:
        MTLSamplerDescriptor* _genSampler(SamplerDsp& _dsp);
        
        MTLVertexDescriptor* _genVertexDsp(BUFFERMODE _mode);
        
        id<MTLFunction> m_vsf;
        id<MTLFunction> m_gsf;
        id<MTLFunction> m_tscf;
        id<MTLFunction> m_tsdf;
        id<MTLFunction> m_fsf;
        id<MTLFunction> m_csf;
        //采样器
        struct INSAMPLE {
            id<MTLSamplerState> m_st;   //采样
            s32 m_stage;                //0:vs 1:fs 2:gs
            s32 m_chn;                  //通道
        };
        std::vector<INSAMPLE> m_sampler_st;
        //buf
        struct UBUF {
            id<MTLBuffer> m_ubuf;   //对应buf
            s32 m_stage;            //0:vs 1:fs 2:gs
            s32 m_bufid;            //buf-id
        };
        std::vector<UBUF> m_ubuf_pool;
        //状态
        id<MTLRenderPipelineState> m_pl_state;
    };


}//!namespace sv


#endif //SV_RSHADER_METAL_H
