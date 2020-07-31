//
// SVShaderMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVShaderMgr.h"
#include "SVShader.h"
#include "../file/SVFileMgr.h"
#include "../base/SVDataChunk.h"
#include "../app/SVInst.h"
#include "../app/SVGlobalParam.h"
#include "../app/SVDispatch.h"
#include "../third/rapidjson/document.h"
#include "../third/rapidjson/stringbuffer.h"
#include "../third/rapidjson/writer.h"
#include "SVMtlLib.h"


using namespace sv;

SVShaderMgr::SVShaderMgr(SVInstPtr _app)
:SVSysBase(_app) {
}

SVShaderMgr::~SVShaderMgr() {
}

void SVShaderMgr::init() {
    _loadAllShader();    //加载表
}

void SVShaderMgr::destroy() {
    _clearAllShader();
}

void SVShaderMgr::_loadAllShader() {
    SVDataChunk tDataStream;
    SV_LOG_ERROR("load shadercfg.json begin\n");
    bool tflag = mApp->getFileMgr()->loadFileContentStr(&tDataStream, "shader/shadercfg.json");
    if (!tflag) {
        SV_LOG_INFO("not find shadercfg.json!please check shader file path!\n");
        return;
    }
    SV_LOG_ERROR("file context %s \n", tDataStream.getPointerChar());
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d \n", code);
        return;
    }
    s32 t_shader_language = 1;
    RAPIDJSON_NAMESPACE::Value &shadertype = doc["shadertype"];
    if( shadertype.IsString() ) {
        SVString t_shadertype_str = shadertype.GetString();
        if(t_shadertype_str == "metal") {
            t_shader_language = 2;
        }
    }
    //"shadertype" :"metal",
    RAPIDJSON_NAMESPACE::Value &shader = doc["shader"];
    if (shader.IsArray()) {
        for (s32 i = 0; i < shader.Size(); ++i) {
            if(t_shader_language == 2) {
                //metal的解析方式
                RAPIDJSON_NAMESPACE::Value &shaderitem = shader[i];
                assert(shaderitem.IsObject());
                SVString t_shader_name = "";
                SVString t_file_name = "";
                if (shaderitem.HasMember("file") && shaderitem["file"].IsString()) {
                    t_shader_name = shaderitem["file"].GetString();
                    t_file_name = SVString("shader/") + t_shader_name + ".metal";
                }else{
                    break;
                }
                SVShaderPtr t_shader = MakeSharedPtr<SVShader>(mApp);
                if(t_shader) {
                    //
                    t_shader->m_dsp.m_programme_fname = t_file_name;
                    //解析vs
                    if (shaderitem.HasMember("vs") && shaderitem["vs"].IsObject() ) {
                        RAPIDJSON_NAMESPACE::Document::Object vs_obj = shaderitem["vs"].GetObject();
                        t_shader->m_dsp.m_vs_fname = vs_obj["entry"].GetString();
                        //采样器
                        if( vs_obj.HasMember("sampler")  && vs_obj["sampler"].IsArray() ) {
                            RAPIDJSON_NAMESPACE::Document::Array t_sampler = vs_obj["sampler"].GetArray();
                            for(s32 i=0;i<t_sampler.Size();i++) {
                                SamplerDsp t_sampler_dsp;
                                t_sampler_dsp.m_chn = t_sampler[i]["chn"].GetInt();
                                t_sampler_dsp.m_warps = t_sampler[i]["warps"].GetString();
                                t_sampler_dsp.m_warpt = t_sampler[i]["warpt"].GetString();
                                t_sampler_dsp.m_min = t_sampler[i]["min"].GetString();
                                t_sampler_dsp.m_mag = t_sampler[i]["mag"].GetString();
                                t_shader->m_vs_sampler.push_back(t_sampler_dsp);
                            }
                        }
                    }
                    //解析fs
                    if (shaderitem.HasMember("fs") && shaderitem["fs"].IsObject()) {
                        RAPIDJSON_NAMESPACE::Document::Object fs_obj = shaderitem["fs"].GetObject();
                        t_shader->m_dsp.m_fs_fname = fs_obj["entry"].GetString();
                        //采样器
                        if( fs_obj.HasMember("sampler")  && fs_obj["sampler"].IsArray() ) {
                            RAPIDJSON_NAMESPACE::Document::Array t_sampler = fs_obj["sampler"].GetArray();
                            for(s32 i=0;i<t_sampler.Size();i++) {
                                SamplerDsp t_sampler_dsp;
                                t_sampler_dsp.m_chn = t_sampler[i]["chn"].GetInt();
                                t_sampler_dsp.m_warps = t_sampler[i]["warps"].GetString();
                                t_sampler_dsp.m_warpt = t_sampler[i]["warpt"].GetString();
                                t_sampler_dsp.m_min = t_sampler[i]["min"].GetString();
                                t_sampler_dsp.m_mag = t_sampler[i]["mag"].GetString();
                                t_shader->m_fs_sampler.push_back(t_sampler_dsp);
                            }
                        }
                    }
                    //解析gs
                    if (shaderitem.HasMember("gs") && shaderitem["gs"].IsObject()) {
                        RAPIDJSON_NAMESPACE::Document::Object gs_obj = shaderitem["gs"].GetObject();
                        t_shader->m_dsp.m_gs_fname = gs_obj["entry"].GetString();
                        //采样器
                        if( gs_obj.HasMember("sampler")  && gs_obj["sampler"].IsArray() ) {
                            RAPIDJSON_NAMESPACE::Document::Array t_sampler = gs_obj["sampler"].GetArray();
                            for(s32 i=0;i<t_sampler.Size();i++) {
                                //
                            }
                        }
                    }
                    if (shaderitem.HasMember("tsd") && shaderitem["tsd"].IsObject()) {
                        RAPIDJSON_NAMESPACE::Document::Object tsd_obj = shaderitem["tsd"].GetObject();
                        t_shader->m_dsp.m_tsc_fname = tsd_obj["entry"].GetString();
                    }
                    if (shaderitem.HasMember("tse") && shaderitem["tse"].IsObject()) {
                        RAPIDJSON_NAMESPACE::Document::Object tse_obj = shaderitem["tse"].GetObject();
                        t_shader->m_dsp.m_tse_fname = tse_obj["entry"].GetString();
                    }
                    //
                    if(t_shader->m_dsp.m_vs_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_VS;
                    }
                    if(t_shader->m_dsp.m_fs_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_FS;
                    }
                    if(t_shader->m_dsp.m_gs_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_GS;
                    }
                    if(t_shader->m_dsp.m_tsc_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_TSC;
                    }
                    if(t_shader->m_dsp.m_tse_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_TSD;
                    }
                    //创建shader
                    m_shaderMap.insert( std::make_pair(t_shader_name, t_shader) );
                    SVDispatch::dispatchShaderCreate(mApp,t_shader);
                    //SV_LOG_ERROR("shader : vs(%s) fs(%s)\n", t_vs_fname.c_str(),t_fs_fname.c_str());
                }
                
            }else if(t_shader_language == 1) {
                //glsl解析方式
                RAPIDJSON_NAMESPACE::Value &shaderitem = shader[i];
                assert(shaderitem.IsObject());
                SVString t_vs_fname = "";
                SVString t_fs_fname = "";
                SVString t_gs_fname = "";
                SVString t_cs_fname = "";
                SVString t_tsc_fname = "";
                SVString t_tse_fname = "";
                SVString t_programme_name = "";
                if (shaderitem.HasMember("vs") && shaderitem["vs"].IsString()) {
                    t_vs_fname = shaderitem["vs"].GetString();
                    t_vs_fname = SVString("shader/") + t_vs_fname + ".vs";
                }
                if (shaderitem.HasMember("fs") && shaderitem["fs"].IsString()) {
                    t_fs_fname = shaderitem["fs"].GetString();
                    t_fs_fname = SVString("shader/") + t_fs_fname + ".fs";
                }
                if (shaderitem.HasMember("programme") && shaderitem["programme"].IsString()) {
                    t_programme_name = shaderitem["programme"].GetString();
                }
                //顶点格式描述
                SVString t_attri_formate = "all";
                if (shaderitem.HasMember("af") && shaderitem["af"].IsString()) {
                    t_attri_formate = shaderitem["af"].GetString();
                }
                //
                SVShaderPtr t_shader = MakeSharedPtr<SVShader>(mApp);
                if(t_shader) {
                    m_shaderMap.insert( std::make_pair(t_programme_name, t_shader) );
                    //
                    t_shader->m_dsp.m_attri_formate = t_attri_formate;
                    t_shader->m_dsp.m_vs_fname = t_vs_fname;
                    t_shader->m_dsp.m_fs_fname = t_fs_fname;
                    t_shader->m_dsp.m_gs_fname = t_gs_fname;
                    t_shader->m_dsp.m_cs_fname = t_cs_fname;
                    t_shader->m_dsp.m_tsc_fname = t_tsc_fname;
                    t_shader->m_dsp.m_tse_fname = t_tse_fname;
                    t_shader->m_dsp.m_programme_fname = t_programme_name;
                    //
                    if(t_vs_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_VS;
                    }
                    if(t_fs_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_FS;
                    }
                    if(t_gs_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_GS;
                    }
                    if(t_tsc_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_TSC;
                    }
                    if(t_tse_fname!="null") {
                        t_shader->m_dsp.m_dsp |= SV_E_TECH_TSD;
                    }
                    //创建shader
                    SVDispatch::dispatchShaderCreate(mApp,t_shader);
                    SV_LOG_ERROR("shader : vs(%s) fs(%s)\n", t_vs_fname.c_str(),t_fs_fname.c_str());
                }
            }
        }
    }
    SV_LOG_DEBUG("load shader end\n");
}

void SVShaderMgr::_clearAllShader() {
    m_shaderMap.clear();
}

SVShaderPtr SVShaderMgr::getShader(cptr8 _name) {
    SHADERPOOL::iterator it = m_shaderMap.find(_name);
    if(it!=m_shaderMap.end()) {
        return it->second;
    }
    return nullptr;
}
