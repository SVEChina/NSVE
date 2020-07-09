//
// SVRTechGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTechGL.h"
#include "SVRendererGL.h"
#include "../../base/SVDataChunk.h"
#include "../../app/SVInst.h"
#include "../../file/SVFileMgr.h"

using namespace sv;

SVRTechGL::SVRTechGL(SVInstPtr _app)
:SVRTech(_app){
}

SVRTechGL::~SVRTechGL() {
}

void SVRTechGL::build(SVRendererPtr _renderer) {
//    if(m_techDsp&SV_E_TECH_VS){
//        m_vsf = _complie_shader(GL_VERTEX_SHADER,m_vs_name.c_str());
//    }
//    if(m_techDsp&SV_E_TECH_FS){
//        m_fsf = _complie_shader(GL_FRAGMENT_SHADER,m_fs_name.c_str());
//    }
//    if(m_techDsp&SV_E_TECH_GS){
//        m_gsf = _complie_shader(GL_GEOMETRY_SHADER,m_gs_name.c_str());
//    }
//    if(m_techDsp&SV_E_TECH_CS){
//        //m_vsf = _complie_shader(GL_VERTEX_SHADER,m_cs_name.c_str());
//    }
//    if(m_techDsp&SV_E_TECH_TSC){
//        m_tscf = _complie_shader(GL_TESS_CONTROL_SHADER,m_tsc_name.c_str());
//    }
//    if(m_techDsp&SV_E_TECH_TSD){
//        m_tsdf = _complie_shader(GL_TESS_EVALUATION_SHADER,m_tsd_name.c_str());
//    }
//    //link
//    //m_p_id
//    s32 t_error = 0;
//    u32 t_program_id = glCreateProgram();
//    glAttachShader(t_program_id, m_vsf);
//    glAttachShader(t_program_id, m_fsf);
//    glAttachShader(t_program_id, m_gsf);
//    glAttachShader(t_program_id, m_tscf);
//    glAttachShader(t_program_id, m_tsdf);
////    if( m_attri_formate == "all" ) {
////        //bind prop
////        glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
////        glBindAttribLocation(t_program_id, CHANNEL_NORMAL, NAME_NORMAL);
////        glBindAttribLocation(t_program_id, CHANNEL_TAGENT, NAME_TAGENT);
////        glBindAttribLocation(t_program_id, CHANNEL_BTAGENT, NAME_BNOR);
////        glBindAttribLocation(t_program_id, CHANNEL_COLOR0, NAME_COLOR);
////        glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD0, NAME_TEXCOORD0);
////        glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD1, NAME_TEXCOORD1);
////        glBindAttribLocation(t_program_id, CHANNEL_INSOFFSET, NAME_INSOFFSET);
////        //蒙皮动画相关
////        glBindAttribLocation(t_program_id, CHANNEL_BONE_ID, NAME_BONE_ID);
////        glBindAttribLocation(t_program_id, CHANNEL_BONE_WEIGHT, NAME_BONE_WEIGHT);
////        //bind attri(new)
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_0, "s_attribute_0");
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_1, "s_attribute_1");
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_2, "s_attribute_2");
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_3, "s_attribute_3");
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_4, "s_attribute_4");
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_5, "s_attribute_5");
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_6, "s_attribute_6");
////        glBindAttribLocation(t_program_id, CHANNEL_ATTRI_7, "s_attribute_7");
////    } else {
////        SVStringArray t_str_array;
////        t_str_array.setData(m_attri_formate.c_str(),'-');
////        for(s32 i=0;i<t_str_array.size();i++) {
////            SVString t_str = t_str_array[i];
////            if( t_str == "V2" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
////            }else if( t_str == "V3" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
////            }else if( t_str == "N" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_NORMAL, NAME_NORMAL);
////            }else if( t_str == "TA" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_TAGENT, NAME_TAGENT);
////            }else if( t_str == "BT" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_BTAGENT, NAME_BNOR);
////            }else if( t_str == "T0" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD0, NAME_TEXCOORD0);
////            }else if( t_str == "T1" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_TEXCOORD1, NAME_TEXCOORD1);
////            }else if( t_str == "C0" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_COLOR0, NAME_COLOR);
////            }else if( t_str == "OFF" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_INSOFFSET, NAME_INSOFFSET);
////            }else if( t_str == "BONE" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_BONE_ID, NAME_BONE_ID);
////            }else if( t_str == "W" ) {
////                glBindAttribLocation(t_program_id, CHANNEL_BONE_WEIGHT, NAME_BONE_WEIGHT);
////            }
////        }
////    }
//    glLinkProgram(t_program_id);
//    GLint linkstatus;
//    glGetProgramiv(t_program_id, GL_LINK_STATUS, &linkstatus);
//    if (linkstatus == GL_FALSE) {
//        t_error = glGetError();
//        GLint logLen = 1000;
//        if (logLen > 0) {
//            char *log = (char *) malloc(logLen);
//            GLsizei written;
//            glGetProgramInfoLog(t_program_id, logLen, &written, log);
//            SV_LOG_DEBUG("link status:%s, error: %d\n", log, t_error);
//            free(log);
//        }
//    } else {
//        glUseProgram(t_program_id);
//    }
}


//s32 SVRTechGL::_complie_shader(s32 _shadertype,cptr8 _fname) {
//    SVDataChunk tDataStream;
//    u32 t_id = 0;
//    bool t_flag = mApp->getFileMgr()->loadFileContentStr(&tDataStream, _fname);
//    if(!t_flag){
//        return t_id;
//    }
//    //
//    cptr8 vs_shader = tDataStream.getPointerChar();
//    u32 t_shader_id = glCreateShader(_shadertype);
//    glShaderSource(t_shader_id, 1, &vs_shader, 0);
//    glCompileShader(t_shader_id);
//    GLint compileErr = 0;
//    glGetShaderiv(t_shader_id, GL_COMPILE_STATUS, &compileErr);
//    if (GL_FALSE == compileErr) {
//        GLint logLen;
//        glGetShaderiv(t_shader_id, GL_INFO_LOG_LENGTH, &logLen);
//        if (logLen > 0) {
//            char *log = (char *) malloc(logLen);
//            GLsizei written;
//            glGetShaderInfoLog(t_shader_id, logLen, &written, log);
//            SV_LOG_DEBUG("vs shader compile error log : \n %s fname:%s \n",
//                         log,
//                         _fname);
//            free(log);
//        }
//        t_shader_id = 0;
//    }else{
//        SV_LOG_DEBUG("load vs: %s (%d) sucess\n", _fname, t_shader_id);
//    }
//    return t_shader_id;
//}


void SVRTechGL::render(SVRendererPtr _renderer) {
}
