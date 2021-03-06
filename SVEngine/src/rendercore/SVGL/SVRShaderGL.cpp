//
// SVRShaderGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRShaderGL.h"
#include "SVRendererGL.h"
#include "../../mtl/SVShader.h"
#include "../../mtl/SVSurface.h"
#include "../../app/SVInst.h"
#include "../../file/SVFileMgr.h"
#include "../../base/SVParamTbl.h"

using namespace sv;

/*
GL Shader
*/

SVRShaderGL::SVRShaderGL(SVInstPtr _app)
:SVRShader(_app){
    m_block = false;
    m_programm = 0;
    m_vs = 0;
    m_fs = 0;
    m_gs = 0;
    m_tsc = 0;
    m_tse = 0;
    m_cs = 0;
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

void SVRShaderGL::load(SVRendererPtr _renderer,ShaderDsp* _shader_dsp) {
    SVRShader::load(_renderer, _shader_dsp);
    if(!m_shader_dsp) {
        return ;
    }
    if( m_shader_dsp->m_dsp & SV_E_TECH_VS ) {
         m_vs = _loadShader(_renderer,
                            m_shader_dsp,
                            m_shader_dsp->m_vs_fname.c_str(),
                            SV_E_TECH_VS);
    }
    if( m_shader_dsp->m_dsp & SV_E_TECH_FS ) {
        m_fs = _loadShader(_renderer,
                           m_shader_dsp,
                           m_shader_dsp->m_fs_fname.c_str(),
                           SV_E_TECH_FS);
    }
    if( m_shader_dsp->m_dsp & SV_E_TECH_GS ) {
       m_gs = _loadShader(_renderer,
                          m_shader_dsp,
                          m_shader_dsp->m_gs_fname.c_str(),
                          SV_E_TECH_GS);
    }
    if( m_shader_dsp->m_dsp & SV_E_TECH_TSE ) {
        m_tsc = _loadShader(_renderer,
                            m_shader_dsp,
                            m_shader_dsp->m_tse_fname.c_str(),
                            SV_E_TECH_TSE);
    }
    if( m_shader_dsp->m_dsp & SV_E_TECH_TSD ) {
        m_tse = _loadShader(_renderer,
                            m_shader_dsp,
                            m_shader_dsp->m_tsd_fname.c_str(),
                            SV_E_TECH_TSD);
    }
    m_programm = _createProgram();
    _clearShaderRes();
}

//在加载shader的时候 可以补充宏定义

u32 SVRShaderGL::_loadShader(SVRendererPtr _renderer,
                             ShaderDsp* _shader_dsp,
                             cptr8 _filename,
                             s32 _shaderType){
    SVRendererGLPtr t_renderGL = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    if(!t_renderGL) {
        return 0;
    }
    //自动补充版本号
    SVString _fname = _filename;
    SVString _aim_str = "code";
    SVString _new_str = "code3";
    SVString version_str = "";
    if( t_renderGL->m_gl_version == 2 ) {
        //version_str = "#version 100 es"
    }else if( t_renderGL->m_gl_version == 3 ) {
        version_str = "#version 300 es \n";
        _fname = SVString::replace(_fname.c_str(),_aim_str.c_str(),_new_str.c_str());
    }
    SVDataChunk tDataStream;
    u32 t_id = 0;
    bool t_flag=false;
    if(!t_id){
        t_flag = mApp->m_file_sys->loadFileContentStr(&tDataStream, _fname.c_str());
    }else{
        return t_id;
    }
    if (!t_flag){
        return 0;
    }
    //
    cptr8 t_shader_res = tDataStream.getPointerChar();
    s32 t_shader_type = 0;
    if(_shaderType == SV_E_TECH_VS) {
        t_shader_type = GL_VERTEX_SHADER;
    }else if(_shaderType == SV_E_TECH_FS) {
        t_shader_type = GL_FRAGMENT_SHADER;
    }else if(_shaderType == SV_E_TECH_GS) {
#ifdef SV_OSX
        t_shader_type = GL_GEOMETRY_SHADER;
#endif
    }else if(_shaderType == SV_E_TECH_TSD) {
#ifdef SV_OSX
        t_shader_type = GL_TESS_EVALUATION_SHADER;
#endif
    }else if(_shaderType == SV_E_TECH_TSE) {
#ifdef SV_OSX
        t_shader_type = GL_TESS_CONTROL_SHADER;
#endif
    }else if(_shaderType == 6) {
    }
    //
    SVDataChunk tNewStream;
    //push head
    tNewStream.push( (void*)(version_str.c_str()), version_str.size());
    //push def
    for(s32 i=0;i<_shader_dsp->m_defs.size();i++) {
        SVString t_def_str = SVString::format("#define %s \n", _shader_dsp->m_defs[i].c_str());
        tNewStream.push( (void*)(t_def_str.c_str()), t_def_str.size());
    }
    //push code
    tNewStream.push( (void*)t_shader_res, (s32)(tDataStream.getRealSize()) );
    t_shader_res = tNewStream.getPointerChar();
    //自动补充精度
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
            SV_LOG_DEBUG("shader compile error log : \n %s fname:%s \n",
                         log,
                         _fname.c_str());
            free(log);
        }
        t_shader_id = 0;
    }else{
        SV_LOG_DEBUG("load shader file %s type %d sucess\n", _filename, _shaderType);
    }
    return t_shader_id;
}

u32 SVRShaderGL::_createProgram(){
    if (m_vs == 0 || m_fs == 0) {
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
    for(s32 i=0;i<m_shader_dsp->m_vft.size();i++) {
        s32 t_vf = m_shader_dsp->m_vft[i];
        if (t_vf == E_VF_V2) {
            glBindAttribLocation(t_program_id, i, NAME_POSITION);
        }else if (t_vf == E_VF_V3) {
            glBindAttribLocation(t_program_id, i, NAME_POSITION);
        }else if (t_vf == E_VF_NOR) {
            glBindAttribLocation(t_program_id, i, NAME_NORMAL);
        }else if (t_vf == E_VF_TAG) {
            glBindAttribLocation(t_program_id, i, NAME_TAGENT);
        }else if (t_vf == E_VF_BTAG) {
            glBindAttribLocation(t_program_id, i, NAME_BNOR);
        }else if (t_vf == E_VF_C0) {
            glBindAttribLocation(t_program_id, i, NAME_COLOR);
        }else if (t_vf == E_VF_T0) {
            glBindAttribLocation(t_program_id, i, NAME_TEXCOORD0);
        }else if (t_vf == E_VF_T1) {
            glBindAttribLocation(t_program_id, i, NAME_TEXCOORD1);
        }else if (t_vf == E_VF_BONE) {
            glBindAttribLocation(t_program_id, i, NAME_BONE_ID);
        }else if (t_vf == E_VF_BONE_W) {
            glBindAttribLocation(t_program_id, i, NAME_BONE_WEIGHT);
        }else if (t_vf == E_VF_INSOFFSET) {
            glBindAttribLocation(t_program_id, i, NAME_INSOFFSET);
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

void SVRShaderGL::unload() {
    if(m_programm != 0){
        glDeleteProgram(m_programm);
    }
}

bool SVRShaderGL::active(SVRendererPtr _renderer) {
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    if(t_rm && m_programm>0) {
        glUseProgram(m_programm);
        t_rm->m_cur_program = m_programm;
        //提交参数
        submitParamTbl();
        //提交纹理
        
        //设置各种属性
        return true;
    }
    return false;
}

void SVRShaderGL::submitParamTbl() {
    if(!m_shader_dsp){
        return ;
    }
    //OpenGL 应该是不分阶段的传递uniform
    for(s32 i=0;i<m_shader_dsp->m_paramtbl.size();i++) {
        SVParamTblPtr t_tbl = m_shader_dsp->m_paramtbl[i].m_tbl;
        for(s32 i=0;i<t_tbl->m_param_names.size();i++) {
            SVString t_name = t_tbl->m_param_names[i].c_str();
            s32 t_locate = glGetUniformLocation(m_programm, t_name.c_str());
            if(t_locate<0) {
                continue;
            }
            if( t_tbl->m_param_dsps[i].m_type == SV_INT) {
                s32* t_p = (s32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1) {
                    glUniform1i(t_locate,*t_p);
                }else{
                    glUniform1iv(t_locate,t_tbl->m_param_dsps[i].m_cnt,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FLOAT) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(f32);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1){
                    glUniform1f(t_locate,*t_p);
                }else{
                    glUniform1fv(t_locate,t_cnt,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FVEC2) {
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1){
                    glUniform2f(t_locate,*t_p,*(t_p+1));
                }else{
                    glUniform2fv(t_locate,t_tbl->m_param_dsps[i].m_cnt,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FVEC3) {
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1){
                    glUniform3f(t_locate,*t_p,*(t_p+1),*(t_p+2));
                }else{
                    glUniform3fv(t_locate,t_tbl->m_param_dsps[i].m_cnt,t_p);
                }
                glUniform3fv(t_locate,1,t_p);
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FVEC4) {
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1){
                    glUniform4f(t_locate,*t_p,*(t_p+1),*(t_p+2),*(t_p+3));
                }else{
                    glUniform4fv(t_locate,t_tbl->m_param_dsps[i].m_cnt,t_p);
                }
                glUniform4fv(t_locate,1,t_p);
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FMAT2) {
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1){
                    glUniformMatrix4fv(t_locate,1,GL_FALSE,t_p);
                }else{
                    glUniformMatrix4fv(t_locate,t_tbl->m_param_dsps[i].m_cnt,GL_FALSE,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FMAT3) {
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1){
                    glUniformMatrix4fv(t_locate,1,GL_FALSE,t_p);
                }else{
                    glUniformMatrix4fv(t_locate,t_tbl->m_param_dsps[i].m_cnt,GL_FALSE,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FMAT4) {
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_tbl->m_param_dsps[i].m_cnt == 1){
                    glUniformMatrix4fv(t_locate,1,GL_FALSE,t_p);
                }else{
                    glUniformMatrix4fv(t_locate,t_tbl->m_param_dsps[i].m_cnt,GL_FALSE,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_BLOCK) {
                //传递一个数据块上去啊
            }
        }
    }
}
