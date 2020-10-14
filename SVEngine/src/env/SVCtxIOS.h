//
// SVCtxIOS.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CONTEXT_IOS_H
#define SV_CONTEXT_IOS_H

#include "SVCtxBase.h"

#ifdef SV_IOS

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

namespace sv {
    
    //苹果手机上跑的 只有gles20,gles30,metle的渲染器
    class SVCtxIOSGLES: public SVCtxBase {
    public:
        SVCtxIOSGLES(SVInstPtr _app);
        
        ~SVCtxIOSGLES();
        
        //同步调用 确保在一个线程
        void init(void* _shareContext,s32 _version,s32 _w,s32 _h);

        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        s32 m_glversion;
        EAGLContext* m_gl_context;
        EAGLContext* m_gl_context_share;
    };

    //Metal渲染器
    class SVCtxIOSMetal: public SVCtxBase {
    public:
        SVCtxIOSMetal(SVInstPtr _app);
        
        ~SVCtxIOSMetal();
        
        void init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex);

        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        s32 m_glversion;
    };
    
}//!namespace sv


#endif  //SV_IOS

#endif  //SV_CONTEXT_IOS_H
