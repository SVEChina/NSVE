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
        return ; // error
    }
    NSError *t_errors;
    NSString* t_shader_str = [NSString stringWithUTF8String:(const char*)(_datachunk.getPointer())];
    id<MTLLibrary> t_lib = [t_rm->m_pDevice newLibraryWithSource:t_shader_str options:nullptr error:&t_errors];
    if(t_errors!=nullptr) {
        if(t_errors.code != 4) {
            //code = 4 是警告
            return; //编译出错了
        }
    }
    if( t_shader->m_shader_dsp.m_dsp &SV_E_TECH_VS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_vs_fname.c_str()];
        m_vsf = [t_lib newFunctionWithName:t_str];
        //生成vs采样器
        for(s32 i=0;i<t_shader->m_vs_sampler.size();i++) {
            //生成sampler-dsp
            MTLSamplerDescriptor *samplerDsp = _genSampler(t_shader->m_vs_sampler[i]);
            //生成sampler-state
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
            //生成sampler-dsp
            MTLSamplerDescriptor *samplerDsp = _genSampler(t_shader->m_fs_sampler[i]);
            //生成sampler-state
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
        for(s32 i=0;i<t_shader->m_gs_sampler.size();i++) {
            //生成sampler-dsp
            MTLSamplerDescriptor *samplerDsp = _genSampler(t_shader->m_gs_sampler[i]);
            //生成sampler-state
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
    //
    m_vft = t_shader->m_shader_dsp.m_vft;
    //创建渲染描述
    MTLRenderPipelineDescriptor *t_pl_dsp = [[MTLRenderPipelineDescriptor alloc] init];
    t_pl_dsp.label = @"Simple Pipeline";
    t_pl_dsp.vertexFunction = m_vsf;
    t_pl_dsp.fragmentFunction = m_fsf;
    t_pl_dsp.vertexDescriptor = _genVertexDsp(m_vft);
    t_pl_dsp.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
    t_pl_dsp.depthAttachmentPixelFormat = MTLPixelFormatInvalid;//MTLPixelFormatDepth32Float_Stencil8;
    t_errors = nullptr;
    m_pl_state = [t_rm->m_pDevice newRenderPipelineStateWithDescriptor:t_pl_dsp error:&t_errors];
    if(t_errors!=nullptr) {
        //error
        m_exist = false;
        return ;
    }
    t_pl_dsp = nullptr;
    //
    m_exist = true;
}

MTLSamplerDescriptor* SVRShaderMetal::_genSampler(SamplerDsp& _dsp) {
    MTLSamplerDescriptor *samplerDsp = [MTLSamplerDescriptor new];
    //warp-s
    s32 t_warp_s = SV_V_WRAP_CLAMP; //default
    if( _dsp.m_warps != "default" ) {
      t_warp_s = SVJsonDef::g_sampler_name[_dsp.m_warps.c_str()];
      if(t_warp_s == 0) {
          t_warp_s = SV_V_WRAP_CLAMP;
      }
    }
    if(t_warp_s == SV_V_WRAP_CLAMP) {
      samplerDsp.sAddressMode = MTLSamplerAddressModeClampToEdge;
    }else if(t_warp_s == SV_V_WRAP_BORDER) {
      samplerDsp.sAddressMode = MTLSamplerAddressModeClampToBorderColor;
    }else if(t_warp_s == SV_V_WRAP_REPEAT) {
      samplerDsp.sAddressMode = MTLSamplerAddressModeRepeat;
    }else if(t_warp_s == SV_V_WRAP_MIRROR) {
      samplerDsp.sAddressMode = MTLSamplerAddressModeMirrorRepeat;
    }else if(t_warp_s == SV_V_WRAP_BLACK) {
      samplerDsp.sAddressMode = MTLSamplerAddressModeClampToZero;
    }else if(t_warp_s == SV_V_WRAP_WHITE) {
      samplerDsp.sAddressMode = MTLSamplerAddressModeMirrorClampToEdge;
    }
    //warp-t
    s32 t_warp_t = SV_V_WRAP_CLAMP; //default
    if( _dsp.m_warpt != "default" ) {
      t_warp_t = SVJsonDef::g_sampler_name[_dsp.m_warpt.c_str()];
      if(t_warp_t == 0) {
          t_warp_t = SV_V_WRAP_CLAMP;
      }
    }
    if(t_warp_t == SV_V_WRAP_CLAMP) {
      samplerDsp.tAddressMode = MTLSamplerAddressModeClampToEdge;
    }else if(t_warp_t == SV_V_WRAP_BORDER) {
      samplerDsp.tAddressMode = MTLSamplerAddressModeClampToBorderColor;
    }else if(t_warp_t == SV_V_WRAP_REPEAT) {
      samplerDsp.tAddressMode = MTLSamplerAddressModeRepeat;
    }else if(t_warp_t == SV_V_WRAP_MIRROR) {
      samplerDsp.tAddressMode = MTLSamplerAddressModeMirrorRepeat;
    }else if(t_warp_t == SV_V_WRAP_BLACK) {
      samplerDsp.tAddressMode = MTLSamplerAddressModeClampToZero;
    }else if(t_warp_t == SV_V_WRAP_WHITE) {
      samplerDsp.tAddressMode = MTLSamplerAddressModeMirrorClampToEdge;
    }
    //min-filter
    s32 t_min_filter = SV_V_FILTER_LINEAR;
    if( _dsp.m_min != "default" ) {
      t_min_filter = SVJsonDef::g_sampler_name[_dsp.m_min.c_str()];
      if(t_min_filter == 0) {
          t_min_filter = SV_V_FILTER_LINEAR;
      }
    }
    if(t_min_filter == SV_V_FILTER_NEAREST) {
      samplerDsp.minFilter = MTLSamplerMinMagFilterLinear;
    }else if(t_min_filter == SV_V_FILTER_LINEAR) {
      samplerDsp.minFilter = MTLSamplerMinMagFilterNearest;
    }
    //mag-filter
    s32 t_mag_filter = SV_V_FILTER_LINEAR; //default
    if( _dsp.m_mag != "default" ) {
      t_mag_filter = SVJsonDef::g_sampler_name[_dsp.m_mag.c_str()];
      if(t_mag_filter == 0) {
          t_mag_filter = SV_V_FILTER_LINEAR;
      }
    }
    if(t_mag_filter == SV_V_FILTER_NEAREST) {
      samplerDsp.magFilter = MTLSamplerMinMagFilterLinear;
    }else if(t_mag_filter == SV_V_FILTER_LINEAR) {
      samplerDsp.magFilter = MTLSamplerMinMagFilterNearest;
    }
    return samplerDsp;
}

MTLVertexDescriptor* SVRShaderMetal::_genVertexDsp(VFTYPE _vf) {
    //顶点描述
    MTLVertexDescriptor* t_vert_dsp = [[MTLVertexDescriptor alloc] init];
    s32 t_attri_index = 0;
    s32 t_vert_size = 0;
    s32 t_off = 0;
    if (_vf & D_VF_V2) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 2*sizeof(f32);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_V3) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 3*sizeof(f32);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_NOR) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 3*sizeof(f32);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_TAG) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 3*sizeof(f32);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_BTAG) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 3*sizeof(f32);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_C0) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUChar4;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 4*sizeof(u8);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_T0) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 2*sizeof(f32);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_T1) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 2*sizeof(f32);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_BONE) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUShort4;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 4*sizeof(u16);
       t_off = t_vert_size;
    }
    if (_vf & D_VF_BONE_W) {
       t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat4;
       t_vert_dsp.attributes[t_attri_index].offset = t_off;
       t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
       t_attri_index++;
       t_vert_size += 4*sizeof(f32);
       t_off = t_vert_size;
    }
    // Position Buffer Layout
    t_vert_dsp.layouts[0].stride = t_vert_size;
    //stepRate和stepFunction 在inst技术和tess技术中可以被设置
    t_vert_dsp.layouts[0].stepRate = 1;
    t_vert_dsp.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    return t_vert_dsp;
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
    if(!m_exist) {
        return false;
    }
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(!t_rm) {
        return false;
    }
    if(!m_pl_state) {
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
    if(m_vs_ubuf) {
        
    }
    if(m_fs_ubuf) {
        
    }
    if(m_gs_ubuf) {
        
    }
//    //
//    id<MTLBuffer> m_vs_ubuf;
//    id<MTLBuffer> m_fs_ubuf;
//    id<MTLBuffer> m_gs_ubuf;
    //
    [t_rm->m_pCurEncoder setRenderPipelineState:m_pl_state];
    return true;
}
