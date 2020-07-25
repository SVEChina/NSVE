//
// SVRShaderMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRShaderMetal.h"
#include "SVRendererMetal.h"
#include "../../mtl/SVShader.h"
#include "../../app/SVInst.h"
#include "../../file/SVFileMgr.h"

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
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(!t_rm) {
        return;
    }
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return ;
    }
    //同步创建
    SVDataChunk _datachunk;
    bool t_ret = mApp->m_pFileMgr->loadFileContentStr(&_datachunk, t_shader->m_dsp.m_programme_fname.c_str());
    if(!t_ret){
        // error
        return ;
    }
    NSError *t_errors;
//    NSString* t_shader_str = [NSString stringWithUTF8String:t_shader->m_dsp.m_programme_fname.c_str()];
//    id<MTLLibrary> t_lib = [t_rm->m_pDevice newLibraryWithFile:t_shader_str error:&t_errors];
    NSString* t_shader_str = [NSString stringWithUTF8String:(const char*)(_datachunk.getPointer())];
    id<MTLLibrary> t_lib = [t_rm->m_pDevice newLibraryWithSource:t_shader_str options:nullptr error:&t_errors];
    if(t_errors!=nullptr) {
        //编译出错了
        return;
    }
    if( t_shader->m_dsp.m_dsp &SV_E_TECH_VS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_dsp.m_vs_fname.c_str()];
        m_vsf = [t_lib newFunctionWithName:t_str];
    }
    if( t_shader->m_dsp.m_dsp&SV_E_TECH_FS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_dsp.m_fs_fname.c_str()];
        m_fsf = [t_lib newFunctionWithName:t_str];
    }
    if( t_shader->m_dsp.m_dsp&SV_E_TECH_GS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_dsp.m_gs_fname.c_str()];
        m_gsf = [t_lib newFunctionWithName:t_str];
    }
//    if( m_shader_dsp&SV_E_TECH_CS ) {
//        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_param.m_cs_fname.c_str()];
//        m_csf = [t_rm->m_pLibrary newFunctionWithName:t_str];
//    }
    if( t_shader->m_dsp.m_dsp&SV_E_TECH_TSC ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_dsp.m_tsc_fname.c_str()];
        m_tscf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    if( t_shader->m_dsp.m_dsp&SV_E_TECH_TSD ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_dsp.m_tse_fname.c_str()];
        m_tsdf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    m_exist = true;
}
           
void SVRShaderMetal::destroy(SVRendererPtr _renderer) {
    
}

bool SVRShaderMetal::active(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(!t_rm) {
        return false;
    }
//    MTLRenderPipelineDescriptor *renderPipelineDesc = [[MTLRenderPipelineDescriptor alloc] init];
//    renderPipelineDesc.vertexFunction = vertFunc;
//    renderPipelineDesc.fragmentFunction = fragFunc;
//    renderPipelineDesc.colorAttachments[0].pixelFormat = currentTexture.pixelFormat;
//    id  pipeline = [device newRenderPipelineStateWithDescriptor:renderPipelineDesc error:&errors];
//    [renderEncoder setRenderPipelineState:pipeline];
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
