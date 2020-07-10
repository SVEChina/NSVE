//
// SVRShaderMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRShaderMetal.h"
#include "SVRendererMetal.h"
#include "../../mtl/SVShader.h"

using namespace sv;

SVRShaderMetal::SVRShaderMetal(SVInstPtr _app)
:SVRShader(_app){
    m_rp_dsp = nullptr;
    m_vsf = nullptr;
    m_gsf = nullptr;
    m_tscf = nullptr;
    m_tsdf = nullptr;
    m_fsf = nullptr;
    m_csf = nullptr;
}

SVRShaderMetal::~SVRShaderMetal() {
}

void SVRShaderMetal::create(SVRendererPtr _renderer) {
    if(!m_logic_obj) {
        return ;
    }
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return ;
    }
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if( t_shader->m_param.m_dsp &SV_E_TECH_VS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_param.m_vs_fname.c_str()];
        m_vsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    if( t_shader->m_param.m_dsp&SV_E_TECH_FS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_param.m_fs_fname.c_str()];
        m_fsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    if( t_shader->m_param.m_dsp&SV_E_TECH_GS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_param.m_gs_fname.c_str()];
        m_gsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
//    if( m_shader_dsp&SV_E_TECH_CS ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_param.m_cs_fname.c_str()];
//        m_csf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
    if( t_shader->m_param.m_dsp&SV_E_TECH_TSC ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_param.m_tsc_fname.c_str()];
        m_tscf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    if( t_shader->m_param.m_dsp&SV_E_TECH_TSD ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_param.m_tse_fname.c_str()];
        m_tsdf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
        //m_rp_dsp = [[MTLRenderPipelineDescriptor alloc] init];
        //    pipelineStateDescriptor.label = @"Simple Pipeline";
        //    pipelineStateDescriptor.vertexFunction = vertexFunction;
        //    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
        //    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;
        //
        //    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
        //
    m_exist = true;
}
           
void SVRShaderMetal::destroy(SVRendererPtr _renderer) {
    
}

bool SVRShaderMetal::active(SVRendererPtr _render) {
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
////
////    //shader 绑定
////    if( m_techDsp&SV_E_TECH_VS ) {
//////        NSString* t_str = [NSString stringWithFormat:@"%s",m_vs_name.c_str()];
//////        m_vsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
////    }
////    if( m_techDsp&SV_E_TECH_FS ) {
//////        NSString* t_str = [NSString stringWithFormat:@"%s",m_fs_name.c_str()];
//////        m_fsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
////    }
////    if( m_techDsp&SV_E_TECH_GS ) {
//////        NSString* t_str = [NSString stringWithFormat:@"%s",m_gs_name.c_str()];
//////        m_gsf = [t_rm->m_pLibrary newFunctionWithName:t_str];
////    }
////    if( m_techDsp&SV_E_TECH_CS ) {
//////        NSString* t_str = [NSString stringWithFormat:@"%s",m_cs_name.c_str()];
//////        m_csf = [t_rm->m_pLibrary newFunctionWithName:t_str];
////    }
////    if( m_techDsp&SV_E_TECH_TSC ) {
//////        NSString* t_str = [NSString stringWithFormat:@"%s",m_tsc_name.c_str()];
//////        m_tscf = [t_rm->m_pLibrary newFunctionWithName:t_str];
////    }
////    if( m_techDsp&SV_E_TECH_TSD ) {
//////        NSString* t_str = [NSString stringWithFormat:@"%s",m_tsd_name.c_str()];
//////        m_tsdf = [t_rm->m_pLibrary newFunctionWithName:t_str];
////    }
////    //状态切换
////
////    //
//
//}
