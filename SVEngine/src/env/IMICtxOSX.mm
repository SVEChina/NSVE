//
// IMICtxOSX.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//


#include "IMICtxOSX.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIGL/IMIRendererGL.h"

using namespace imi;

#ifdef IMI_OSX

//设备上下文 真的不能随意切换啊 否则这这个设备上下文中创建的所有GL资源全部都失效
IMICtxOSXGL::IMICtxOSXGL(IMIInstPtr _app)
:IMICtxBase(_app) {
    m_gl_context = nullptr;
    m_gl_context_out = nullptr;
}

IMICtxOSXGL::~IMICtxOSXGL() {
    m_gl_context = nullptr;
    m_gl_context_out = nullptr;
}

void IMICtxOSXGL::init(void* _context,s32 _w,s32 _h,s32 _version) {
    m_gl_context_out = (__bridge NSOpenGLContext*)_context;
    if(m_gl_context_out) {
        IMIRendererGLPtr t_renderer = MakeSharedPtr<IMIRendererGL>(mApp);
        t_renderer->init(_w,_h,_version);
        //_handle->setRenderer(t_renderer);
    }
}

bool IMICtxOSXGL::activeContext(IMIRendererPtr _renderer){
    if( m_gl_context_out ) {
        [m_gl_context_out makeCurrentContext];
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        return true;
    }
    return false;
}

bool IMICtxOSXGL::swap(IMIRendererPtr _renderer){
    if( m_gl_context_out ) {
        [m_gl_context_out flushBuffer];
        return true;
    }
//    if( m_gl_context ) {
//        [m_gl_context flushBuffer];
//        return true;
//    }
    return false;
}

//
//设备上下文 真的不能随意切换啊 否则这这个设备上下文中创建的所有GL资源全部都失效
IMICtxOSXMetal::IMICtxOSXMetal(IMIInstPtr _app)
:IMICtxBase(_app) {
}

IMICtxOSXMetal::~IMICtxOSXMetal() {
}

void IMICtxOSXMetal::init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _tex) {
    if( _target && _tex) {
        //设置主Target大小
        mApp->m_global_param.sv_width = s32(_tex.width);
        mApp->m_global_param.sv_height = s32(_tex.height);
        //创建渲染器
        IMIRendererMetalPtr t_renderer = MakeSharedPtr<IMIRendererMetal>(mApp);
        t_renderer->init(_device);
        //
        mApp->_initRenderer(t_renderer);
        //
        m_target = _target;
        m_texture = _tex;
        m_pass = [MTLRenderPassDescriptor renderPassDescriptor];
    }
}

void IMICtxOSXMetal::resize(s32 _w,s32 _h){
}

bool IMICtxOSXMetal::activeContext(IMIRendererPtr _renderer){
    IMIRendererMetalPtr t_rm = dynamic_pointer_cast<IMIRendererMetal>(_renderer);
    if(t_rm ){
        t_rm->m_cmdBuffer = [t_rm->m_cmdQuene commandBuffer];
        return true;
    }
    return false;
}

bool IMICtxOSXMetal::swap(IMIRendererPtr _renderer) {
    IMIRendererMetalPtr t_rm = std::dynamic_pointer_cast<IMIRendererMetal>(_renderer);
    if(t_rm) {
        m_pass.colorAttachments[0].texture = m_texture;
        m_pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        m_pass.colorAttachments[0].storeAction = MTLStoreActionDontCare;
        m_pass.colorAttachments[0].clearColor = MTLClearColorMake(0.5f, 0.0f, 0.5f, 1);
        id<MTLRenderCommandEncoder> t_encoder  = [t_rm->m_cmdBuffer renderCommandEncoderWithDescriptor:m_pass];
        t_rm->pushEncoder(t_encoder);
        //屏幕空间绘制
        t_rm->drawScreen(E_TEX_MAIN);
        //
        [t_encoder endEncoding];
        [t_rm->m_cmdBuffer presentDrawable:m_target];
        [t_rm->m_cmdBuffer commit];
        t_rm->popEncoder();
        return true;
    }
    return false;
}


#endif






