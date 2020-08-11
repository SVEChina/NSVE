//
// SVCtxOSXGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CONTEXTOSX_H
#define SV_CONTEXTOSX_H

#include "SVCtxBase.h"

#ifdef SV_OSX

#import <Foundation/Foundation.h>
#import <AppKit/NSOpenGL.h>

namespace sv {

    //mac上跑的 只有gl20,gl30,metle的渲染器

    class SVCtxOSXGL: public SVCtxBase {
    public:
        SVCtxOSXGL();
        
        ~SVCtxOSXGL();
        
        void init(void* _context);
        
        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        NSOpenGLContext* m_pGLContext;
    };

    //osx metal环境
    class SVCtxOSXMetal: public SVCtxBase {
    public:
        SVCtxOSXMetal();
        
        ~SVCtxOSXMetal();
        
        void init(SVInstPtr _handle,id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex);

        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        id<MTLDrawable> m_target;
        id<MTLTexture> m_texture;
        MTLRenderPassDescriptor* m_pass;
        id<MTLCommandBuffer> m_cmdBuffer;
        id<MTLRenderCommandEncoder> m_cmdEncoder;
    };
    
}//!namespace sv



#endif  //SV_OSX

#endif  //SV_CONTEXTOSX_H
