//
// IMIRResGL.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRTexGL.h"
#include "../../mtl/IMITexture.h"
#include "../../third/rapidjson/document.h"
#include "../../app/IMIInst.h"
#include "../../base/IMIDataSwap.h"
#include "../../work/IMITdCore.h"
#include "../../base/IMIDataChunk.h"
#include "../../mtl/IMIMtlDef.h"
#include "../../mtl/IMITexMgr.h"
#include "../../mtl/IMITexture.h"
#include "../../file/IMIFileMgr.h"
#include "../../rendercore/IMIRenderMgr.h"
#include "../IMIRenderer.h"
#include "../IMIGL/IMIRendererGL.h"

using namespace imi;

//
bool isPow2(s32 _value) {
    s32 t_flag = 2;
    while(1) {
        if(t_flag == _value ) {
            return true;
        }
        t_flag*=2;
        if(t_flag>_value) {
            break;
        }
        
    }
    return false;
}

IMIRTexGL::IMIRTexGL(IMIInstPtr _app)
:IMIRTex(_app)
,m_res_id(0) {
    m_dataformate = GL_RGBA;
    m_informate = GL_RGBA;
}

IMIRTexGL::~IMIRTexGL(){
    IMI_LOG_INFO("IMIRTexGL destroy %d ",m_res_id);
}

void IMIRTexGL::load(IMIRendererPtr _renderer,IMITextureDsp* _tex_dsp) {
    IMIRTex::load(_renderer,_tex_dsp);
    IMIRendererGLPtr t_rm = std::dynamic_pointer_cast<IMIRendererGL>(_renderer);
    if(t_rm && m_texture_dsp) {
        IMI_LOG_INFO("IMIRTexGL create %d\n",m_res_id);
        //数据格式
        m_dataformate = GL_RGBA;
        m_informate = GL_RGBA;
        if(_tex_dsp->m_data_formate == IMI_FORMAT_R8 ) {
            m_dataformate = GL_LUMINANCE;
            m_informate = GL_LUMINANCE;
        }else if(_tex_dsp->m_data_formate == IMI_FORMAT_RG8 ) {
            m_dataformate = GL_LUMINANCE_ALPHA;
            m_informate = GL_LUMINANCE_ALPHA;
        }else if(_tex_dsp->m_data_formate == IMI_FORMAT_RGB8) {
            m_dataformate = GL_RGB;
            m_informate = GL_RGB;
        }else if(_tex_dsp->m_data_formate == IMI_FORMAT_RGBA8) {
            m_dataformate = GL_RGBA;
            m_informate = GL_RGBA;
        }else if(_tex_dsp->m_data_formate == IMI_FORMAT_BGRA8) {
            m_dataformate = GL_BGRA;    //glext
            m_informate = GL_RGBA;
        }
        //生成纹理
        s32 t_tex_kind = GL_TEXTURE_2D;
        glGenTextures(1, &m_res_id);
        if(m_texture_dsp->m_image_type == IMI_IMAGE_1D) {
#ifdef IMI_OSX
            t_tex_kind = GL_TEXTURE_1D;
            glBindTexture(GL_TEXTURE_1D, m_res_id);
            IMIDataSwapPtr t_data = m_texture_dsp->m_pData[0];
            if(t_data) {
                glTexImage1D(GL_TEXTURE_1D,
                             0,
                             m_informate,
                             m_texture_dsp->m_width,
                             0,
                             t_datafmt,
                             GL_UNSIGNED_BYTE,
                             t_data->getData());
            }else{
                glTexImage1D(GL_TEXTURE_1D,
                             0,
                             m_informate,
                             m_texture_dsp->m_width,
                             0,
                             t_datafmt,
                             GL_UNSIGNED_BYTE,
                             0);
            }
#endif
        }else if(m_texture_dsp->m_image_type == IMI_IMAGE_2D) {
            t_tex_kind = GL_TEXTURE_2D;
            glBindTexture(GL_TEXTURE_2D, m_res_id);
            IMIDataSwapPtr t_data = m_texture_dsp->m_pData[0];
            if(t_data) {
                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             m_informate,
                             m_texture_dsp->m_width,
                             m_texture_dsp->m_height,
                             0,
                             m_dataformate,
                             GL_UNSIGNED_BYTE,
                             t_data->getData() );
                
            } else {
                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             m_informate,
                             m_texture_dsp->m_width,
                             m_texture_dsp->m_height,
                             0,
                             m_dataformate,
                             GL_UNSIGNED_BYTE,
                             0);
            }
        }else if(m_texture_dsp->m_image_type == IMI_IMAGE_3D) {
            t_tex_kind = GL_TEXTURE_3D;
            glBindTexture(GL_TEXTURE_3D, m_res_id);
            IMIDataSwapPtr t_data = m_texture_dsp->m_pData[0];
            if(t_data) {
                glTexImage3D(GL_TEXTURE_3D,0,
                             m_informate,
                             m_texture_dsp->m_width,
                             m_texture_dsp->m_height,
                             m_texture_dsp->m_depth,
                             0,
                             m_dataformate,
                             GL_UNSIGNED_BYTE,
                             t_data->getData() );
            }else{
                glTexImage3D(GL_TEXTURE_3D,0,
                             m_informate,
                             m_texture_dsp->m_width,
                             m_texture_dsp->m_height,
                             m_texture_dsp->m_depth,
                             0,
                             m_dataformate,
                             GL_UNSIGNED_BYTE,0);
            }
        }else if(m_texture_dsp->m_image_type == IMI_IMAGE_CUBE) {
            t_tex_kind = GL_TEXTURE_CUBE_MAP;
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_res_id);
            for(s32 i = 0;i<6;i++) {
                IMIDataSwapPtr t_data = m_texture_dsp->m_pData[i];
                if(t_data) {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,
                                 m_informate,
                                 m_texture_dsp->m_width,
                                 m_texture_dsp->m_height,
                                 0,
                                 m_dataformate,
                                 GL_UNSIGNED_BYTE,
                                 t_data->getData());
                }
            }
        }
        //
        if (m_texture_dsp->m_minmap) {
            if( isPow2(m_texture_dsp->m_width) && isPow2(m_texture_dsp->m_height%2) ) {
                glGenerateMipmap(t_tex_kind);
                glTexParameteri(t_tex_kind, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }else{
                glTexParameteri(t_tex_kind, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            }
        }else{
            glTexParameteri(t_tex_kind, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        }
        glTexParameteri(t_tex_kind, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(t_tex_kind, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(t_tex_kind, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //
        m_exist = true;
    }
}

void IMIRTexGL::unload() {
    IMIRRes::unload();
    if(m_res_id>0){
        glDeleteTextures(1, &m_res_id);
        m_res_id = 0;
    }
}

void IMIRTexGL::commit() {
    if(!m_texture_dsp)
        return ;
    m_texLock->lock();
    if(m_texture_dsp->m_image_type == IMI_IMAGE_1D) {
        if(m_texture_dsp->m_pData[0]) {
#ifdef IMI_OSX
            glBindTexture(GL_TEXTURE_1D, m_res_id);
            glTexSubImage1D(GL_TEXTURE_1D,
                            0,
                            0,
                            m_texture_dsp->m_width,
                            m_dataformate,
                            GL_UNSIGNED_BYTE,
                            m_texture_dsp->m_pData[0]->getData());
            m_texture_dsp->m_pData[0] = nullptr;
#endif
        }
    }else if(m_texture_dsp->m_image_type == IMI_IMAGE_2D) {
        if(m_texture_dsp->m_pData[0]) {
            glBindTexture(GL_TEXTURE_2D, m_res_id);
            glTexSubImage2D(GL_TEXTURE_2D,
                            0,
                            0,0,
                            m_texture_dsp->m_width,
                            m_texture_dsp->m_height,
                            m_dataformate,
                            GL_UNSIGNED_BYTE,
                            m_texture_dsp->m_pData[0]->getData());
            m_texture_dsp->m_pData[0] = nullptr;
        }
    }else if(m_texture_dsp->m_image_type == IMI_IMAGE_3D) {
        if(m_texture_dsp->m_pData[0]) {
            glBindTexture(GL_TEXTURE_3D, m_res_id);
            glTexSubImage3D(GL_TEXTURE_3D,
                            0,
                            0,0,0,
                            m_texture_dsp->m_width,
                            m_texture_dsp->m_height,
                            m_texture_dsp->m_depth,
                            m_dataformate,
                            GL_UNSIGNED_BYTE,
                            m_texture_dsp->m_pData[0]->getData());
            m_texture_dsp->m_pData[0] = nullptr;
        }
    }else if(m_texture_dsp->m_image_type == IMI_IMAGE_CUBE) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_res_id);
        for(s32 i = 0;i<6;i++) {
            if(m_texture_dsp->m_pData[i]) {
                glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                0,
                                0,0,
                                m_texture_dsp->m_width,
                                m_texture_dsp->m_height,
                                m_dataformate,
                                GL_UNSIGNED_BYTE,
                                m_texture_dsp->m_pData[i]->getData());
                m_texture_dsp->m_pData[i] = nullptr;
            }
        }
    }
    m_texLock->unlock();
}

void IMIRTexGL::swap(IMIRTexGLPtr _rtex) {
    IMIRTexGLPtr tt = dynamic_pointer_cast<IMIRTexGL>(_rtex);
    if(tt) {
        u32 t_res_id = tt->m_res_id;
        tt->m_res_id = m_res_id;
        m_res_id = t_res_id;
    }
}
