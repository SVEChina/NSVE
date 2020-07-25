//
// SVRDPStateMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRDPStateMetal.h"
#include "SVRendererMetal.h"
#include "../../mtl/SVShader.h"
#include "../../app/SVInst.h"
#include "../../file/SVFileMgr.h"

using namespace sv;

SVRDPStateMetal::SVRDPStateMetal(SVInstPtr _app)
:SVRDPState(_app){
}

SVRDPStateMetal::~SVRDPStateMetal() {
}

void SVRDPStateMetal::create(SVRendererPtr _renderer) {
}
           
void SVRDPStateMetal::destroy(SVRendererPtr _renderer) {
    
}

bool SVRDPStateMetal::active(SVRendererPtr _render) {
    //m_rp_dsp = [[MTLRenderPipelineDescriptor alloc] init];
    //    pipelineStateDescriptor.label = @"Simple Pipeline";
    //    pipelineStateDescriptor.vertexFunction = vertexFunction;
    //    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    //    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;
    //    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
    return true;
}
//void SVRShaderMetal::render(SVRendererPtr _renderer) {
//    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
//    //id<MTLCommandBuffer> commandBuffer = [t_rm->m_pCmdQueue commandBuffer];
//
////    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
////    pipelineStateDescriptor.label = @"Simple Pipeline";
////    pipelineStateDescriptor.vertexFunction = vertexFunction;
////    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
////    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;
////
////    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
////                                                             error:&error];
///////    //状态切换
////
////    //
//
//}
