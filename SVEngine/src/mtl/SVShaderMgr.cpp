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
    if ( shader.IsArray() ) {
        for (s32 i = 0; i < shader.Size(); ++i) {
            RAPIDJSON_NAMESPACE::Value &shaderitem = shader[i];
            SVShaderPtr t_shader = MakeSharedPtr<SVShader>(mApp);
            if( t_shader->fromJSON( shaderitem ) ) {
                SVDispatch::dispatchShaderCreate(mApp,t_shader);
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
