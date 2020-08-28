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

void SVRShaderGL::create(SVRendererPtr _renderer) {
    if(!m_logic_obj) {
        return ;
    }
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return ;
    }
    //
    if( t_shader->m_shader_dsp.m_dsp &SV_E_TECH_VS ) {
         m_vs = _loadShader(mApp,t_shader->m_shader_dsp.m_vs_fname.c_str(),SV_E_TECH_VS);
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_FS ) {
        m_fs = _loadShader(mApp,t_shader->m_shader_dsp.m_fs_fname.c_str(),SV_E_TECH_FS);
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_GS ) {
       m_gs = _loadShader(mApp,t_shader->m_shader_dsp.m_gs_fname.c_str(),SV_E_TECH_GS);
    }
//    if( m_shader_dsp&SV_E_TECH_CS ) {
//     m_cs = _loadShader(mApp,t_shader->m_dsp.m_gs_fname.c_str(),SV_E_TECH_GS);
//    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_TSE ) {
        m_tsc = _loadShader(mApp,t_shader->m_shader_dsp.m_tsc_fname.c_str(),SV_E_TECH_TSE);
    }
    if( t_shader->m_shader_dsp.m_dsp&SV_E_TECH_TSD ) {
        m_tse = _loadShader(mApp,t_shader->m_shader_dsp.m_tse_fname.c_str(),SV_E_TECH_TSD);
    }
    m_programm = _createProgram();
    //创建采样器
    
    //生成uniform-buf
    for(s32 i=0;i<t_shader->m_paramtbl.size();i++) {
        //合并参数表
        SVParamTblPtr t_p_tbl = t_shader->m_paramtbl[i].m_tbl;
//        s32 t_len = t_shader->m_paramtbl[i].m_tbl->getDataSize();
        //m_tbl->setParam(<#cptr8 _name#>, <#s32 _value#>)
        //UBUF t_ubuf;
//        t_ubuf.m_bufid = t_shader->m_paramtbl[i].m_id;
//        t_ubuf.m_type = t_shader->m_paramtbl[i].m_type;
//        t_ubuf.m_ubuf = [t_rm->m_pDevice newBufferWithBytes:t_pointer length: t_len options: MTLResourceStorageModeShared ];
//        m_ubuf_pool.push_back(t_ubuf);
    }
//    for(s32 i=0;i<m_paramtbl.size();i++) {
//        if(m_block) {
//            //创建参数block
//        }else{
//
//        }
//    }
//    //采样器
//    std::vector<SamplerDsp> m_samplers;
//    //参数表
//    std::vector<ParamTblDsp> m_paramtbl;
    //生产program后就删除shader资源
    _clearShaderRes();
    //创建完毕，资源释放
    m_logic_obj = nullptr;
}

u32 SVRShaderGL::_loadShader(SVInstPtr _app,cptr8 _filename,s32 _shaderType){
    SVDataChunk tDataStream;
    u32 t_id = 0;
    bool t_flag=false;
    if(!t_id){
        t_flag = _app->m_file_sys->loadFileContentStr(&tDataStream, _filename);
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
        t_shader_type = GL_GEOMETRY_SHADER;
    }else if(_shaderType == SV_E_TECH_TSD) {
        t_shader_type = GL_TESS_EVALUATION_SHADER;
    }else if(_shaderType == SV_E_TECH_TSE) {
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
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    for(s32 i=0;i<t_shader->m_shader_dsp.m_vft.size();i++) {
        //单一混合流
        s32 t_vf = t_shader->m_shader_dsp.m_vft[i];
        if (t_vf & E_VF_V2) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_V3) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_NOR) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_TAG) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_BTAG) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_C0) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_T0) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_T1) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_BONE) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
        }else if (t_vf & E_VF_BONE_W) {
            glBindAttribLocation(t_program_id, CHANNEL_POSITION, NAME_POSITION);
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
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return ;
    }
    for(s32 i=0;i<t_shader->m_paramtbl.size();i++) {
        ParamTblDsp* t_dsp = &(t_shader->m_paramtbl[i]);
        SVParamTblPtr t_tbl = t_dsp->m_tbl;
        for(s32 i=0;i<t_tbl->m_param_dsps.size();i++) {
            u32 t_locate = glGetUniformLocation(m_programm, t_tbl->m_param_dsps[i].m_name.c_str());
            if(t_locate<=0) {
                continue;
            }
            //
            if( t_tbl->m_param_dsps[i].m_type == SV_INT) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(s32);
                s32* t_p = (s32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1) {
                    glUniform1i(t_locate,*t_p);
                }else{
                    glUniform1iv(t_locate,t_cnt,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FLOAT) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(f32);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1){
                    glUniform1f(t_locate,*t_p);
                }else{
                    glUniform1fv(t_locate,t_cnt,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FVEC2) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(FVec2);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1){
                    glUniform2f(t_locate,*t_p,*(t_p+1));
                }else{
                    glUniform2fv(t_locate,t_cnt,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FVEC3) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(FVec3);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1){
                    glUniform3f(t_locate,*t_p,*(t_p+1),*(t_p+2));
                }else{
                    glUniform3fv(t_locate,t_cnt,t_p);
                }
                glUniform3fv(t_locate,1,t_p);
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FVEC4) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(FVec4);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1){
                    glUniform4f(t_locate,*t_p,*(t_p+1),*(t_p+2),*(t_p+3));
                }else{
                    glUniform4fv(t_locate,t_cnt,t_p);
                }
                glUniform4fv(t_locate,1,t_p);
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FMAT2) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(FMat2);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1){
                    glUniformMatrix4fv(t_locate,1,GL_FALSE,t_p);
                }else{
                    glUniformMatrix4fv(t_locate,t_cnt,GL_FALSE,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FMAT3) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(FMat3);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1){
                    glUniformMatrix4fv(t_locate,1,GL_FALSE,t_p);
                }else{
                    glUniformMatrix4fv(t_locate,t_cnt,GL_FALSE,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_FMAT4) {
                s32 t_cnt = t_tbl->m_param_dsps[i].m_size/sizeof(FMat4);
                f32* t_p = (f32*)(t_tbl->m_param_values->getPointer( t_tbl->m_param_dsps[i].m_off));
                if(t_cnt == 1){
                    glUniformMatrix4fv(t_locate,1,GL_FALSE,t_p);
                }else{
                    glUniformMatrix4fv(t_locate,t_cnt,GL_FALSE,t_p);
                }
            }else if( t_tbl->m_param_dsps[i].m_type == SV_BLOCK) {
            }
        }
    }
}

void SVRShaderGL::submitSurface(SVSurfacePtr _surface) {
    if(!_surface) {
        return ;
    }
    SVShaderPtr t_shader = std::dynamic_pointer_cast<SVShader>(m_logic_obj);
    if(!t_shader){
        return ;
    }
}
