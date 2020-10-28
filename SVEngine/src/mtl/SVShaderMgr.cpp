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
:SVGBaseEx(_app) {
}

SVShaderMgr::~SVShaderMgr() {
}

void SVShaderMgr::init() {
}

void SVShaderMgr::destroy() {
    _clearAllShader();
}

void SVShaderMgr::loadDefault() {
    _loadShaderDef();
    _loadAllShader();    //加载表
}

void SVShaderMgr::_loadShaderDef() {
    SVDataChunk tDataStream;
    SV_LOG_ERROR("load shaderdef.json begin\n");
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, "shader/shaderdef.json");
    if (!tflag) {
        SV_LOG_INFO("error not find shaderdef.json!n");
        return;
    }
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d \n", code);
        return;
    }
    RAPIDJSON_NAMESPACE::Value &def = doc["def"];
    if( def.IsObject() ) {
        RAPIDJSON_NAMESPACE::Document::MemberIterator it = def.MemberBegin();
        while(it!=def.MemberEnd()) {
            SVString t_key = it->name.GetString();
            s32 t_value = it->value.GetInt();
            m_deftbl.insert(std::make_pair(t_key,t_value));
            it++;
        }
    }
}

void SVShaderMgr::_loadAllShader() {
    SVDataChunk tDataStream;
    SV_LOG_ERROR("load shadercfg.json begin\n");
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, "shader/shadercfg.json");
    if (!tflag) {
        SV_LOG_INFO("error not find shadercfg.json!n");
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
    //
    SVString t_language = "";
    RAPIDJSON_NAMESPACE::Value &language = doc["language"];
    if( language.IsString() ) {
        t_language = language.GetString();
    }
    //获取文件列表
    RAPIDJSON_NAMESPACE::Value &dspfiles = doc["dspfiles"];
    if( dspfiles.IsArray() ) {
        RAPIDJSON_NAMESPACE::Document::Array t_files = dspfiles.GetArray();
        for(s32 i=0;i<t_files.Size();i++) {
            SVString t_filename = t_files[i].GetString();
            loadSDSP(t_filename.c_str(),t_language.c_str());
        }
    }
    SV_LOG_DEBUG("load shader end\n");
}

void SVShaderMgr::loadSDSP(cptr8 _sdsp,cptr8 _language) {
    SVDataChunk tDataStream;
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, _sdsp);
    if (!tflag) {
        SV_LOG_INFO("not find _sdsp file!please check shader file path!\n");
        return ;
    }
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d \n", code);
        return ;
    }
    //
    SVString t_s_name = _sdsp;
    s32 t_pos = t_s_name.rfind('.');
    if(t_pos>0) {
        t_s_name = SVString::substr(t_s_name.c_str(), 0, t_pos);
    }
    t_pos = t_s_name.rfind('\\');
    if(t_pos>0) {
       t_s_name = SVString::substr(t_s_name.c_str(), t_pos+1);
    }
    t_pos = t_s_name.rfind('/');
    if(t_pos>0) {
       t_s_name = SVString::substr(t_s_name.c_str(), t_pos+1);
    }
    //解析
    SVShaderPtr t_shader = MakeSharedPtr<SVShader>(mApp);
    if( t_shader->fromJSON( doc ,_language) ) {
        SVString t_ext = SVString::format("_%d",t_shader->getShaderDsp()->m_pbr_def);
        t_s_name += t_ext;
    }
    //防止重名的shader
    SHADERPOOL::iterator it = m_shaderMap.find(t_s_name);
    if( it == m_shaderMap.end() ) {
        m_shaderMap.insert(std::make_pair(t_s_name, t_shader));
        t_shader->dispatch();
    }
    t_shader = nullptr;
}

void SVShaderMgr::_clearAllShader() {
    m_shaderMap.clear();
}

s32 SVShaderMgr::getDefValue(cptr8 _defname) {
    DEFTBL::iterator it = m_deftbl.find(_defname);
    if(it!=m_deftbl.end()) {
        return it->second;
    }
    return 0;
}

SVShaderPtr SVShaderMgr::getShader(cptr8 _name,s32 _pbrdef) {
    SVString t_name = _name;
    SVString t_ext = SVString::format("_%d",_pbrdef);
    t_name += t_ext;
    SHADERPOOL::iterator it = m_shaderMap.find(t_name.c_str());
    if(it!=m_shaderMap.end()) {
        return it->second;
    }
    return nullptr;
}
