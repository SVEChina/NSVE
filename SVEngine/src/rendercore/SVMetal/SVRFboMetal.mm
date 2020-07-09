//
// SVRFboMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRFboMetal.h"
#include "SVRendererMetal.h"

using namespace sv;

//
SVRFboMetal::SVRFboMetal(SVInstPtr _app)
:SVRFbo(_app) {
    m_pTarget = nullptr;
    m_pTargetTex = nullptr;
    m_passDsp = nullptr;
}

SVRFboMetal::~SVRFboMetal() {
}

void SVRFboMetal::init(id<MTLDrawable> _target,id<MTLTexture> _targetTex) {
    m_pTarget = _target;
    m_pTargetTex = _targetTex;
    m_passDsp = [MTLRenderPassDescriptor renderPassDescriptor];
    m_passDsp.colorAttachments[0].texture = m_pTargetTex;
    m_passDsp.colorAttachments[0].loadAction = MTLLoadActionClear;
    m_passDsp.colorAttachments[0].storeAction = MTLStoreActionStore;
    m_passDsp.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
}

void SVRFboMetal::_preRender(SVRendererPtr _renderer) {
    m_passDsp.colorAttachments[0].texture = m_pTargetTex;
    m_passDsp.colorAttachments[0].loadAction = MTLLoadActionClear;
    m_passDsp.colorAttachments[0].storeAction = MTLStoreActionStore;
    m_passDsp.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
    //
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    m_cmdBuffer = [t_rm->m_pCmdQueue commandBuffer];
    m_cmdEncoder = [m_cmdBuffer renderCommandEncoderWithDescriptor:m_passDsp];
}

void SVRFboMetal::_render(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    //数据，数据，数据
    
}

void SVRFboMetal::_afterRender(SVRendererPtr _renderer) {
    //SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    [m_cmdEncoder endEncoding];
    [m_cmdBuffer presentDrawable:m_pTarget];
    [m_cmdBuffer commit];
}

