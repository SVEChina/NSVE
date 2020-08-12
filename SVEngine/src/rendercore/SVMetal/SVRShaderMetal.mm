//
// SVRShaderMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRShaderMetal.h"
#include "SVRendererMetal.h"
#include "../../mtl/SVShader.h"
#include "../../mtl/SVSurface.h"
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
    //函数入口
    if( t_shader->m_shader_dsp.m_dsp &SV_E_TECH_VS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_vs_fname.c_str()];
        m_vsf = [t_lib newFunctionWithName:t_str];
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_FS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_fs_fname.c_str()];
        m_fsf = [t_lib newFunctionWithName:t_str];
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_GS ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_gs_fname.c_str()];
        m_gsf = [t_lib newFunctionWithName:t_str];
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_TSE ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_tsc_fname.c_str()];
        m_tscf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_TSD ) {
        NSString* t_str = [NSString stringWithFormat:@"%s",t_shader->m_shader_dsp.m_tse_fname.c_str()];
        m_tsdf = [t_rm->m_pLibrary newFunctionWithName:t_str];
    }
    //生成vs采样器(都在一起)
    for(s32 i=0;i<t_shader->m_samplers.size();i++) {
        INSAMPLE t_sampler;
        //生成sampler-dsp
        MTLSamplerDescriptor *samplerDsp = _genSampler(t_shader->m_samplers[i]);
        //生成sampler-state
        t_sampler.m_st = [t_rm->m_pDevice newSamplerStateWithDescriptor:samplerDsp];
        t_sampler.m_chn = t_shader->m_samplers[i].m_chn;
        t_sampler.m_stage = t_shader->m_samplers[i].m_stage;
        m_sampler_st.push_back(t_sampler);
    }
    //生成uniform-buf
    for(s32 i=0;i<t_shader->m_paramtbl.size();i++) {
        void* t_pointer = t_shader->m_paramtbl[i].m_tbl->getDataPointer();
        s32 t_len = t_shader->m_paramtbl[i].m_tbl->getDataSize();
        UBUF t_ubuf;
        t_ubuf.m_bufid = t_shader->m_paramtbl[i].m_id;
        t_ubuf.m_stage = t_shader->m_paramtbl[i].m_stage;
        t_ubuf.m_ubuf = [t_rm->m_pDevice newBufferWithBytes:t_pointer length: t_len options: MTLResourceStorageModeShared ];
        m_ubuf_pool.push_back(t_ubuf);
    }
    //创建渲染描述
    MTLRenderPipelineDescriptor *t_pl_dsp = [[MTLRenderPipelineDescriptor alloc] init];
    t_pl_dsp.label = @"Simple Pipeline";
    t_pl_dsp.vertexFunction = m_vsf;
    t_pl_dsp.fragmentFunction = m_fsf;
    t_pl_dsp.vertexDescriptor = _genVertexDsp(E_BFM_AOS);
    t_pl_dsp.colorAttachments[0].pixelFormat = MTLPixelFormatRGBA8Unorm;
    if(t_shader->m_shader_dsp.m_post == 1) {
        t_pl_dsp.depthAttachmentPixelFormat = MTLPixelFormatInvalid;
        t_pl_dsp.stencilAttachmentPixelFormat = MTLPixelFormatInvalid;
    }else{
        t_pl_dsp.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
        t_pl_dsp.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    }
    t_errors = nullptr;
    m_pl_state = [t_rm->m_pDevice newRenderPipelineStateWithDescriptor:t_pl_dsp error:&t_errors];
    if(t_errors!=nullptr) {
        m_exist = false;
        return ;
    }
    t_pl_dsp = nullptr;
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

MTLVertexDescriptor* SVRShaderMetal::_genVertexDsp(BUFFERMODE _mode) {
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return nullptr;
    }
    MTLVertexDescriptor* t_vert_dsp = [[MTLVertexDescriptor alloc] init];
    s32 t_attri_index = 0;
    s32 t_vert_size = 0;
    s32 t_off = 0;
    if(_mode == E_BFM_AOS) {
        for(s32 i=0;i<t_shader->m_shader_dsp.m_vft.size();i++) {
            s32 _vf = t_shader->m_shader_dsp.m_vft[i];
            //单一混合流
            if (_vf & SV_SMT_V2) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 2*sizeof(f32);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_V3) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 3*sizeof(f32);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_NOR) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 3*sizeof(f32);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_TAG) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 3*sizeof(f32);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_BTAG) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 3*sizeof(f32);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_C0) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUChar4;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 4*sizeof(u8);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_T0) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 2*sizeof(f32);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_T1) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 2*sizeof(f32);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_BONE) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUShort4;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 4*sizeof(u16);
               t_off = t_vert_size;
            }else if (_vf & SV_SMT_BONE_W) {
               t_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat4;
               t_vert_dsp.attributes[t_attri_index].offset = t_off;
               t_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
               t_attri_index++;
               t_vert_size += 4*sizeof(f32);
               t_off = t_vert_size;
            }
        }
    }else{
        //多流
    }
    // Position Buffer Layout
    t_vert_dsp.layouts[0].stride = t_vert_size;
    //stepRate和stepFunction 在inst技术和tess技术中可以被设置
    t_vert_dsp.layouts[0].stepRate = 1;
    t_vert_dsp.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    return t_vert_dsp;
}

void SVRShaderMetal::destroy(SVRendererPtr _renderer) {
    //in-sampler销毁
    for(s32 i=0;i<m_sampler_st.size();i++) {
    }
    m_sampler_st.clear();
    //u-buf销毁
    //
    if(m_pl_state!=nullptr) {
    }
    //uniform-buf销毁
}

bool SVRShaderMetal::active(SVRendererPtr _renderer) {
    if(!m_exist) {
        return false;
    }
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(!t_rm) {
        return false;
    }
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return false;
    }
    if(!m_pl_state) {
        return false;
    }
    //采样器更新
    for(s32 i=0;i<m_sampler_st.size();i++) {
        if(m_sampler_st[i].m_stage == SV_STAGE_VS) {
            [t_rm->m_pCurEncoder setVertexSamplerState:m_sampler_st[i].m_st atIndex:m_sampler_st[i].m_chn];
        }else if(m_sampler_st[i].m_stage == SV_STAGE_FS) {
            [t_rm->m_pCurEncoder setFragmentSamplerState:m_sampler_st[i].m_st atIndex:m_sampler_st[i].m_chn];
        }
    }
    //替换uniform
    for(s32 i=0;i<t_shader->m_paramtbl.size();i++) {
        void* t_pointer = t_shader->m_paramtbl[i].m_tbl->getDataPointer();
        s32 t_len = t_shader->m_paramtbl[i].m_tbl->getDataSize();
        memcpy( m_ubuf_pool[i].m_ubuf.contents , t_pointer ,t_len);
    }
    //上传uniform
    for(s32 i=0;i<m_ubuf_pool.size();i++) {
        if( m_ubuf_pool[i].m_stage == SV_STAGE_VS ) {
            //vs
            [t_rm->m_pCurEncoder setVertexBuffer:m_ubuf_pool[i].m_ubuf offset:0 atIndex:m_ubuf_pool[i].m_bufid];
        }else if( m_ubuf_pool[i].m_stage == SV_STAGE_FS ) {
            //fs
            [t_rm->m_pCurEncoder setFragmentBuffer:m_ubuf_pool[i].m_ubuf offset:0 atIndex:m_ubuf_pool[i].m_bufid];
        }else if( m_ubuf_pool[i].m_stage == SV_STAGE_GS ) {
            //gs
            //[t_rm->m_pCurEncoder setFragmentBuffer:m_ubuf_pool[i].m_ubuf offset:0 atIndex:m_ubuf_pool[i].m_bufid];
        }
    }
    [t_rm->m_pCurEncoder setRenderPipelineState:m_pl_state];
    return true;
}

void SVRShaderMetal::submitSurface(SVSurfacePtr _surface) {
    if(!_surface) {
        return ;
    }
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return ;
    }
}
