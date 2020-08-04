//
// SVShader.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVShader.h"
#include "../rendercore/SVRShader.h"
#include "../app/SVInst.h"
#include "../base/SVParamTbl.h"
#include "../core/SVVertDef.h"

using namespace sv;

SVShader::SVShader(SVInstPtr _app)
:SVGBaseEx(_app)
,m_res_shader(nullptr)
,m_vs_paramtbl(nullptr)
,m_fs_paramtbl(nullptr)
,m_gs_paramtbl(nullptr){
}

SVShader::~SVShader() {
    m_vs_sampler.clear();
    m_fs_sampler.clear();
    m_gs_sampler.clear();
    m_res_shader = nullptr;
    m_vs_paramtbl = nullptr;
    m_fs_paramtbl = nullptr;
    m_gs_paramtbl = nullptr;
}

//渲染内核
void SVShader::bindRes(SVRShaderPtr _res) {
    m_res_shader = _res;
}

void SVShader::unbindRes() {
    m_res_shader = nullptr;
}

SVRShaderPtr SVShader::getResShader() {
    return m_res_shader;
}

bool SVShader::active() {
    if(m_res_shader && mApp->getRenderer() ) {
        return m_res_shader->active( mApp->getRenderer() );
    }
    return false;
}

bool SVShader::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                      RAPIDJSON_NAMESPACE::Value &_objValue){
    return true;
}

bool SVShader::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
    assert(item.IsObject());
    if (item.HasMember("file") && item["file"].IsString()) {
        m_shader_dsp.m_programme_fname = item["file"].GetString();
    }else{
        return false;
    }
    //
    if( item.HasMember("formate")  && item["formate"].IsString() ) {
        SVString t_formate = item["formate"].GetString();
        std::map<std::string,s32>::iterator it = SVVertDef::g_vf_name.find( t_formate.c_str() );
        if(it!=SVVertDef::g_vf_name.end()) {
           m_shader_dsp.m_vft = VFTYPE(it->second);
        }else{
           m_shader_dsp.m_vft = E_VF_V2;
        }
    }else{
        m_shader_dsp.m_vft = E_VF_V2;
    }
    //解析vs
    if (item.HasMember("vs") && item["vs"].IsObject() ) {
        //
        m_shader_dsp.m_dsp |= SV_E_TECH_VS;
        //
        RAPIDJSON_NAMESPACE::Document::Object vs_obj = item["vs"].GetObject();
        m_shader_dsp.m_vs_fname = vs_obj["entry"].GetString();
        //采样器
        if( vs_obj.HasMember("sampler")  && vs_obj["sampler"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_sampler = vs_obj["sampler"].GetArray();
            for(s32 i=0;i<t_sampler.Size();i++) {
                SamplerDsp t_sampler_dsp;
                SamplerDspFromJson(t_sampler[i],t_sampler_dsp);
                m_vs_sampler.push_back(t_sampler_dsp);
            }
        }
        //uniform参数
        if( vs_obj.HasMember("uniform")  && vs_obj["uniform"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_uniform = vs_obj["uniform"].GetArray();
            for(s32 i=0;i<t_uniform.Size();i++) {
                RAPIDJSON_NAMESPACE::Document::Object element = t_uniform[i].GetObject();
                SVString t_param_name = element["name"].GetString();
                SVString t_param_type = element["type"].GetString();
                SVString t_param_value = element["value"].GetString();
                if(!m_vs_paramtbl) {
                    m_vs_paramtbl = MakeSharedPtr<SVParamTbl>();
                }
                m_vs_paramtbl->addParam(t_param_name.c_str(),t_param_type.c_str(),t_param_value.c_str());
            }
        }
    }
    //解析fs
    if (item.HasMember("fs") && item["fs"].IsObject()) {
        //
        m_shader_dsp.m_dsp |= SV_E_TECH_FS;
        //
        RAPIDJSON_NAMESPACE::Document::Object fs_obj = item["fs"].GetObject();
        m_shader_dsp.m_fs_fname = fs_obj["entry"].GetString();
        //采样器
        if( fs_obj.HasMember("sampler")  && fs_obj["sampler"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_sampler = fs_obj["sampler"].GetArray();
            for(s32 i=0;i<t_sampler.Size();i++) {
                SamplerDsp t_sampler_dsp;
                SamplerDspFromJson(t_sampler[i],t_sampler_dsp);
                m_fs_sampler.push_back(t_sampler_dsp);
            }
        }
        //uniform参数
        if( fs_obj.HasMember("uniform")  && fs_obj["uniform"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_uniform = fs_obj["uniform"].GetArray();
            for(s32 i=0;i<t_uniform.Size();i++) {
                RAPIDJSON_NAMESPACE::Document::Object element = t_uniform[i].GetObject();
                SVString t_param_name = element["name"].GetString();
                SVString t_param_type = element["type"].GetString();
                SVString t_param_value = element["value"].GetString();
                if(!m_fs_paramtbl) {
                    m_fs_paramtbl = MakeSharedPtr<SVParamTbl>();
                }
                m_fs_paramtbl->addParam(t_param_name.c_str(),t_param_type.c_str(),t_param_value.c_str());
            }
        }
    }
    //解析gs
    if (item.HasMember("gs") && item["gs"].IsObject()) {
        //
        m_shader_dsp.m_dsp |= SV_E_TECH_GS;
        //
        RAPIDJSON_NAMESPACE::Document::Object gs_obj = item["gs"].GetObject();
        m_shader_dsp.m_gs_fname = gs_obj["entry"].GetString();
        //采样器
        if( gs_obj.HasMember("sampler")  && gs_obj["sampler"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_sampler = gs_obj["sampler"].GetArray();
            for(s32 i=0;i<t_sampler.Size();i++) {
                //
            }
        }
    }
    //
    if (item.HasMember("tsd") && item["tsd"].IsObject()) {
        m_shader_dsp.m_dsp |= SV_E_TECH_TSD;
        RAPIDJSON_NAMESPACE::Document::Object tsd_obj = item["tsd"].GetObject();
        m_shader_dsp.m_tsc_fname = tsd_obj["entry"].GetString();
    }
    //
    if (item.HasMember("tse") && item["tse"].IsObject()) {
        m_shader_dsp.m_dsp |= SV_E_TECH_TSE;
        RAPIDJSON_NAMESPACE::Document::Object tse_obj = item["tse"].GetObject();
        m_shader_dsp.m_tse_fname = tse_obj["entry"].GetString();
    }
    return true;
}

/**
 static function
 */

void SVShader::SamplerDspFromJson(RAPIDJSON_NAMESPACE::Value &item,SamplerDsp& _dsp) {
    if( item.IsObject() ) {
        _dsp.m_chn = item["chn"].GetInt();
        _dsp.m_warps = item["warp-s"].GetString();
        _dsp.m_warpt = item["warp-t"].GetString();
        _dsp.m_min = item["min"].GetString();
        _dsp.m_mag = item["mag"].GetString();
    }
}
