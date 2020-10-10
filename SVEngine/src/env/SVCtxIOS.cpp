//
// SVCtxIOS.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVCtxIOS.h"
#include "../app/SVInst.h"

using namespace sv;

#ifdef SV_IOS

//设备上下文 真的不能随意切换啊 否则这这个设备上下文中创建的所有GL资源全部都失效
SVCtxIOSGLES::SVCtxIOSGLES(SVInstPtr _app)
:SVCtxBase(_app) {
}

SVCtxIOSGLES::~SVCtxIOSGLES() {
    [EAGLContext setCurrentContext:nil];
    m_gl_context = nil;
    SV_LOG_INFO("destroy context ios\n");
}

//同步初始化
void SVCtxIOSGLES::init(void* _shareContext,s32 _version) {
    m_glversion = _version;
    if(_shareContext){
        EAGLContext* t_context = (__bridge EAGLContext*)_shareContext;
        m_gl_context = [[EAGLContext alloc] initWithAPI:[t_context API] sharegroup:[t_context sharegroup]];
        SV_LOG_INFO("create context ios new\n");
    }else{
        if (_version == 3) {
            m_gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        }else if(_version == 2) {
            m_gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        }else {
            m_gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        }
        SV_LOG_INFO("create context ios share\n");
    }
}

//异步初始化
void SVCtxIOSGLES::initASync(void* _shareContext,s32 _version) {
    
}

bool SVCtxIOSGLES::activeContext(SVRendererPtr _renderer){
    if(m_gl_context){
        return [EAGLContext setCurrentContext:m_gl_context];
    }
    NSLog(@"activeContext error!");
    return false;
}

//交换场景
bool SVCtxIOSGLES::swap(SVRendererPtr _renderer){
    if(m_gl_context){
        bool t_flag = [m_gl_context presentRenderbuffer:GL_RENDERBUFFER];
        if(!t_flag){
            NSLog(@"presentRenderbuffer error!");
            return false;
        }
        return true;
    }
    return false;
}

//
SVCtxIOSMetal::SVCtxIOSMetal(SVInstPtr _app)
:SVCtxBase(_app) {
}

SVCtxIOSMetal::~SVCtxIOSMetal() {
}

void SVCtxIOSMetal::init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex) {
//    m_gl_context_out = (__bridge NSOpenGLContext*)_context;
//    if(m_gl_context_out) {
//        SVRendererGLPtr t_renderer = MakeSharedPtr<SVRendererGL>(_handle);
//        t_renderer->init(_w,_h,_version);
//        //_handle->setRenderer(t_renderer);
//    }
}

bool SVCtxIOSMetal::activeContext(SVRendererPtr _renderer){
    return false;
}

//交换场景
bool SVCtxIOSMetal::swap(SVRendererPtr _renderer){
    return false;
}

#endif






