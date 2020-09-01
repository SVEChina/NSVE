//
// SVCtxOSX.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CONTEXT_OSX_H
#define SV_CONTEXT_OSX_H

#include "SVCtxBase.h"
#include "../rendercore/SVRenderCmd.h"

#ifdef SV_OSX

#import <Foundation/Foundation.h>
#import <AppKit/NSOpenGL.h>

namespace sv {
    
    //mac上跑的 只有gl20,gl30,metle的渲染器
    class SVCtxOSXGL: public SVCtxBase {
    public:
        SVCtxOSXGL();
        
        ~SVCtxOSXGL();
        
        void init(SVInstPtr _handle,void* _context,s32 _w,s32 _h);
        
        void resize(s32 _w,s32 _h){}
        
        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        NSOpenGLContext* m_gl_context_out;
        NSOpenGLContext* m_gl_context;
    };

    //osx metal环境
    class SVCtxOSXMetal: public SVCtxBase {
    public:
        SVCtxOSXMetal();
        
        ~SVCtxOSXMetal();
        
        void init(SVInstPtr _handle,id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex);
        
        void resize(s32 _w,s32 _h);

        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        id<MTLDrawable> m_target;
        id<MTLTexture> m_texture;
        MTLRenderPassDescriptor* m_pass;
    };
    
}//!namespace sv



#endif  //SV_OSX

#endif  //SV_CONTEXT_OSX_H
