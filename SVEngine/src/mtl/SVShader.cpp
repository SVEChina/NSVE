//
// SVShader.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVShader.h"
#include "SVSurface.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRShader.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../base/SVParamTbl.h"
#include "../core/SVVertDef.h"
#include "../base/SVDataChunk.h"

using namespace sv;

SVShader::SVShader(SVInstPtr _app)
:SVGBaseEx(_app)
,m_res_shader_id(-1){
}

SVShader::~SVShader() {
    m_res_shader_id = -1;
    m_shader_dsp.m_samplers.clear();
    for(s32 i=0;i<m_shader_dsp.m_paramtbl.size();i++) {
        m_shader_dsp.m_paramtbl[i].m_tbl = nullptr;
    }
    m_shader_dsp.m_paramtbl.clear();
}

SVShaderPtr SVShader::share() {
    return std::dynamic_pointer_cast<SVShader>(shareObject()) ;
}

void SVShader::dispatch() {
    SVDispatch::dispatchShaderCreate(mApp, share());
}

//渲染内核
void SVShader::bindRes(s32 _instid) {
    m_res_shader_id = _instid;
}

void SVShader::unbindRes() {
    m_res_shader_id = -1;
}

SVRShaderPtr SVShader::getResShader() {
    if(mApp->getRenderer()) {
        return mApp->getRenderer()->getResShader(m_res_shader_id);
    }
    return nullptr;
}

SVString SVShader::getSamplerName(s32 stage,s32 _chn) {
    SVString t_name = "";
    for(s32 i = 0; i<m_shader_dsp.m_samplers.size(); i++ ) {
        if( (m_shader_dsp.m_samplers[i].m_stage == stage) && (m_shader_dsp.m_samplers[i].m_chn == _chn) ) {
            t_name = m_shader_dsp.m_samplers[i].m_name;
            break;
        }
    }
    return t_name;
}

//创建一个surface
SVSurfacePtr SVShader::createSurface() {
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
//    if(t_surface) {
//        FMat4 t_mat;
//        t_mat.setIdentity();
//        m_surface->m_tbl->addParam("matModel",t_mat);
//        m_surface->m_tbl->addParam("matV",t_mat);
//        m_surface->m_tbl->addParam("matP",t_mat);
//    }
    return t_surface;
}

bool SVShader::active() {
    SVRShaderPtr t_res_shader = getResShader();
    if(t_res_shader && mApp->getRenderer() ) {
        return t_res_shader->active( mApp->getRenderer());
    }
    return false;
}

//更新参数表
void SVShader::submitParam(SVParamTblPtr _param) {
    if(!_param) {
        return;
    }
    //将参数表中所有数值都写入本身的参数表中
    for(s32 i=0;i<_param->m_param_names.size();i++) {
        cptr8 t_param_name = _param->m_param_names[i].c_str();
        SVParamDsp* t_dsp = &(_param->m_param_dsps[i]);
        if(t_dsp->m_type == SV_INT) {
            s32 t_value = 0;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value);
            }
        }else if(t_dsp->m_type == SV_FLOAT) {
            f32 t_value = 0;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value);
            }
        }else if(t_dsp->m_type == SV_FVEC2) {
            FVec2 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value);
            }
        }else if(t_dsp->m_type == SV_FVEC3) {
            FVec3 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value);
            }
        }else if(t_dsp->m_type == SV_FVEC4) {
            FVec4 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value);
            }
        }else if(t_dsp->m_type == SV_FMAT2) {
            FMat2 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value);
            }
        }else if(t_dsp->m_type == SV_FMAT3) {
            FMat3 t_value;
            _param->m_param_values->get(t_dsp->m_off, t_value);
            for(s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value);
            }
        }else if(t_dsp->m_type == SV_FMAT4) {
            SVArray<FMat4> t_value;
            t_value.resize(t_dsp->m_cnt);
            void *t_ret = (void *)t_value.get();
            _param->m_param_values->get(t_dsp->m_off, t_ret, t_dsp->m_cnt * sizeof(FMat4));
            for (s32 j=0;j<m_shader_dsp.m_paramtbl.size();j++) {
                if (t_dsp->m_cnt > 1) {
                    m_shader_dsp.m_paramtbl[j].m_tbl->setParamArray(t_param_name, (FMat4*)t_value.get(), t_dsp->m_cnt);
                } else {
                    m_shader_dsp.m_paramtbl[j].m_tbl->setParam(t_param_name, t_value[0]);
                }
            }
        }
    }
}

bool SVShader::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                      RAPIDJSON_NAMESPACE::Value &_objValue){
    return true;
}

bool SVShader::fromJSON(RAPIDJSON_NAMESPACE::Value &item,cptr8 _language) {
    assert(item.IsObject());
    if( strcmp(_language,"") == 0 ) {
        return false;
    }
    //language = 1
    if( strcmp(_language, "gl") == 0 ) {
        //shader函数入口还有各个文件名称
        if (item.HasMember("vs") && item["vs"].IsString() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_VS;
            m_shader_dsp.m_vs_fname = item["vs"].GetString();
        }
        if (item.HasMember("fs") && item["fs"].IsString() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_FS;
            m_shader_dsp.m_fs_fname = item["fs"].GetString();
        }
        if (item.HasMember("gs") && item["gs"].IsString() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_GS;
            m_shader_dsp.m_gs_fname = item["gs"].GetString();
        }
        if (item.HasMember("tse") && item["tse"].IsString() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_TSE;
            m_shader_dsp.m_tse_fname = item["tse"].GetString();
        }
        if (item.HasMember("tsd") && item["tsd"].IsString() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_TSD;
            m_shader_dsp.m_tsd_fname = item["tsd"].GetString();
        }
        //
    }else if(strcmp(_language, "metal") == 0) {
        if (item.HasMember("file") && item["file"].IsString()) {
            m_shader_dsp.m_programme_fname = item["file"].GetString();
        }else{
            return false;
        }
        //shader函数入口
        if (item.HasMember("vs") && item["vs"].IsInt() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_VS;
        }
        if (item.HasMember("fs") && item["fs"].IsInt() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_FS;
        }
        if (item.HasMember("gs") && item["gs"].IsInt() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_GS;
        }
        if (item.HasMember("tse") && item["tse"].IsInt() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_TSE;
        }
        if (item.HasMember("tsd") && item["tsd"].IsInt() ) {
            m_shader_dsp.m_dsp |= SV_E_TECH_TSD;
        }
    }
    //pass序列
    if( item.HasMember("pass")  && item["pass"].IsString() ) {
        m_shader_dsp.m_pass = item["pass"].GetString();
    }
    //顶点格式描述
    if( item.HasMember("vdsp")  && item["vdsp"].IsArray() ) {
        RAPIDJSON_NAMESPACE::Document::Array t_formate = item["vdsp"].GetArray();
        for(s32 i=0;i<t_formate.Size();i++) {
            SVString t_str = t_formate[i].GetString();
            std::map<std::string,s32>::iterator it = SVJsonDef::g_vf_name.find( t_str.c_str() );
            if(it!=SVJsonDef::g_vf_name.end()) {
                m_shader_dsp.m_vft.push_back(it->second);
            }
        }
    }
    //采样器
    if( item.HasMember("sampler")  && item["sampler"].IsArray() ) {
        RAPIDJSON_NAMESPACE::Document::Array t_sampler = item["sampler"].GetArray();
        for(s32 i=0;i<t_sampler.Size();i++) {
            SamplerDsp t_sampler_dsp;
            SamplerDspFromJson(t_sampler[i],t_sampler_dsp);
            m_shader_dsp.m_samplers.push_back(t_sampler_dsp);
        }
    }
    //uniform参数
    if( item.HasMember("uniform") && item["uniform"].IsArray() ) {
        RAPIDJSON_NAMESPACE::Document::Array t_uniform = item["uniform"].GetArray();
        for(s32 i=0;i<t_uniform.Size();i++) {
            ParamTblDsp _dsp;
            ParamTblFromJson(t_uniform[i],_dsp);
            m_shader_dsp.m_paramtbl.push_back(_dsp);
        }
    }
    return true;
}

/**
 static function
 */

void SVShader::SamplerDspFromJson(RAPIDJSON_NAMESPACE::Value &item,SamplerDsp& _dsp) {
    if( item.IsObject() ) {
        //buf-stage
        if( item.HasMember("stage") && item["stage"].IsInt() ) {
            _dsp.m_stage = item["stage"].GetInt();
        }
        if( item.HasMember("chn") && item["chn"].IsInt() ) {
            _dsp.m_chn = item["chn"].GetInt();
        }
        if( item.HasMember("name") && item["name"].GetString() ) {
            _dsp.m_name = item["name"].GetString();
        }else{
            _dsp.m_name = "";
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
    //buf-stage
    if( item.HasMember("stage") && item["stage"].IsInt() ) {
        _dsp.m_stage = item["stage"].GetInt();
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
