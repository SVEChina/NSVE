//
// IMIShaderMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIShaderMgr.h"
#include "IMIShader.h"
#include "../file/IMIFileMgr.h"
#include "../base/IMIDataChunk.h"
#include "../app/IMIInst.h"
#include "../app/IMIGlobalParam.h"
#include "../app/IMIDispatch.h"
#include "../third/rapidjson/document.h"
#include "../third/rapidjson/stringbuffer.h"
#include "../third/rapidjson/writer.h"
#include "IMIMtlLib.h"


using namespace imi;

IMIShaderMgr::IMIShaderMgr(IMIInstPtr _app)
:IMIGBaseEx(_app) {
}

IMIShaderMgr::~IMIShaderMgr() {
}

void IMIShaderMgr::init() {
    m_language = "";
}

void IMIShaderMgr::destroy() {
    _clearAllShader();
}

void IMIShaderMgr::loadDefault() {
    _loadShaderDef();
    _loadAllShader();    //加载表
}

void IMIShaderMgr::_loadShaderDef() {
    IMIDataChunk tDataStream;
    IMI_LOG_ERROR("load shaderdef.json begin\n");
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, "shader/shaderdef.json");
    if (!tflag) {
        IMI_LOG_INFO("error not find shaderdef.json!n");
        return;
    }
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        IMI_LOG_ERROR("rapidjson error code:%d \n", code);
        return;
    }
    RAPIDJSON_NAMESPACE::Value &def = doc["def"];
    if( def.IsObject() ) {
        RAPIDJSON_NAMESPACE::Document::MemberIterator it = def.MemberBegin();
        while(it!=def.MemberEnd()) {
            IMIString t_key = it->name.GetString();
            s32 t_value = it->value.GetInt();
            m_deftbl.insert(std::make_pair(t_key,t_value));
            it++;
        }
    }
}

void IMIShaderMgr::_loadAllShader() {
    IMIDataChunk tDataStream;
    IMI_LOG_ERROR("load shadercfg.json begin\n");
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, "shader/shadercfg.json");
    if (!tflag) {
        IMI_LOG_INFO("error not find shadercfg.json!n");
        return;
    }
    IMI_LOG_ERROR("file context %s \n", tDataStream.getPointerChar());
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        IMI_LOG_ERROR("rapidjson error code:%d \n", code);
        return;
    }
    //
    RAPIDJSON_NAMESPACE::Value &language = doc["language"];
    if( language.IsString() ) {
        m_language = language.GetString();
    }
    //获取文件列表
    RAPIDJSON_NAMESPACE::Value &dspfiles = doc["dspfiles"];
    if( dspfiles.IsArray() ) {
        RAPIDJSON_NAMESPACE::Document::Array t_files = dspfiles.GetArray();
        for(s32 i=0;i<t_files.Size();i++) {
            IMIString t_filename = t_files[i].GetString();
            loadSDSP(t_filename.c_str());
        }
    }
    IMI_LOG_DEBUG("load shader end\n");
}

IMIShaderPtr IMIShaderMgr::loadSDSP(cptr8 _sdsp) {
    IMIDataChunk tDataStream;
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, _sdsp);
    if (!tflag) {
        IMI_LOG_INFO("not find _sdsp file!please check shader file path!\n");
        return nullptr;
    }
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        IMI_LOG_ERROR("rapidjson error code:%d \n", code);
        return nullptr;
    }
    //
    IMIString t_s_name = _sdsp;
    s32 t_pos = t_s_name.rfind('.');
    if(t_pos>0) {
        t_s_name = IMIString::substr(t_s_name.c_str(), 0, t_pos);
    }
    //解析
    IMIShaderPtr t_shader = MakeSharedPtr<IMIShader>(mApp);
    if( t_shader->fromJSON( doc ,m_language.c_str()) ) {
        s32 t_code = getDefCode(t_shader->getShaderDsp()->m_defs);
        t_s_name = IMIString::format("%s_%d",t_s_name.c_str(),t_code);
    }else{
        return nullptr;
    }
    //防止重名的shader
    SHADERPOOL::iterator it = m_shaderMap.find(t_s_name);
    if( it == m_shaderMap.end() ) {
        m_shaderMap.insert(std::make_pair(t_s_name, t_shader));
        t_shader->dispatch();
    }
    return t_shader;
}

IMIShaderPtr IMIShaderMgr::loadSDSP(cptr8 _sdsp,std::vector<IMIString>& _defs) {
    IMIString t_fname = IMIString::format("%s.dsp", _sdsp);
    IMIDataChunk tDataStream;
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, t_fname.c_str());
    if (!tflag) {
        return nullptr;
    }
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        IMI_LOG_ERROR("rapidjson error code:%d \n", code);
        return nullptr;
    }
    IMIString t_s_name = _sdsp;
    s32 t_pos = t_s_name.rfind('.');
    if(t_pos>0) {
        t_s_name = IMIString::substr(t_s_name.c_str(), 0, t_pos);
    }
    //解析
    IMIShaderPtr t_shader = MakeSharedPtr<IMIShader>(mApp);
    if( t_shader->fromJSON( doc ,m_language.c_str()) ) {
        //送入宏
        t_shader->getShaderDsp()->m_defs.clear();
        for(s32 i=0;i<_defs.size();i++) {
            t_shader->getShaderDsp()->m_defs.push_back(_defs[i]);
        }
        //重新构建shader名字
        s32 t_code = getDefCode(t_shader->getShaderDsp()->m_defs);
        t_s_name = IMIString::format("%s_%d",t_s_name.c_str(),t_code);
    }else{
        return nullptr;
    }
    //防止重名的shader
    SHADERPOOL::iterator it = m_shaderMap.find(t_s_name);
    if( it == m_shaderMap.end() ) {
        m_shaderMap.insert(std::make_pair(t_s_name, t_shader));
        t_shader->dispatch();
    }
    return t_shader;
}

void IMIShaderMgr::_clearAllShader() {
    m_shaderMap.clear();
}

s32 IMIShaderMgr::getDefValue(cptr8 _defname) {
    DEFTBL::iterator it = m_deftbl.find(_defname);
    if(it!=m_deftbl.end()) {
        return it->second;
    }
    return 0;
}

s32 IMIShaderMgr::getDefCode(std::vector<IMIString>& _defs) {
    if(_defs.size() == 0) {
        return 0;
    }
    s32 t_ret = 0;
    for(s32 i=0;i<_defs.size();i++) {
        s32 t_value = getDefValue( _defs[i].c_str() );
        t_ret |= t_value;
    }
    return t_ret;
}

IMIShaderPtr IMIShaderMgr::getShader(cptr8 _name,s32 _sdef) {
    IMIString t_name = _name;
    t_name = IMIString::format("%s_%d",t_name.c_str(),_sdef);
    SHADERPOOL::iterator it = m_shaderMap.find(t_name.c_str());
    if(it!=m_shaderMap.end()) {
        return it->second;
    }
    return nullptr;
}
