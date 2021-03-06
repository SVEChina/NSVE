//
// SVRFboMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RFBO_METAL_H
#define SV_RFBO_METAL_H

#include "../SVRFbo.h"

#import <Metal/Metal.h>

namespace sv {
    
    /*
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRFboMetal : public SVRFbo {
    public:
        SVRFboMetal(SVInstPtr _app);
        
        ~SVRFboMetal();
        
        virtual void load(SVRendererPtr _renderer,SVTargetDsp* _logic_dsp);

        virtual void unload();
        
        virtual void resize(s32 _width,s32 _height,SVRendererPtr _renderer);
        
        virtual void bind(SVRendererPtr _renderer);

        virtual void unbind(SVRendererPtr _renderer);
        
    private:
        void _createCommonBuf(SVRendererMetalPtr _renderer);
        
        void _createDepthBuf(SVRendererMetalPtr _renderer);

        void _createStencilBuf(SVRendererMetalPtr _renderer) ;
        
    public:
        SV_TEXIN m_color_tex[SV_SUPPORT_MAX_TAREGT];
        id<MTLTexture> m_depth_tex;
        id<MTLTexture> m_stencil_tex;
        //
        MTLRenderPassDescriptor* m_pass;
        //
        id<MTLRenderCommandEncoder> m_render_encoder;
        id<MTLBlitCommandEncoder> m_blit_encoder;
        id<MTLComputeCommandEncoder> m_compute_encoder;
    };

    
}//!namespace sv



#endif //SV_RFBO_METAL_H
