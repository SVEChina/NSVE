//
// SVCtxOSXGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#include "SVCtxOSX.h"
#include "../app/SVInst.h"
#include "../rendercore/SVMetal/SVRendererMetal.h"
#include "../rendercore/SVGL/SVRendererGL.h"

using namespace sv;

#ifdef SV_OSX

//设备上下文 真的不能随意切换啊 否则这这个设备上下文中创建的所有GL资源全部都失效
SVCtxOSXGL::SVCtxOSXGL()
:SVCtxBase() {
}

SVCtxOSXGL::~SVCtxOSXGL() {
    m_pGLContext = nullptr;
}

void SVCtxOSXGL::init(void* _context) {
    m_pGLContext = (__bridge NSOpenGLContext*)_context;
}

bool SVCtxOSXGL::activeContext(SVRendererPtr _renderer){
    if( m_pGLContext ) {
        [m_pGLContext makeCurrentContext];
        return true;
    }
    return false;
}

bool SVCtxOSXGL::swap(SVRendererPtr _renderer){
    if( m_pGLContext ) {
        [m_pGLContext flushBuffer];
        return true;
    }
    return false;
}

//
//设备上下文 真的不能随意切换啊 否则这这个设备上下文中创建的所有GL资源全部都失效
SVCtxOSXMetal::SVCtxOSXMetal()
:SVCtxBase() {
}

SVCtxOSXMetal::~SVCtxOSXMetal() {
}

void SVCtxOSXMetal::init(SVInstPtr _handle,id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _tex) {
    if(_handle && _target && _tex) {
        SVRendererMetalPtr t_renderer = MakeSharedPtr<SVRendererMetal>(_handle);
        t_renderer->init(_device,s32(_tex.width),s32(_tex.height));
        _handle->setRenderer(t_renderer);
        m_target = _target;
        m_texture = _tex;
        m_pass = [MTLRenderPassDescriptor renderPassDescriptor];
    }
}

bool SVCtxOSXMetal::activeContext(SVRendererPtr _renderer){
    SVRendererMetalPtr t_rm = dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm ){
        t_rm->m_cmdBuffer = [t_rm->m_cmdQuene commandBuffer];
        return true;
    }
    return false;
}

bool SVCtxOSXMetal::swap(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm) {
        m_pass.colorAttachments[0].texture = m_texture;
        m_pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        m_pass.colorAttachments[0].storeAction = MTLStoreActionDontCare;
        m_pass.colorAttachments[0].clearColor = MTLClearColorMake(0.5f, 0.0f, 0.5f, 1);
        id<MTLRenderCommandEncoder> t_encoder  = [t_rm->m_cmdBuffer renderCommandEncoderWithDescriptor:m_pass];
        t_rm->pushEncoder(t_encoder);
        //绘制
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






