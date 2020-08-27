//
// SVRFboMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRFboMetal.h"
#include "SVRendererMetal.h"
#include "../SVRTarget.h"
#include "../../app/SVInst.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"

using namespace sv;

//
SVRFboMetal::SVRFboMetal(SVInstPtr _app)
:SVRFbo(_app) {
    m_pass = nullptr;
    m_render_encoder = nullptr;
    m_blit_encoder = nullptr;
    m_compute_encoder = nullptr;
    for(s32 i=0;i<SV_SUPPORT_MAX_TAREGT;i++) {
        m_color_tex[i] = E_TEX_BEGIN;
    }
    m_depth_tex = nullptr;
    m_stencil_tex = nullptr;
}

SVRFboMetal::~SVRFboMetal() {
    for(s32 i=0;i<SV_SUPPORT_MAX_TAREGT;i++) {
        m_color_tex[i] = E_TEX_BEGIN;
    }
}

void SVRFboMetal::create(SVRendererPtr _renderer) {
    SVRFbo::create(_renderer);
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    SVRTargetPtr t_target = std::dynamic_pointer_cast<SVRTarget>(m_logic_obj);
    if(t_rm && t_target) {
        m_pass = [MTLRenderPassDescriptor renderPassDescriptor];
        SVTargetDsp* t_dsp = t_target->getTargetDsp();
        //创建color纹理，支持多目标渲染,暂时不支持不同目标，不同的格式
        m_width = t_dsp->m_width;
        m_height = t_dsp->m_height;
        m_target_num = t_dsp->m_target_num>SV_SUPPORT_MAX_TAREGT ? SV_SUPPORT_MAX_TAREGT : t_dsp->m_target_num;
        m_use_depth = t_dsp->m_use_depth;
        m_use_stencil = t_dsp->m_use_stencil;
        MTLPixelFormat t_pfmt = MTLPixelFormatRGBA8Unorm;
        MTLTextureDescriptor* t_descriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:t_pfmt width:m_width height:m_height mipmapped:false];
        t_descriptor.usage |= MTLTextureUsageRenderTarget;
        for(s32 i=0;i<m_target_num;i++) {
            m_color_tex[i]= SVINTEX(t_dsp->m_color_texid[i]);
        }
        //
        if(m_use_depth && m_use_stencil) {
            _createCommonBuf(t_rm);
            return ;
        }
        if(m_use_depth) {
            _createDepthBuf(t_rm);
            return ;
        }
        if(m_use_stencil) {
            _createStencilBuf(t_rm);
            return ;
        }
    }
}

void SVRFboMetal::_createCommonBuf(SVRendererMetalPtr _renderer) {
    MTLTextureDescriptor* t_dsp = [[MTLTextureDescriptor alloc] init];
    t_dsp.textureType = _renderer->m_samplenum > 1 ? MTLTextureType2DMultisample : MTLTextureType2D;
    t_dsp.pixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    t_dsp.width = m_width;
    t_dsp.height = m_height;
    t_dsp.depth  = 1;
    t_dsp.mipmapLevelCount = 1;
    t_dsp.sampleCount = _renderer->m_samplenum;;
    t_dsp.arrayLength = 1;
    if (_renderer->m_iOS9Runtime ||  _renderer->m_macOS11Runtime){
        t_dsp.cpuCacheMode = MTLCPUCacheModeDefaultCache;
        t_dsp.storageMode  = MTLStorageModePrivate;
        t_dsp.usage        = MTLTextureUsageRenderTarget;
    }
    m_depth_tex = [_renderer->m_pDevice newTextureWithDescriptor:t_dsp ];
    m_stencil_tex = m_depth_tex;
}

void SVRFboMetal::_createDepthBuf(SVRendererMetalPtr _renderer) {
    MTLTextureDescriptor* t_dsp = [[MTLTextureDescriptor alloc] init];
    t_dsp.textureType =  _renderer->m_samplenum > 1 ? MTLTextureType2DMultisample : MTLTextureType2D;
    t_dsp.pixelFormat = MTLPixelFormatDepth32Float;
    t_dsp.width = m_width;
    t_dsp.height = m_height;
    t_dsp.depth  = 1;
    t_dsp.mipmapLevelCount = 1;
    t_dsp.sampleCount = _renderer->m_samplenum;
    t_dsp.arrayLength = 1;
    if (_renderer->m_iOS9Runtime || _renderer->m_macOS11Runtime){
        t_dsp.cpuCacheMode = MTLCPUCacheModeDefaultCache;
        t_dsp.storageMode  = MTLStorageModePrivate;
        t_dsp.usage        = MTLTextureUsageRenderTarget;
    }
    m_depth_tex = [_renderer->m_pDevice newTextureWithDescriptor:t_dsp ];
}

void SVRFboMetal::_createStencilBuf(SVRendererMetalPtr _renderer) {
    MTLTextureDescriptor* t_dsp = [[MTLTextureDescriptor alloc] init];
    t_dsp.textureType = _renderer->m_samplenum > 1 ? MTLTextureType2DMultisample : MTLTextureType2D;
    t_dsp.pixelFormat = MTLPixelFormatStencil8;
    t_dsp.width = m_width;
    t_dsp.height = m_height;
    t_dsp.depth  = 1;
    t_dsp.mipmapLevelCount = 1;
    t_dsp.sampleCount = _renderer->m_samplenum;
    t_dsp.arrayLength = 1;
    if (_renderer->m_iOS9Runtime ||  _renderer->m_macOS11Runtime){
        t_dsp.cpuCacheMode = MTLCPUCacheModeDefaultCache;
        t_dsp.storageMode  = MTLStorageModePrivate;
        t_dsp.usage        = MTLTextureUsageRenderTarget;
    }
    m_stencil_tex = [_renderer->m_pDevice newTextureWithDescriptor:t_dsp ];
}

void SVRFboMetal::destroy(SVRendererPtr _renderer) {
    //颜色重置
    //深度重置
    //模版重置
    SVRFbo::destroy(_renderer);
}

void SVRFboMetal::resize(s32 _width,s32 _height,SVRendererPtr _renderer) {
    if(m_width!=_width || m_height!=_height) {
        m_width = _width;
        m_height = _height;
        //重新改大小
        if(m_use_depth && m_use_stencil) {
            //_createCommonBuf(t_rm);
        }else if(m_use_depth) {
            //_createDepthBuf(t_rm);
        }else if(m_use_stencil) {
            //_createStencilBuf(t_rm);
        }
        //颜色纹理重制大小
        for(s32 i=0;i<SV_SUPPORT_MAX_TAREGT;i++) {
            SVTexturePtr t_tex = mApp->getTexMgr()->getInTexture(m_color_tex[i]);
            if(t_tex && t_tex->getResTex() ) {
                t_tex->resize(_width,_height);
            }
        }
    }
}

void SVRFboMetal::bind(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm) {
        //支持多目标
        for(s32 i=0;i<SV_SUPPORT_MAX_TAREGT;i++) {
            SVTexturePtr t_tex = mApp->getTexMgr()->getInTexture(m_color_tex[i]);
            if(t_tex && t_tex->getResTex() ) {
                SVRTexPtr t_res_tex = t_tex->getResTex();
                SVRTexMetalPtr t_metal_tex = std::dynamic_pointer_cast<SVRTexMetal>(t_res_tex);
                m_pass.colorAttachments[i].texture = t_metal_tex->getInner();
                m_pass.colorAttachments[i].loadAction = MTLLoadActionClear;
                m_pass.colorAttachments[i].storeAction = MTLStoreActionDontCare;
                m_pass.colorAttachments[i].clearColor = MTLClearColorMake(m_color_value.r,
                                                                          m_color_value.g,
                                                                          m_color_value.b,
                                                                          m_color_value.a);
            } else {
                m_pass.colorAttachments[i].texture = nullptr;
                m_pass.colorAttachments[i].loadAction = MTLLoadActionClear;
                m_pass.colorAttachments[i].storeAction = MTLStoreActionDontCare;
                m_pass.colorAttachments[i].clearColor = MTLClearColorMake(m_color_value.r,
                                                                          m_color_value.g,
                                                                          m_color_value.b,
                                                                          m_color_value.a);
            }
        }
        //支持深度
        if(m_depth_tex) {
            m_pass.depthAttachment.texture = m_depth_tex;
            m_pass.depthAttachment.loadAction = MTLLoadActionClear;
            m_pass.depthAttachment.storeAction = MTLStoreActionDontCare;
            m_pass.depthAttachment.clearDepth = m_depth_value;
        }
        //支持模版
        if(m_stencil_tex) {
            m_pass.stencilAttachment.texture = m_stencil_tex;
            m_pass.stencilAttachment.loadAction = MTLLoadActionClear;
            m_pass.stencilAttachment.storeAction = MTLStoreActionDontCare;
            m_pass.stencilAttachment.clearStencil = m_stencil_value;
        }
        m_render_encoder = [t_rm->m_cmdBuffer renderCommandEncoderWithDescriptor:m_pass];
        MTLViewport t_vp;
        t_vp.originX = 0.0;
        t_vp.originY = 0.0;
        t_vp.width = m_width;
        t_vp.height = m_height;
        t_vp.znear = 1.0;
        t_vp.zfar = 10000.0;
        [m_render_encoder setViewport:t_vp];
        t_rm->pushEncoder(m_render_encoder);
    }
}

void SVRFboMetal::unbind(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm) {
        [m_render_encoder endEncoding];
        t_rm->popEncoder();
    }
}
