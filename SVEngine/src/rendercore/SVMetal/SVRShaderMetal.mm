//
// SVRShaderMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRShaderMetal.h"
#include "SVRendererMetal.h"
#include "../../mtl/SVShader.h"
#include "../../base/SVParamTbl.h"
#include "../../app/SVInst.h"
#include "../../file/SVFileMgr.h"

using namespace sv;

SVRShaderMetal::SVRShaderMetal(SVInstPtr _app)
:SVRShader(_app){
    m_vsf = nullptr;
    m_gsf = nullptr;
    m_tscf = nullptr;
    m_tsdf = nullptr;
    m_fsf = nullptr;
    m_csf = nullptr;
    //
    m_pl_state = nullptr;
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
    bool t_ret = mApp->m_pFileMgr->loadFileContentStr(&_datachunk, t_shader->m_shader_dsp.m_programme_fname.c_str());
    if(!t_ret){
        // error
        return ;
    }
    NSError *t_errors;
    NSString* t_shader_str = [NSString stringWithUTF8String:(const char*)(_datachunk.getPointer())];
    id<MTLLibrary> t_lib = [t_rm->m_pDevice newLibraryWithSource:t_shader_str options:nullptr error:&t_errors];
    if(t_errors!=nullptr) {
        //编译出错了
        return;
    }
    if( t_shader->m_shader_dsp.m_dsp &SV_E_TECH_VS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_vs_fname.c_str()];
        m_vsf = [t_lib newFunctionWithName:t_str];
        //生成vs采样器
        for(s32 i=0;i<t_shader->m_vs_sampler.size();i++) {
            MTLSamplerDescriptor *samplerDsp = [MTLSamplerDescriptor new];
            samplerDsp.minFilter = MTLSamplerMinMagFilterLinear;
            samplerDsp.magFilter = MTLSamplerMinMagFilterLinear;
            samplerDsp.sAddressMode = MTLSamplerAddressModeRepeat;
            samplerDsp.tAddressMode = MTLSamplerAddressModeRepeat;
            id<MTLSamplerState> t_sampler_state = [t_rm->m_pDevice newSamplerStateWithDescriptor:samplerDsp];
            m_vs_sampler_st.push_back(t_sampler_state);
        }
        //
        if(t_shader->m_vs_paramtbl) {
            void* t_pointer = t_shader->m_vs_paramtbl->getDataPointer();
            s32 t_len = t_shader->m_vs_paramtbl->getDataSize();
            m_vs_ubuf = [t_rm->m_pDevice newBufferWithBytes:t_pointer length: t_len options: MTLResourceStorageModeShared ];
        }
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_FS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_fs_fname.c_str()];
        m_fsf = [t_lib newFunctionWithName:t_str];
        //生成fs采样器
        for(s32 i=0;i<t_shader->m_fs_sampler.size();i++) {
            MTLSamplerDescriptor *samplerDsp = [MTLSamplerDescriptor new];
            samplerDsp.minFilter = MTLSamplerMinMagFilterLinear;
            samplerDsp.magFilter = MTLSamplerMinMagFilterLinear;
            samplerDsp.sAddressMode = MTLSamplerAddressModeRepeat;
            samplerDsp.tAddressMode = MTLSamplerAddressModeRepeat;
            id<MTLSamplerState> t_sampler_state = [t_rm->m_pDevice newSamplerStateWithDescriptor:samplerDsp];
            m_fs_sampler_st.push_back(t_sampler_state);
        }
        //
        if(t_shader->m_fs_paramtbl) {
            void* t_pointer = t_shader->m_fs_paramtbl->getDataPointer();
            s32 t_len = t_shader->m_fs_paramtbl->getDataSize();
            m_fs_ubuf = [t_rm->m_pDevice newBufferWithBytes:t_pointer length: t_len options: MTLResourceStorageModeShared ];
        }
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_GS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_gs_fname.c_str()];
        m_gsf = [t_lib newFunctionWithName:t_str];
        //生成gs采样器
        for(s32 i=0;i<t_shader->m_vs_sampler.size();i++) {
            MTLSamplerDescriptor *samplerDsp = [MTLSamplerDescriptor new];
            samplerDsp.minFilter = MTLSamplerMinMagFilterLinear;
            samplerDsp.magFilter = MTLSamplerMinMagFilterLinear;
            samplerDsp.sAddressMode = MTLSamplerAddressModeRepeat;
            samplerDsp.tAddressMode = MTLSamplerAddressModeRepeat;
            id<MTLSamplerState> t_sampler_state = [t_rm->m_pDevice newSamplerStateWithDescriptor:samplerDsp];
            m_gs_sampler_st.push_back(t_sampler_state);
        }
        //
        if(t_shader->m_gs_paramtbl) {
            //
        }
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_TSE ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_tsc_fname.c_str()];
        m_tscf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_TSD ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_tse_fname.c_str()];
        m_tsdf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    
    //创建渲染描述
    MTLRenderPipelineDescriptor *t_pl_dsp = [[MTLRenderPipelineDescriptor alloc] init];
    t_pl_dsp.label = @"Simple Pipeline";
    t_pl_dsp.vertexFunction = m_vsf;
    t_pl_dsp.fragmentFunction = m_fsf;
    t_pl_dsp.colorAttachments[0].pixelFormat = MTLPixelFormatRGBA8Unorm;
    NSError* t_error;
    m_pl_state = [t_rm->m_pDevice newRenderPipelineStateWithDescriptor:t_pl_dsp error:&t_error];
    t_pl_dsp = nullptr;
    //
    m_exist = true;
}
           
void SVRShaderMetal::destroy(SVRendererPtr _renderer) {
    //采样器销毁
    for(s32 i=0;i<m_vs_sampler_st.size();i++) {
    }
    m_vs_sampler_st.clear();
    //
    for(s32 i=0;i<m_fs_sampler_st.size();i++) {
    }
    m_fs_sampler_st.clear();
    //
    for(s32 i=0;i<m_gs_sampler_st.size();i++) {
    }
    m_gs_sampler_st.clear();
    //
    if(m_pl_state!=nullptr) {
    }
}

bool SVRShaderMetal::active(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(!t_rm) {
        return false;
    }
    //设置采样器
    for(s32 i=0;i<m_vs_sampler_st.size();i++) {
        [t_rm->m_pCurEncoder setVertexSamplerState:m_vs_sampler_st[i] atIndex:i];
    }
    //
    for(s32 i=0;i<m_fs_sampler_st.size();i++) {
        [t_rm->m_pCurEncoder setFragmentSamplerState:m_fs_sampler_st[i] atIndex:i];
    }
    //
    for(s32 i=0;i<m_gs_sampler_st.size();i++) {
        //[t_rm->m_pCurEncoder setFragmentSamplerState:m_gs_sampler_st[i] atIndex:i];
    }
    //
    [t_rm->m_pCurEncoder setRenderPipelineState:m_pl_state];
    return true;
}
