//
// IMICtxOSX.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_CONTEXT_OSX_H
#define IMI_CONTEXT_OSX_H

#include "IMICtxBase.h"
#include "../rendercore/IMIRenderCmd.h"

#ifdef IMI_OSX

#import <Foundation/Foundation.h>
#import <AppKit/NSOpenGL.h>

namespace imi {
    
    //mac上跑的 只有gl20,gl30,metle的渲染器
    class IMICtxOSXGL: public IMICtxBase {
    public:
        IMICtxOSXGL(IMIInstPtr _app);
        
        ~IMICtxOSXGL();
        
        void init(void* _context,s32 _w,s32 _h,s32 _version);
        
        void resize(s32 _w,s32 _h){}
        
        bool activeContext(IMIRendererPtr _renderer);

        bool swap(IMIRendererPtr _renderer);
        
    protected:
        NSOpenGLContext* m_gl_context_out;
        NSOpenGLContext* m_gl_context;
    };

    //osx metal环境
    class IMICtxOSXMetal: public IMICtxBase {
    public:
        IMICtxOSXMetal(IMIInstPtr _app);
        
        ~IMICtxOSXMetal();
        
        void init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex);
        
        void resize(s32 _w,s32 _h);

        bool activeContext(IMIRendererPtr _renderer);

        bool swap(IMIRendererPtr _renderer);
        
    protected:
        id<MTLDrawable> m_target;
        id<MTLTexture> m_texture;
        MTLRenderPassDescriptor* m_pass;
    };
    
}//!namespace imi



#endif  //IMI_OSX

#endif  //IMI_CONTEXT_OSX_H
