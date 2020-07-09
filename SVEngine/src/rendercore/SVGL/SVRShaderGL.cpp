//
// SVRShaderGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRShaderGL.h"
#include "../../third/rapidjson/document.h"
#include "../../base/SVPreDeclare.h"
#include "../../app/SVInst.h"
#include "../../mtl/SVMtlDef.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"
#include "../../base/SVDataChunk.h"
#include "../../file/SVFileMgr.h"
#include "../../base/SVDataSwap.h"
#include "../../work/SVTdCore.h"
#include "../../rendercore/SVRenderMgr.h"
#include "../SVRenderer.h"
#include "../SVRenderState.h"
#include "../SVGL/SVRendererGL.h"

using namespace sv;

/*
GL Shader
*/

SVRShaderGL::SVRShaderGL(SVInstPtr _app)
:SVRShader(_app){
    m_programm = 0;
    m_vs = 0;
    m_fs = 0;
    m_gs = 0;
    m_tsc = 0;
    m_tse = 0;
    m_cs = 0;
    m_use_tech = false;
}

SVRShaderGL::~SVRShaderGL(){
    m_programm = 0;
    m_vs = 0;
    m_fs = 0;
    m_gs = 0;
    m_tsc = 0;
    m_tse = 0;
    m_cs = 0;
}

void SVRShaderGL::create(SVRendererPtr _renderer) {
    if( m_use_tech ) {
        _parseTech();
    } else {
        m_vs = _loadShader(mApp,m_vs_fname.c_str(),1);
        m_fs = _loadShader(mApp,m_fs_fname.c_str(),2);
        m_gs = _loadShader(mApp,m_gs_fname.c_str(),3);
        m_tsc = _loadShader(mApp,m_tsc_fname.c_str(),4);
        m_tse = _loadShader(mApp,m_tse_fname.c_str(),5);
        m_cs = _loadShader(mApp,m_cs_fname.c_str(),6);
        m_programm = _createProgram();
        _clearShaderRes();//生产program后就删除shader资源
    }
}

void SVRShaderGL::setTechFName(cptr8 _filename) {
    m_tech_fname = _filename;
    m_use_tech = true;
}

u32 SVRShaderGL::_loadShader(SVInstPtr _app,cptr8 _filename,s32 _shaderType){
    SVDataChunk tDataStream;
    u32 t_id = 0;
    bool t_flag=false;
    if(!t_id){
        t_flag = _app->getFileMgr()->loadFileContentStr(&tDataStream, _filename);
    }else{
        return t_id;
    }
    if (!t_flag){
        return 0;
    }
    //
    cptr8 t_shader_res = tDataStream.getPointerChar();
    s32 t_shader_type = 0;
    if(_shaderType == 1) {
        t_shader_type = GL_VERTEX_SHADER;
    }else if(_shaderType == 2) {
        t_shader_type = GL_FRAGMENT_SHADER;
    }else if(_shaderType == 3) {
        t_shader_type = GL_GEOMETRY_SHADER;
    }else if(_shaderType == 4) {
        t_shader_type = GL_TESS_EVALUATION_SHADER;
    }else if(_shaderType == 5) {
        t_shader_type = GL_TESS_CONTROL_SHADER;
    }else if(_shaderType == 6) {
    }
    u32 t_shader_id = glCreateShader(t_shader_type);
    glShaderSource(t_shader_id, 1, &t_shader_res, 0);
    glCompileShader(t_shader_id);
    GLint compileErr = 0;
    glGetShaderiv(t_shader_id, GL_COMPILE_STATUS, &compileErr);
    if (GL_FALSE == compileErr) {
        GLint logLen;
        glGetShaderiv(t_shader_id, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            c8 *log = (c8 *) malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(t_shader_id, logLen, &written, log);
            SV_LOG_DEBUG("vs shader compile error log : \n %s fname:%s \n", log,
                         _filename/*[filename UTF8String]*/);
            free(log);
        }
        t_shader_id = 0;
    }else{
        SV_LOG_DEBUG("load shader file %s type %d sucess\n", _filename, _shaderType);
    }
    return t_shader_id;
}

//解析tech
bool SVRShaderGL::_parseTech() {
    SVDataChunk tDataStream;
    bool tflag = mApp->getFileMgr()->loadFileContentStr(&tDataStream, m_tech_fname.c_str());
    if (!tflag)
        return false;
    RAPIDJSON_NAMESPACE::Document t_doc;
    t_doc.Parse(tDataStream.getPointerChar());
    if (t_doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = t_doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d \n", code);
        return false;
    }
    //
    if (t_doc.HasMember("version")) {
        RAPIDJSON_NAMESPACE::Value &version = t_doc["version"];
    }
    if (t_doc.HasMember("language")) {
        RAPIDJSON_NAMESPACE::Value &language = t_doc["language"];
    }
    //
    if (t_doc.HasMember("vs")) {
        RAPIDJSON_NAMESPACE::Value &vs = t_doc["vs"];
        if (vs.IsObject()) {
            SVString t_precision = SVString::null;
            SVString t_src = SVString::null;
            if (vs.HasMember("precision")) {
                RAPIDJSON_NAMESPACE::Value &t_value = vs["precision"];
                t_precision = t_value.GetString();
            }
            if (vs.HasMember("source")) {
                RAPIDJSON_NAMESPACE::Value &t_value = vs["source"];
                t_src = t_value.GetString();
            }
            //拼接字符串 这里需要
            m_vs = _loadTechVS(t_precision.c_str(),t_src.c_str());
        }
    }
    //
    if (t_doc.HasMember("fs")) {
        RAPIDJSON_NAMESPACE::Value &fs = t_doc["fs"];
        if (fs.IsObject()) {
            SVString t_precision = SVString::null;
            SVString t_src = SVString::null;
            if (fs.HasMember("precision")) {
                RAPIDJSON_NAMESPACE::Value &t_value = fs["precision"];
                t_precision = t_value.GetString();
            }
            if (fs.HasMember("source")) {
                RAPIDJSON_NAMESPACE::Value &t_value = fs["source"];
                t_src = t_value.GetString();
            }
            m_fs = _loadTechFS(t_precision.c_str(),t_src.c_str());
        }
    }
    //
    if (t_doc.HasMember("gs")) {
        RAPIDJSON_NAMESPACE::Value &gs = t_doc["gs"];
        if (gs.IsObject()) {
            SVString t_precision = SVString::null;
            SVString t_src = SVString::null;
            if (gs.HasMember("precision")) {
                RAPIDJSON_NAMESPACE::Value &t_value = gs["precision"];
                t_precision = t_value.GetString();
            }
            if (gs.HasMember("source")) {
                RAPIDJSON_NAMESPACE::Value &t_value = gs["source"];
                t_src = t_value.GetString();
            }
            m_gs = _loadTechGS(t_precision.c_str(),t_src.c_str());
        }
    }
    return true;
}

u32 SVRShaderGL::_loadTechVS(cptr8 _precision,cptr8 _src) {
    SVString t_source = _src;
#ifdef SV_ANDROID
    if(strcmp(_src,"lowp") == 0 ) {

    } else if(strcmp(_src,"mediump") == 0 ) {

    } else if(strcmp(_src,"highp") == 0 ) {

    }
#endif

#ifdef  SV_IOS
    if(strcmp(_src,"lowp") == 0 ) {

    } else if(strcmp(_src,"mediump") == 0 ) {

    } else if(strcmp(_src,"highp") == 0 ) {

    }
#endif

    return 0;
}

u32 SVRShaderGL::_loadTechFS(cptr8 _precision,cptr8 _src) {
    SVString t_source = _src;
#ifdef SV_ANDROID
    if(strcmp(_src,"lowp") == 0 ) {
        //t_source =
    } else if(strcmp(_src,"mediump") == 0 ) {

    } else if(strcmp(_src,"highp") == 0 ) {

    }
#endif

#ifdef SV_IOS
    if(strcmp(_src,"lowp") == 0 ) {
        //t_source =
    } else if(strcmp(_src,"mediump") == 0 ) {

    } else if(strcmp(_src,"highp") == 0 ) {

    }
#endif
    return 0;
}

u32 SVRShaderGL::_loadTechGS(cptr8 _precision,cptr8 _src) {
#ifdef SV_ANDROID
    if(strcmp(_src,"lowp") == 0 ) {

    } else if(strcmp(_src,"mediump") == 0 ) {

    } else if(strcmp(_src,"highp") == 0 ) {

    }
#endif
#ifdef SV_IOS
    if(strcmp(_src,"lowp") == 0 ) {

    } else if(strcmp(_src,"mediump") == 0 ) {

    } else if(strcmp(_src,"highp") == 0 ) {

    }
#endif
    return 0;
}

u32 SVRShaderGL::_createProgram(){
    if (m_vs == 0 || m_fs == 0) {
        SV_LOG_DEBUG("error : create program fail, please check out shader:%s\n", m_programme_fname.c_str());
        return 0;
    }
    s32 t_error = 0;
    u32 t_program_id = glCreateProgram();
    if(m_vs>0) {
        glAttachShader(t_program_id, m_vs);
    }
    if(m_fs>0) {
        glAttachShader(t_program_id, m_fs);
    }
    if(m_gs>0) {
        glAttachShader(t_program_id, m_gs);
    }
    if(m_tsc>0) {
        glAttachShader(t_program_id, m_tsc);
    }
    if(m_tse>0) {
        glAttachShader(t_program_id, m_tse);
    }
    if(m_cs>0) {
        glAttachShader(t_program_id, m_cs);
    }
    //
    if( m_attri_formate == "all" ) {
        //bind prop
        glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        glBindAttribLocation(t_program_id, CHANNEL_NORMAL, NAME_NORMAL);
        glBindAttribLocation(t_program_id, CHANNEL_TAGENT, NAME_TAGENT);
        glBindAttribLocation(t_program_id, CHANNEL_BTAGENT, NAME_BNOR);
        glBindAttribLocation(t_program_id, CHANNEL_COLOR0, NAME_COLOR);
        glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD0, NAME_TEXCOORD0);
        glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD1, NAME_TEXCOORD1);
        glBindAttribLocation(t_program_id, CHANNEL_INSOFFSET, NAME_INSOFFSET);
        //蒙皮动画相关
        glBindAttribLocation(t_program_id, CHANNEL_BONE_ID, NAME_BONE_ID);
        glBindAttribLocation(t_program_id, CHANNEL_BONE_WEIGHT, NAME_BONE_WEIGHT);
        //bind attri(new)
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_0, "s_attribute_0");
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_1, "s_attribute_1");
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_2, "s_attribute_2");
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_3, "s_attribute_3");
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_4, "s_attribute_4");
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_5, "s_attribute_5");
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_6, "s_attribute_6");
        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_7, "s_attribute_7");
    } else {
        SVStringArray t_str_array;
        t_str_array.setData(m_attri_formate.c_str(),'-');
        for(s32 i=0;i<t_str_array.size();i++) {
            SVString t_str = t_str_array[i];
            if( t_str == "V2" ) {
                glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
            }else if( t_str == "V3" ) {
                glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
            }else if( t_str == "N" ) {
                glBindAttribLocation(t_program_id, CHANNEL_NORMAL, NAME_NORMAL);
            }else if( t_str == "TA" ) {
                glBindAttribLocation(t_program_id, CHANNEL_TAGENT, NAME_TAGENT);
            }else if( t_str == "BT" ) {
                glBindAttribLocation(t_program_id, CHANNEL_BTAGENT, NAME_BNOR);
            }else if( t_str == "T0" ) {
                glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD0, NAME_TEXCOORD0);
            }else if( t_str == "T1" ) {
                glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD1, NAME_TEXCOORD1);
            }else if( t_str == "C0" ) {
                glBindAttribLocation(t_program_id, CHANNEL_COLOR0, NAME_COLOR);
            }else if( t_str == "OFF" ) {
                glBindAttribLocation(t_program_id, CHANNEL_INSOFFSET, NAME_INSOFFSET);
            }else if( t_str == "BONE" ) {
                glBindAttribLocation(t_program_id, CHANNEL_BONE_ID, NAME_BONE_ID);
            }else if( t_str == "W" ) {
                glBindAttribLocation(t_program_id, CHANNEL_BONE_WEIGHT, NAME_BONE_WEIGHT);
            }
        }
    }
    glLinkProgram(t_program_id);
    GLint linkstatus;
    glGetProgramiv(t_program_id, GL_LINK_STATUS, &linkstatus);
    if (linkstatus == GL_FALSE) {
        t_error = glGetError();
        GLint logLen = 1000;
        if (logLen > 0) {
            char *log = (char *) malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(t_program_id, logLen, &written, log);
            SV_LOG_DEBUG("link status:%s, error: %d\n", log, t_error);
            free(log);
        }
    } else {
        glUseProgram(t_program_id);
    }
    return t_program_id;
}

void SVRShaderGL::_clearShaderRes(){
    if(m_vs != 0) {
        glDeleteShader(m_vs);
        m_vs = 0;
    }
    if(m_fs != 0) {
        glDeleteShader(m_fs);
        m_fs = 0;
    }
    if(m_gs != 0) {
        glDeleteShader(m_gs);
        m_gs = 0;
    }
    if(m_cs != 0) {
        glDeleteShader(m_cs);
        m_cs = 0;
    }
    if(m_tsc != 0) {
        glDeleteShader(m_tsc);
        m_tsc = 0;
    }
    if(m_tse != 0) {
        glDeleteShader(m_tse);
        m_tse = 0;
    }
}

void SVRShaderGL::destroy(SVRendererPtr _renderer) {
    if(m_programm != 0){
        glDeleteProgram(m_programm);
    }
}

bool SVRShaderGL::active(SVRendererPtr _render) {
    SVRenderStatePtr t_state = _render->getState();
    if(m_programm>0) {
        glUseProgram(m_programm);
        t_state->m_shaderID = m_programm;
        return true;
    }
    t_state->m_shaderID = 0;
    return false;
}
