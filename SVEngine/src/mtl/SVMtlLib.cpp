//
// SVMtlLib.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMtlLib.h"
#include "SVMtlCore.h"
#include "SVMtlGLTF.h"
#include "../app/SVInst.h"
#include "../file/SVFileMgr.h"
#include "../base/SVDataChunk.h"

using namespace sv;

//SVMtlCorePtr SVMtlLib::m_pSkinMtl = nullptr;

void SVMtlLib::clear() {
    //m_pSkinMtl = nullptr;
}

SVMtlCorePtr SVMtlLib::getSkinMtl(SVInstPtr _app) {
//    if(!m_pSkinMtl) {
//         m_pSkinMtl = MakeSharedPtr<SVMtlGLTF>(_app);
//    }
//    //
//    FMat4 tMat_rotx;
//    tMat_rotx.setIdentity();
//    tMat_rotx.setRotateX(45.0f);
//
//    FMat4 tMat_roty;
//    tMat_roty.setIdentity();
//    tMat_roty.setRotateY(45.0f);
//
//    FMat4 tMat_sc;
//    tMat_sc.setIdentity();
//    tMat_sc.setScale(FVec3(200.0f,200.0f,200.0f));
//    //
//    FMat4 tMat = tMat_sc * tMat_roty * tMat_rotx;
//    m_pSkinMtl->setModelMatrix(tMat.get());
//    m_pSkinMtl->setBlendEnable(false);
//    m_pSkinMtl->setDepthEnable(true);
//    m_pSkinMtl->update(0.03f);
//    //
//    return m_pSkinMtl;
    return nullptr;
}

SVMtlCorePtr SVMtlLib::get3DNorMtl(SVInstPtr _app) {
    SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlGLTF>(_app);
    return t_mtl;
}

//材质名称和shader名称有个映射关系
SVString SVMtlLib::mapName(cptr8 _name) {
    return "";
}

SVMtlCorePtr SVMtlLib::genMtl(SVInstPtr _app,cptr8 _name) {
    SVString t_mtlname = _name;
    SVString t_shadername = mapName(_name);
    SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlCore>(_app,t_shadername.c_str());
    if(t_mtlname == "SVMtl2D") {
        //t_mtl->setParam("u_alpha",0.0f);
    }else if(t_mtlname == "SVMtl2D") {
        //
    }
    return t_mtl;
}

SVMtlCorePtr SVMtlLib::createMtl(SVInstPtr _app,cptr8 _mtlname) {
    //SVDataChunk *_datachunk
    SVDataChunk t_data;
    bool t_ret = _app->m_pFileMgr->loadFileContent(&t_data, _mtlname);
    if(!t_ret) {
        return nullptr;
    }
    //解析json文件
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse(t_data.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d \n", code);
        return nullptr;
    }
    SVString t_version = "1.0";
    if (doc.HasMember("version")) {
        t_version = doc["version"].GetString();
    }
    if(t_version == "1.0") {
        SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlCore>(_app);
        parseMtl1(t_mtl,doc);
        return t_mtl;
    }
    return nullptr;
}

bool SVMtlLib::parseMtl1(SVMtlCorePtr _mtl,RAPIDJSON_NAMESPACE::Document& _doc) {
    if(!_mtl)
        return false;
    SVString t_shader_file = "shader";
    if (_doc.HasMember("shader") && _doc["shader"].IsString()) {
        RAPIDJSON_NAMESPACE::Value &t_value = _doc["shader"];
        t_shader_file = t_value.GetString();
    }
    //param param 参数解析
    if (_doc.HasMember("param-tbl") && _doc["param-tbl"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_value_array = _doc["param-tbl"].GetArray();
        for(s32 i=0;i<t_value_array.Size();i++) {
            RAPIDJSON_NAMESPACE::Document::Object element = t_value_array[i].GetObject();
            SVString t_param_name = element["name"].GetString();
            SVString t_param_type = element["type"].GetString();
            SVString t_param_value = element["value"].GetString();
            _mtl->addParam(t_param_name.c_str(),t_param_type.c_str(),t_param_value.c_str());
        }
    }
    //texture param 纹理解析
    if (_doc.HasMember("texture-tbl") && _doc["texture-tbl"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_value_array = _doc["texture-tbl"].GetArray();
        for(s32 i=0;i<t_value_array.Size();i++) {
            RAPIDJSON_NAMESPACE::Document::Object element = t_value_array[i].GetObject();
            s32 t_param_chan = element["chn"].GetInt();
            SVString t_param_type = element["from"].GetString();
            SVString t_param_path = element["path"].GetString();
            if(t_param_type == "file") {
                _mtl->setTexture(t_param_chan, t_param_path.c_str());
            }else if(t_param_type == "inner") {
                if(t_param_path == "SV_MAIN") {
                    _mtl->setTexture(t_param_chan,E_TEX_MAIN);
                }
            }
        }
        //t_shader_file = t_value.GetString();
    }
    //blend param 融合
    if (_doc.HasMember("blend-param") && _doc["blend-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _doc["blend-param"].GetObject();
        s32 t_enable = t_value_obj["enable"].GetInt();
        _mtl->setBlendEnable(true);
        //_mtl->setBlendState(<#MTLBLENDFUNC _src#>, <#MTLBLENDFUNC _dst#>)
    }
    //stencil param 融合
    if (_doc.HasMember("stencil-param") && _doc["stencil-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _doc["stencil-param"].GetObject();
        s32 t_enable = t_value_obj["enable"].GetInt();
    }
    //alpha param 融合
    if (_doc.HasMember("alpha-param") && _doc["alpha-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _doc["alpha-param"].GetObject();
        s32 t_enable = t_value_obj["enable"].GetInt();
    }
    return true;
}
