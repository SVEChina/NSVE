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
#include "../base/SVDataChunk.h"

using namespace sv;

SVShader::SVShader(SVInstPtr _app)
:SVGBaseEx(_app)
,m_res_shader(nullptr){
}

SVShader::~SVShader() {
    m_samplers.clear();
    m_res_shader = nullptr;
    for(s32 i=0;i<m_paramtbl.size();i++) {
        m_paramtbl[i].m_tbl = nullptr;
    }
    m_paramtbl.clear();
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

void SVShader::submitParam(SVParamTblPtr _param) {
    if(!_param) {
        return;
    }
    //将参数表中所有数值都写入本身的参数表中
    for(s32 i=0;i<_param->m_param_dsps.size();i++) {
        SVParamDsp* t_dsp = &(_param->m_param_dsps[i]);
        if(t_dsp->m_type == SV_INT) {
            s32 t_value = 0;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }else if(t_dsp->m_type == SV_FLOAT) {
            f32 t_value = 0;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }else if(t_dsp->m_type == SV_FVEC2) {
            FVec2 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }else if(t_dsp->m_type == SV_FVEC3) {
            FVec3 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }else if(t_dsp->m_type == SV_FVEC4) {
            FVec4 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }else if(t_dsp->m_type == SV_FMAT2) {
            FMat2 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }else if(t_dsp->m_type == SV_FMAT3) {
            FMat3 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }else if(t_dsp->m_type == SV_FMAT4) {
            FMat4 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_paramtbl.size();j++) {
                m_paramtbl[j].m_tbl->setParam(t_dsp->m_name.c_str(), t_value);
            }
        }
    }
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
    if( item.HasMember("formate")  && item["formate"].IsArray() ) {
        RAPIDJSON_NAMESPACE::Document::Array t_formate = item["formate"].GetArray();
        for(s32 i=0;i<t_formate.Size();i++) {
            SVString t_str = t_formate[i].GetString();
            std::map<std::string,s32>::iterator it = SVJsonDef::g_vf_name.find( t_str.c_str() );
            if(it!=SVJsonDef::g_vf_name.end()) {
                m_shader_dsp.m_vft.push_back(it->second);
            }
        }
    }
    //解析vs
    if (item.HasMember("vs") && item["vs"].IsObject() ) {
        m_shader_dsp.m_dsp |= SV_E_TECH_VS;
        //函数入口
        RAPIDJSON_NAMESPACE::Document::Object vs_obj = item["vs"].GetObject();
        m_shader_dsp.m_vs_fname = vs_obj["entry"].GetString();
        //采样器
        if( vs_obj.HasMember("sampler")  && vs_obj["sampler"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_sampler = vs_obj["sampler"].GetArray();
            for(s32 i=0;i<t_sampler.Size();i++) {
                SamplerDsp t_sampler_dsp;
                t_sampler_dsp.m_type = 0;
                SamplerDspFromJson(t_sampler[i],t_sampler_dsp);
                m_samplers.push_back(t_sampler_dsp);
            }
        }
        //uniform参数
        if( vs_obj.HasMember("uniform") && vs_obj["uniform"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_uniform = vs_obj["uniform"].GetArray();
            for(s32 i=0;i<t_uniform.Size();i++) {
                ParamTblDsp _dsp;
                _dsp.m_type = 0;
                ParamTblFromJson(t_uniform[i],_dsp);
                m_paramtbl.push_back(_dsp);
            }
        }
    }
    //解析fs
    if (item.HasMember("fs") && item["fs"].IsObject()) {
        m_shader_dsp.m_dsp |= SV_E_TECH_FS;
        //函数入口
        RAPIDJSON_NAMESPACE::Document::Object fs_obj = item["fs"].GetObject();
        m_shader_dsp.m_fs_fname = fs_obj["entry"].GetString();
        //采样器
        if( fs_obj.HasMember("sampler")  && fs_obj["sampler"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_sampler = fs_obj["sampler"].GetArray();
            for(s32 i=0;i<t_sampler.Size();i++) {
                SamplerDsp t_sampler_dsp;
                t_sampler_dsp.m_type = 1;
                SamplerDspFromJson(t_sampler[i],t_sampler_dsp);
                m_samplers.push_back(t_sampler_dsp);
            }
        }
        //uniform参数
        if( fs_obj.HasMember("uniform")  && fs_obj["uniform"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_uniform = fs_obj["uniform"].GetArray();
            for(s32 i=0;i<t_uniform.Size();i++) {
                ParamTblDsp _dsp;
                _dsp.m_type = 1;
                ParamTblFromJson(t_uniform[i],_dsp);
                m_paramtbl.push_back(_dsp);
            }
        }
    }
    //解析gs
    if (item.HasMember("gs") && item["gs"].IsObject()) {
        m_shader_dsp.m_dsp |= SV_E_TECH_GS;
        //函数入口
        RAPIDJSON_NAMESPACE::Document::Object gs_obj = item["gs"].GetObject();
        m_shader_dsp.m_gs_fname = gs_obj["entry"].GetString();
        //采样器
        if( gs_obj.HasMember("sampler")  && gs_obj["sampler"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_sampler = gs_obj["sampler"].GetArray();
            for(s32 i=0;i<t_sampler.Size();i++) {
                SamplerDsp t_sampler_dsp;
                t_sampler_dsp.m_type = 2;
                SamplerDspFromJson(t_sampler[i],t_sampler_dsp);
                m_samplers.push_back(t_sampler_dsp);
            }
        }
        //uniform参数
        if( gs_obj.HasMember("uniform") && gs_obj["uniform"].IsArray() ) {
            RAPIDJSON_NAMESPACE::Document::Array t_uniform = gs_obj["uniform"].GetArray();
            for(s32 i=0;i<t_uniform.Size();i++) {
                ParamTblDsp _dsp;
                _dsp.m_type = 2;
                ParamTblFromJson(t_uniform[i],_dsp);
                m_paramtbl.push_back(_dsp);
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
        if( item.HasMember("chn") && item["chn"].IsInt() ) {
            _dsp.m_chn = item["chn"].GetInt();
        }
        if( item.HasMember("warp-s") && item["warp-s"].GetString() ) {
            _dsp.m_warps = item["warp-s"].GetString();
        }else{
            _dsp.m_warps = "default";
        }
        //
        if( item.HasMember("warp-t") && item["warp-t"].GetString() ) {
            _dsp.m_warpt = item["warp-t"].GetString();
        }else{
            _dsp.m_warpt = "default";
        }
        //
        if( item.HasMember("min") && item["min"].GetString() ) {
            _dsp.m_min = item["min"].GetString();
        }else{
            _dsp.m_min = "default";
        }
        //
        if( item.HasMember("mag") && item["mag"].GetString() ) {
            _dsp.m_mag = item["mag"].GetString();
        }else{
            _dsp.m_mag = "default";
        }
    }
}

void SVShader::ParamTblFromJson(RAPIDJSON_NAMESPACE::Value &item,ParamTblDsp& _dsp) {
    if( !item.IsObject() ) {
        return;
    }
    //buf-id
    if( item.HasMember("bufID") && item["bufID"].IsInt() ) {
        _dsp.m_id = item["bufID"].GetInt();
    }
    //参数列表
    if( item.HasMember("tbl") && item["tbl"].IsArray() ) {
        _dsp.m_tbl = MakeSharedPtr<SVParamTbl>();
        RAPIDJSON_NAMESPACE::Document::Array tbl = item["tbl"].GetArray();
        for(s32 j=0;j<tbl.Size();j++) {
            RAPIDJSON_NAMESPACE::Document::Object param = tbl[j].GetObject();
            SVString t_param_name = param["name"].GetString();
            SVString t_param_type = param["type"].GetString();
            SVString t_param_value = param["value"].GetString();
            _dsp.m_tbl->addParam(t_param_name.c_str(),t_param_type.c_str(),t_param_value.c_str());
        }
    }
}
