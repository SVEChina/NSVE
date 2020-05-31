//
// SVRTargetMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTargetMetal.h"
#include "SVRendererMetal.h"

using namespace sv;

//
SVRTargetMetal::SVRTargetMetal(SVInstPtr _app)
: SVRTarget(_app) {
    m_pTarget = nullptr;
    m_pTargetTex = nullptr;
    m_passDsp = nullptr;
}

SVRTargetMetal::~SVRTargetMetal() {
}

void SVRTargetMetal::init(id<MTLDrawable> _target,id<MTLTexture> _targetTex) {
    m_pTarget = _target;
    m_pTargetTex = _targetTex;
    m_passDsp = [MTLRenderPassDescriptor renderPassDescriptor];
    m_passDsp.colorAttachments[0].texture = m_pTargetTex;
    m_passDsp.colorAttachments[0].loadAction = MTLLoadActionClear;
    m_passDsp.colorAttachments[0].storeAction = MTLStoreActionStore;
    m_passDsp.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
}

void SVRTargetMetal::_preRender(SVRendererPtr _renderer) {
    m_passDsp.colorAttachments[0].texture = m_pTargetTex;
    m_passDsp.colorAttachments[0].loadAction = MTLLoadActionClear;
    m_passDsp.colorAttachments[0].storeAction = MTLStoreActionStore;
    m_passDsp.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
}

void SVRTargetMetal::_render(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    id<MTLCommandBuffer> commandBuffer = [t_rm->m_pCmdQueue commandBuffer];
    id<MTLRenderCommandEncoder> commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:m_passDsp];
    //数据，数据，数据
    
    //
    [commandEncoder endEncoding];
}

void SVRTargetMetal::_afterRender(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    id<MTLCommandBuffer> commandBuffer = [t_rm->m_pCmdQueue commandBuffer];
    [commandBuffer presentDrawable:m_pTarget];
    [commandBuffer commit];
}

