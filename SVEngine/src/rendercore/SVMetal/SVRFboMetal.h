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
//#import <Metal/MTLDrawable.h>
//#import <Metal/MTLRenderCommandEncoder.h>
//#import <MetalKit/MetalKit.h>

namespace sv {
    
    /*
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRFboMetal : public SVRFbo {
    public:
        SVRFboMetal(SVInstPtr _app);
        
        ~SVRFboMetal();
        
        virtual void create(SVRendererPtr _renderer);

        virtual void destroy(SVRendererPtr _renderer);
        
        virtual void bind(SVRendererPtr _renderer);

        virtual void unbind(SVRendererPtr _renderer);
        
//        void init(id<MTLDrawable> _target,id<MTLTexture> _targetTex);

//    protected:
//        void _preRender(SVRendererPtr _renderer);
//        
//        void _render(SVRendererPtr _renderer);
//        
//        void _afterRender(SVRendererPtr _renderer);
        
    public:
        id<MTLDrawable> m_pTarget;
        id<MTLTexture> m_pTargetTex;
        MTLRenderPassDescriptor* m_passDsp;
        id<MTLCommandBuffer> m_cmdBuffer;
        id<MTLRenderCommandEncoder> m_cmdEncoder;
    };

    
}//!namespace sv



#endif //SV_RFBO_METAL_H
