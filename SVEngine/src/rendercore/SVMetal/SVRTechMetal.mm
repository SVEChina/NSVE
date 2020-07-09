//
// SVRTechMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTechMetal.h"
#include "SVRendererMetal.h"

using namespace sv;

SVRTechMetal::SVRTechMetal(SVInstPtr _app)
:SVRTech(_app){
    m_rp_dsp = nullptr;
    m_vsf = nullptr;
    m_gsf = nullptr;
    m_tscf = nullptr;
    m_tsdf = nullptr;
    m_fsf = nullptr;
    m_csf = nullptr;
}

SVRTechMetal::~SVRTechMetal() {
}

void SVRTechMetal::build(SVRendererPtr _renderer) {
//    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
//    if( m_techDsp&SV_E_TECH_VS ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",m_vs_name.c_str()];
//        m_vsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_FS ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",m_fs_name.c_str()];
//        m_fsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_GS ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",m_gs_name.c_str()];
//        m_gsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_CS ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",m_cs_name.c_str()];
//        m_csf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_TSC ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",m_tsc_name.c_str()];
//        m_tscf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_TSD ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",m_tsd_name.c_str()];
//        m_tsdf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
    
    //m_rp_dsp = [[MTLRenderPipelineDescriptor alloc] init];
    //    pipelineStateDescriptor.label = @"Simple Pipeline";
    //    pipelineStateDescriptor.vertexFunction = vertexFunction;
    //    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    //    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;
    //
    //    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
    //                                                             error:&error];
}

void SVRTechMetal::render(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    //id<MTLCommandBuffer> commandBuffer = [t_rm->m_pCmdQueue commandBuffer];
    
//    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
//    pipelineStateDescriptor.label = @"Simple Pipeline";
//    pipelineStateDescriptor.vertexFunction = vertexFunction;
//    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
//    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;
//
//    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
//                                                             error:&error];
//    
//    //shader 绑定
//    if( m_techDsp&SV_E_TECH_VS ) {
////        NSString* t_str = [NSString stringWithFormat:@"%s",m_vs_name.c_str()];
////        m_vsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_FS ) {
////        NSString* t_str = [NSString stringWithFormat:@"%s",m_fs_name.c_str()];
////        m_fsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_GS ) {
////        NSString* t_str = [NSString stringWithFormat:@"%s",m_gs_name.c_str()];
////        m_gsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_CS ) {
////        NSString* t_str = [NSString stringWithFormat:@"%s",m_cs_name.c_str()];
////        m_csf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_TSC ) {
////        NSString* t_str = [NSString stringWithFormat:@"%s",m_tsc_name.c_str()];
////        m_tscf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    if( m_techDsp&SV_E_TECH_TSD ) {
////        NSString* t_str = [NSString stringWithFormat:@"%s",m_tsd_name.c_str()];
////        m_tsdf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
//    //状态切换
//    
//    //
    
}
