//
// SVRResGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTexGL.h"
#include "../../mtl/SVTexture.h"
#include "../../third/rapidjson/document.h"
#include "../../app/SVInst.h"
#include "../../base/SVDataSwap.h"
#include "../../work/SVTdCore.h"
#include "../../base/SVDataChunk.h"
#include "../../mtl/SVMtlDef.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"
#include "../../file/SVFileMgr.h"
#include "../../rendercore/SVRenderMgr.h"
#include "../SVRenderer.h"
#include "../SVGL/SVRendererGL.h"

using namespace sv;

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

SVRTexGL::SVRTexGL(SVInstPtr _app)
:SVRTex(_app)
,m_res_id(0) {
    m_dataformate = GL_RGBA;
    m_informate = GL_RGBA;
}

SVRTexGL::~SVRTexGL(){
    SV_LOG_INFO("SVRTexGL destroy %d ",m_res_id);
}

void SVRTexGL::load(SVRendererPtr _renderer,SVTextureDsp* _tex_dsp) {
    SVRTex::load(_renderer,_tex_dsp);
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    if(t_rm && m_texture_dsp) {
        SV_LOG_INFO("SVRTexGL create %d\n",m_res_id);
        //数据格式
        m_dataformate = GL_RGBA;
        m_informate = GL_RGBA;
        if(_tex_dsp->m_data_formate == SV_FORMAT_R8 ) {
            m_dataformate = GL_LUMINANCE;
            m_informate = GL_LUMINANCE;
        }else if(_tex_dsp->m_data_formate == SV_FORMAT_RG8 ) {
            m_dataformate = GL_LUMINANCE_ALPHA;
            m_informate = GL_LUMINANCE_ALPHA;
        }else if(_tex_dsp->m_data_formate == SV_FORMAT_RGB8) {
            m_dataformate = GL_RGB;
            m_informate = GL_RGB;
        }else if(_tex_dsp->m_data_formate == SV_FORMAT_RGBA8) {
            m_dataformate = GL_RGBA;
            m_informate = GL_RGBA;
        }else if(_tex_dsp->m_data_formate == SV_FORMAT_BGRA8) {
            m_dataformate = GL_BGRA;    //glext
            m_informate = GL_RGBA;
        }
        //生成纹理
        s32 t_tex_kind = GL_TEXTURE_2D;
        glGenTextures(1, &m_res_id);
        if(m_texture_dsp->m_image_type == SV_IMAGE_1D) {
#ifdef SV_OSX
            t_tex_kind = GL_TEXTURE_1D;
            glBindTexture(GL_TEXTURE_1D, m_res_id);
            SVDataSwapPtr t_data = m_texture_dsp->m_pData[0];
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
        }else if(m_texture_dsp->m_image_type == SV_IMAGE_2D) {
            t_tex_kind = GL_TEXTURE_2D;
            glBindTexture(GL_TEXTURE_2D, m_res_id);
            SVDataSwapPtr t_data = m_texture_dsp->m_pData[0];
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
        }else if(m_texture_dsp->m_image_type == SV_IMAGE_3D) {
            t_tex_kind = GL_TEXTURE_3D;
            glBindTexture(GL_TEXTURE_3D, m_res_id);
            SVDataSwapPtr t_data = m_texture_dsp->m_pData[0];
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
        }else if(m_texture_dsp->m_image_type == SV_IMAGE_CUBE) {
            t_tex_kind = GL_TEXTURE_CUBE_MAP;
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_res_id);
            for(s32 i = 0;i<6;i++) {
                SVDataSwapPtr t_data = m_texture_dsp->m_pData[i];
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

void SVRTexGL::unload() {
    SVRRes::unload();
    if(m_res_id>0){
        glDeleteTextures(1, &m_res_id);
        m_res_id = 0;
    }
}

void SVRTexGL::commit() {
    if(!m_texture_dsp)
        return ;
    m_texLock->lock();
    if(m_texture_dsp->m_image_type == SV_IMAGE_1D) {
        if(m_texture_dsp->m_pData[0]) {
#ifdef SV_OSX
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
    }else if(m_texture_dsp->m_image_type == SV_IMAGE_2D) {
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
    }else if(m_texture_dsp->m_image_type == SV_IMAGE_3D) {
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
    }else if(m_texture_dsp->m_image_type == SV_IMAGE_CUBE) {
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

void SVRTexGL::swap(SVRTexGLPtr _rtex) {
    SVRTexGLPtr tt = dynamic_pointer_cast<SVRTexGL>(_rtex);
    if(tt) {
        u32 t_res_id = tt->m_res_id;
        tt->m_res_id = m_res_id;
        m_res_id = t_res_id;
    }
}
