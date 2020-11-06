//
// IMICtxIOS.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMICtxIOS.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIGL/IMIRendererGL.h"

using namespace imi;

#ifdef IMI_IOS

//设备上下文 真的不能随意切换啊 否则这这个设备上下文中创建的所有GL资源全部都失效
IMICtxIOSGLES::IMICtxIOSGLES(IMIInstPtr _app)
:IMICtxBase(_app) {
}

IMICtxIOSGLES::~IMICtxIOSGLES() {
    [EAGLContext setCurrentContext:nil];
    m_gl_context = nil;
    m_gl_context_share = nil;
    IMI_LOG_INFO("destroy context ios\n");
}

//同步初始化
void IMICtxIOSGLES::init(void* _shareContext,s32 _version,void* _layer) {
    m_glversion = _version;
    m_gl_context_share = (__bridge EAGLContext*)_shareContext;
    m_gl_layer = (__bridge CAEAGLLayer*)_layer;
    //
    mApp->m_global_param.sv_width = m_gl_layer.frame.size.width;
    mApp->m_global_param.sv_height = m_gl_layer.frame.size.height;
    //创建渲染器
    IMIRendererGLPtr t_renderer = MakeSharedPtr<IMIRendererGL>(mApp);
    t_renderer->init(_version);
    //
    mApp->_initRenderer(t_renderer);
}

bool IMICtxIOSGLES::activeContext(IMIRendererPtr _renderer){
    bool ret = false;
    if(m_gl_context){
        ret = [EAGLContext setCurrentContext:m_gl_context];
    } else {
        //创建阶段
        //因为是OpenGL 所以需要跟render绑定在一起才对
        if(m_gl_context_share){
            m_gl_context = [[EAGLContext alloc] initWithAPI:[m_gl_context_share API] sharegroup:[m_gl_context_share sharegroup]];
            IMI_LOG_INFO("create context ios new\n");
        } else {
            if (m_glversion == 3) {
                m_gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
            }else if(m_glversion == 2) {
                m_gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
            }else {
                m_gl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
            }
            IMI_LOG_INFO("create context ios share\n");
        }
        if(m_gl_context) {
            ret = [EAGLContext setCurrentContext:m_gl_context];
        }
        //
        _renderer->info();
        //
        if( m_gl_layer ) {
            glGenFramebuffers(1, &m_frameBuf);
            glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuf);
            glGenRenderbuffers(1, &m_colorBuf);
            glBindRenderbuffer(GL_RENDERBUFFER, m_colorBuf);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorBuf);
            [m_gl_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:m_gl_layer];
            //check success
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                NSLog(@"Failed to make complete framebuffer object: %i", glCheckFramebufferStatus(GL_FRAMEBUFFER));
            }
        }
    }
    if( m_gl_layer ) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuf);
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, mApp->m_global_param.sv_width, mApp->m_global_param.sv_height);
    }
    return ret;
}

//交换场景
bool IMICtxIOSGLES::swap(IMIRendererPtr _renderer){
    if(m_gl_context){
        if( m_gl_layer ) {
            glViewport(0, 0, mApp->m_global_param.sv_width, mApp->m_global_param.sv_height);
            _renderer->drawScreen(E_TEX_MAIN);
        }
        //
        glBindRenderbuffer(GL_RENDERBUFFER, m_colorBuf);
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
IMICtxIOSMetal::IMICtxIOSMetal(IMIInstPtr _app)
:IMICtxBase(_app) {
}

IMICtxIOSMetal::~IMICtxIOSMetal() {
}

void IMICtxIOSMetal::init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex) {
//    m_gl_context_out = (__bridge NSOpenGLContext*)_context;
//    if(m_gl_context_out) {
//        IMIRendererGLPtr t_renderer = MakeSharedPtr<IMIRendererGL>(_handle);
//        t_renderer->init(_w,_h,_version);
//        //_handle->setRenderer(t_renderer);
//    }
}

bool IMICtxIOSMetal::activeContext(IMIRendererPtr _renderer){
    return false;
}

//交换场景
bool IMICtxIOSMetal::swap(IMIRendererPtr _renderer){
    return false;
}

#endif






