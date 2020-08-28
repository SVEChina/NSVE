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
    //
    SVDataChunk tDataStream;
    SV_LOG_ERROR("load shadercfg.json begin\n");
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, "shader/shadercfg.json");
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
    
    //name
    
    //获取文件列表
    RAPIDJSON_NAMESPACE::Value &dspfiles = doc["dspfiles"];
    if( dspfiles.IsArray() ) {
        RAPIDJSON_NAMESPACE::Document::Array t_files = dspfiles.GetArray();
        for(s32 i=0;i<t_files.Size();i++) {
            SVString t_filename = t_files[i].GetString();
            loadSDSP(t_filename.c_str());
        }
    }
    SV_LOG_DEBUG("load shader end\n");
}

void SVShaderMgr::loadSDSP(cptr8 _sdsp) {
    SVDataChunk tDataStream;
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, _sdsp);
    if (!tflag) {
        SV_LOG_INFO("not find _sdsp file!please check shader file path!\n");
        return ;
    }
    SV_LOG_ERROR("file context %s \n", tDataStream.getPointerChar());
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d \n", code);
        return ;
    }
    //
    s32 t_shader_language = 1;
    if ( doc.HasMember("shadertype") && doc["shadertype"].IsString() ) {
        RAPIDJSON_NAMESPACE::Value &shadertype = doc["shadertype"];
        SVString t_shadertype_str = shadertype.GetString();
        if(t_shadertype_str == "metal") {
            t_shader_language = 2;
        }
    }
    //
    if ( doc.HasMember("name") && doc["name"].IsString() ) {
        RAPIDJSON_NAMESPACE::Value &shadername = doc["name"];
        SVShaderPtr t_shader = MakeSharedPtr<SVShader>(mApp);
        if( t_shader->fromJSON( doc ) ) {
            m_shaderMap.insert(std::make_pair(shadername.GetString(), t_shader));
            SVDispatch::dispatchShaderCreate(mApp,t_shader);
        }
    }
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
