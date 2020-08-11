//
// SVRFboMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRFboMetal.h"
#include "SVRendererMetal.h"
#include "../SVRTarget.h"

using namespace sv;

//
SVRFboMetal::SVRFboMetal(SVInstPtr _app)
:SVRFbo(_app) {
    m_pTarget = nullptr;
    m_passDsp = nullptr;
    for(s32 i=0;i<MAX_SUPPORT_TEXTAREGT;i++) {
        m_pTargetTex[i] = nullptr;
    }
    m_pDepthTex = nullptr;
    m_pStencilTex = nullptr;
}

SVRFboMetal::~SVRFboMetal() {
}

void SVRFboMetal::create(SVRendererPtr _renderer) {
    SVRFbo::create(_renderer);
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    SVRTargetPtr t_target = std::dynamic_pointer_cast<SVRTarget>(m_logic_obj);
    if(t_rm && t_target) {
        SVTargetDsp* t_dsp = t_target->getTargetDsp();
        //非创建，直接引用外部参数
        if(t_dsp->m_oc_target ) {
            //配置rendertarget
            m_pTarget = (__bridge id<MTLDrawable>)(t_dsp->m_oc_target);
            m_passDsp = [MTLRenderPassDescriptor renderPassDescriptor];
            if( t_dsp->m_oc_texture) {
                //单目标颜色
                m_pTargetTex[0] = (__bridge id<MTLTexture>)(t_dsp->m_oc_texture);
                m_width = s32(m_pTargetTex[0].width);
                m_height = s32(m_pTargetTex[0].height);
            } else {
                //创建color纹理，支持多目标渲染,暂时不支持不同目标，不同的格式
                m_width = t_dsp->m_width;
                m_height = t_dsp->m_height;
                m_target_num = t_dsp->m_target_num;
                //
                MTLPixelFormat t_pfmt = MTLPixelFormatRGBA8Unorm;
                MTLTextureDescriptor* t_descriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:t_pfmt width:m_width height:m_height mipmapped:true];
                t_descriptor.usage |= MTLTextureUsageRenderTarget;
                for(s32 i=0;i<m_target_num;i++) {
                    //创建MRT多目标
                    m_pTargetTex[i] =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
                }
            }
            //
            if(t_dsp->m_use_depth && t_dsp->m_use_stencil) {
                //公用
                _createCommonBuf(t_rm);
                return ;
            }
            if(t_dsp->m_use_depth) {
                //只有深度
                _createDepthBuf(t_rm);
                return ;
            }
            if(t_dsp->m_use_stencil) {
                //只有模版
                _createStencilBuf(t_rm);
            }
        } else {
            //创建新的RenderTarget
            
            
        } //m_oc_target
        
    }//rm or target
    
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
    m_pDepthTex = [_renderer->m_pDevice newTextureWithDescriptor:t_dsp ];
    m_pStencilTex = m_pDepthTex;
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
    m_pDepthTex = [_renderer->m_pDevice newTextureWithDescriptor:t_dsp ];
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
    m_pStencilTex = [_renderer->m_pDevice newTextureWithDescriptor:t_dsp ];
}

void SVRFboMetal::destroy(SVRendererPtr _renderer) {
    if(m_pTarget) {
        m_pTarget = nullptr;
    }
    if(m_pTargetTex[0]){
        m_pTargetTex[0] = nullptr;
    }
    SVRFbo::destroy(_renderer);
}

void SVRFboMetal::resize(s32 _width,s32 _height,SVRendererPtr _renderer) {
    if(m_width!=_width || m_height!=_height) {
        m_width = _width;
        m_height = _height;
        //销毁旧的纹理
        
        //创建新的纹理
        SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
        SVRTargetPtr t_target = std::dynamic_pointer_cast<SVRTarget>(m_logic_obj);
        SVTargetDsp* t_dsp = t_target->getTargetDsp();
        //非创建，直接引用外部参数
        if(t_dsp->m_oc_target ) {
            //外部传递的target
        } else {
            //自己创建的target
        }
    }//width height
}

void SVRFboMetal::bind(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm) {
        //支持多目标
        for(s32 i=0;i<MAX_SUPPORT_TEXTAREGT;i++) {
            if(m_pTargetTex[i]) {
                m_passDsp.colorAttachments[i].texture = m_pTargetTex[i];
                m_passDsp.colorAttachments[i].loadAction = MTLLoadActionClear;
                m_passDsp.colorAttachments[i].storeAction = MTLStoreActionDontCare;
                m_passDsp.colorAttachments[i].clearColor = MTLClearColorMake(1, 0, 0, 1);
            }else{
                m_passDsp.colorAttachments[i].texture = nullptr;
                m_passDsp.colorAttachments[i].loadAction = MTLLoadActionClear;
                m_passDsp.colorAttachments[i].storeAction = MTLStoreActionDontCare;
                m_passDsp.colorAttachments[i].clearColor = MTLClearColorMake(1, 0, 0, 1);
            }
        }
        //支持深度
        if(m_pDepthTex && false) {
            m_passDsp.depthAttachment.texture = m_pDepthTex;
            m_passDsp.depthAttachment.loadAction = MTLLoadActionClear;
            m_passDsp.depthAttachment.storeAction = MTLStoreActionDontCare;
            m_passDsp.depthAttachment.clearDepth = 1.0;
        }
        //支持模版
        if(m_pStencilTex && false) {
            m_passDsp.stencilAttachment.texture = m_pStencilTex;
            m_passDsp.stencilAttachment.loadAction = MTLLoadActionClear;
            m_passDsp.stencilAttachment.storeAction = MTLStoreActionDontCare;
            m_passDsp.stencilAttachment.clearStencil = 0;
        }
        //
        m_cmdBuffer = [t_rm->m_pCmdQueue commandBuffer];
        m_cmdEncoder = [m_cmdBuffer renderCommandEncoderWithDescriptor:m_passDsp];
        //设置当前encoder
        t_rm->m_pCurEncoder = m_cmdEncoder;
    }
}

void SVRFboMetal::unbind(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm) {
        [m_cmdEncoder endEncoding];
        [m_cmdBuffer commit];
        [m_cmdBuffer presentDrawable:m_pTarget];
        t_rm->m_pCurEncoder = nullptr;
    }
}
