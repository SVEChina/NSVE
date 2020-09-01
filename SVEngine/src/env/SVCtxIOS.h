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
        SVCtxIOSGLES(void* _context,s32 _glversion);
        
        ~SVCtxIOSGLES();

        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        s32 m_glversion;
        EAGLContext* m_gl_context;
    };

    //Metal渲染器
    class SVCtxIOSMetal: public SVCtxBase {
    public:
        SVCtxIOSMetal();
        
        ~SVCtxIOSMetal();

        bool activeContext(SVRendererPtr _renderer);

        bool swap(SVRendererPtr _renderer);
        
    protected:
        s32 m_glversion;
    };
    
}//!namespace sv


#endif  //SV_IOS

#endif  //SV_CONTEXT_IOS_H
