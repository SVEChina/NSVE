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
    m_pTargetTex = nullptr;
    m_passDsp = nullptr;
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
        if(t_dsp->m_oc_target && t_dsp->m_oc_texture) {
            m_pTarget = (__bridge id<MTLDrawable>)(t_dsp->m_oc_target);
            m_pTargetTex = (__bridge id<MTLTexture>)(t_dsp->m_oc_texture);
            //创建一个pass
            m_passDsp = [MTLRenderPassDescriptor renderPassDescriptor];
            m_passDsp.colorAttachments[0].texture = m_pTargetTex;
            m_passDsp.colorAttachments[0].loadAction = MTLLoadActionClear;
            m_passDsp.colorAttachments[0].storeAction = MTLStoreActionStore;
            m_passDsp.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
//            //
//            m_cmdBuffer = [t_rm->m_pCmdQueue commandBuffer];
//            m_cmdEncoder = [m_cmdBuffer renderCommandEncoderWithDescriptor:m_passDsp];
        }
    }
}

void SVRFboMetal::destroy(SVRendererPtr _renderer) {
    //
    if(m_pTarget) {
        m_pTarget = nullptr;
        //CFRelease(m_pTarget);
        //[m_pTarget release];
    }
    if(m_pTargetTex){
        m_pTargetTex = nullptr;
        //CFRelease(m_pTargetTex);
        //[m_pTargetTex release];
    }
    SVRFbo::destroy(_renderer);
}

void SVRFboMetal::bind(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm) {
        m_passDsp.colorAttachments[0].texture = m_pTargetTex;
        m_passDsp.colorAttachments[0].loadAction = MTLLoadActionClear;
        m_passDsp.colorAttachments[0].storeAction = MTLStoreActionStore;
        m_passDsp.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
        m_cmdBuffer = [t_rm->m_pCmdQueue commandBuffer];
        m_cmdEncoder = [m_cmdBuffer renderCommandEncoderWithDescriptor:m_passDsp];
    }
}

void SVRFboMetal::unbind(SVRendererPtr _renderer) {
    //SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    [m_cmdEncoder endEncoding];
    [m_cmdBuffer presentDrawable:m_pTarget];
    [m_cmdBuffer commit];
}

//void SVRFboMetal::_preRender(SVRendererPtr _renderer) {
//    m_passDsp.colorAttachments[0].texture = m_pTargetTex;
//    m_passDsp.colorAttachments[0].loadAction = MTLLoadActionClear;
//    m_passDsp.colorAttachments[0].storeAction = MTLStoreActionStore;
//    m_passDsp.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
//    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
//    m_cmdBuffer = [t_rm->m_pCmdQueue commandBuffer];
//    m_cmdEncoder = [m_cmdBuffer renderCommandEncoderWithDescriptor:m_passDsp];
//}
//
//void SVRFboMetal::_render(SVRendererPtr _renderer) {
//    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
//    //数据，数据，数据
//
//}
//
//void SVRFboMetal::_afterRender(SVRendererPtr _renderer) {
////SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
////    [m_cmdEncoder endEncoding];
////    [m_cmdBuffer presentDrawable:m_pTarget];
////    [m_cmdBuffer commit];
//}

