//
// IMICtxIOS.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_CONTEXT_IOS_H
#define IMI_CONTEXT_IOS_H

#include "IMICtxBase.h"

#ifdef IMI_IOS

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

namespace imi {
    
    //苹果手机上跑的 只有gles20,gles30,metle的渲染器
    class IMICtxIOSGLES: public IMICtxBase {
    public:
        IMICtxIOSGLES(IMIInstPtr _app);
        
        ~IMICtxIOSGLES();
        
        //同步调用 确保在一个线程
        void init(void* _shareContext,s32 _version,void* _layer);

        bool activeContext(IMIRendererPtr _renderer);

        bool swap(IMIRendererPtr _renderer);
        
    protected:
        s32 m_glversion;
        u32 m_frameBuf;
        u32 m_colorBuf;
        EAGLContext* m_gl_context;
        EAGLContext* m_gl_context_share;
        CAEAGLLayer* m_gl_layer;
    };

    //Metal渲染器
    class IMICtxIOSMetal: public IMICtxBase {
    public:
        IMICtxIOSMetal(IMIInstPtr _app);
        
        ~IMICtxIOSMetal();
        
        void init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex);

        bool activeContext(IMIRendererPtr _renderer);

        bool swap(IMIRendererPtr _renderer);
        
    protected:
        s32 m_glversion;
    };
    
}//!namespace imi


#endif  //IMI_IOS

#endif  //IMI_CONTEXT_IOS_H
