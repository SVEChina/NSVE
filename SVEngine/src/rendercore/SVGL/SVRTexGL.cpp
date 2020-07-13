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

SVRTexGL::SVRTexGL(SVInstPtr _app)
:SVRTex(_app)
,m_res_id(0){
}

SVRTexGL::~SVRTexGL(){
    SV_LOG_INFO("SVRTexGL destroy %d ",m_uid);
}

void SVRTexGL::create(SVRendererPtr _renderer) {
    SVRRes::create(_renderer);
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    SVTexturePtr t_texture = std::dynamic_pointer_cast<SVTexture>(m_logic_obj);
    if(t_rm && t_texture) {
        SV_LOG_INFO("SVRTexGL create %d ",m_uid);
        SVTextureDsp* t_dsp = t_texture->getTextureDsp();
        //内部格式
        m_informate = GL_RGBA;
        if(t_dsp->m_inFormate == E_TEX_RGBA8888) {
            m_informate = GL_RGBA;
        }else if(t_dsp->m_inFormate == E_TEX_RGB888) {
            m_informate = GL_RGBA;
        }else if(t_dsp->m_inFormate == E_TEX_ALPHA) {
            m_informate = GL_RGBA;
        }else if(t_dsp->m_inFormate == E_TEX_L_ALPHA) {
            m_informate = GL_RGBA;
        }
        //数据格式
        s32 t_datafmt = GL_RGBA;
        if(t_dsp->m_dataFormate == E_TEX_RGBA8888) {
            t_datafmt = GL_RGBA;
        }else if(t_dsp->m_dataFormate == E_TEX_RGB888) {
            t_datafmt = GL_RGBA;
        }else if(t_dsp->m_dataFormate == E_TEX_ALPHA) {
            t_datafmt = GL_RGBA;
        }else if(t_dsp->m_dataFormate == E_TEX_L_ALPHA) {
            t_datafmt = GL_RGBA;
        }
        SVDataSwapPtr t_data = t_texture->getTextureData();
        //生成纹理
        m_tex_kind = t_dsp->m_kind;
        m_width = t_dsp->m_width;
        m_height = t_dsp->m_height;
        m_depth = t_dsp->m_depth;
        s32 t_tex_kind = GL_TEXTURE_2D;
        glGenTextures(1, &m_res_id);
        if(m_tex_kind == E_TEX_1D) {
            t_tex_kind = GL_TEXTURE_1D;
            glBindTexture(GL_TEXTURE_1D, m_res_id);
            if(t_data) {
                glTexImage1D(GL_TEXTURE_1D,
                             0,
                             m_informate,
                             m_width,
                             0,
                             t_datafmt,
                             GL_UNSIGNED_BYTE,
                             t_data->getData());
            }else{
                glTexImage1D(GL_TEXTURE_1D,
                             0,
                             m_informate,
                             m_width,
                             0,
                             t_datafmt,
                             GL_UNSIGNED_BYTE,
                             0);
            }
        }else if(m_tex_kind == E_TEX_2D) {
            t_tex_kind = GL_TEXTURE_2D;
            glBindTexture(GL_TEXTURE_2D, m_res_id);
            if(t_data) {
                glTexImage2D(GL_TEXTURE_2D,
                    0,
                    m_informate,
                    m_width,
                    m_height,
                    0,
                    t_datafmt,
                    GL_UNSIGNED_BYTE,
                    0);
            } else {
                glTexImage2D(GL_TEXTURE_2D,
                    0,
                    m_informate,
                    m_width,
                    m_height,
                    0,
                    t_datafmt,
                    GL_UNSIGNED_BYTE,
                    t_data->getData() );
            }
        }else if(m_tex_kind == E_TEX_3D) {
            t_tex_kind = GL_TEXTURE_3D;
            glBindTexture(GL_TEXTURE_3D, m_res_id);
            if(t_data) {
                glTexImage3D(GL_TEXTURE_3D,
                0,
                m_informate,
                m_width,
                m_height,
                m_depth,
                0,
                t_datafmt,
                GL_UNSIGNED_BYTE,
                t_data->getData() );
            }else{
                glTexImage3D(GL_TEXTURE_3D,
                0,
                m_informate,
                m_width,
                m_height,
                m_depth,
                0,
                t_datafmt,
                GL_UNSIGNED_BYTE,
                0);
            }
        }else if(m_tex_kind == E_TEX_CUBE) {
            t_tex_kind = GL_TEXTURE_CUBE_MAP;
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_res_id);
            for(s32 i = 0;i<6;i++) {
                SVDataSwapPtr t_data = t_texture->getTextureCubeData(i);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                              0,
                              m_informate,
                              m_width,
                              m_height,
                              0,
                              t_datafmt,
                              GL_UNSIGNED_BYTE,
                              t_data->getData());
            }
        }
        //
        if (t_dsp->m_minmap) {
            glGenerateMipmap(t_tex_kind);
            glTexParameteri(t_tex_kind, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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

void SVRTexGL::destroy(SVRendererPtr _renderer) {
    SVRRes::destroy(_renderer);
    if(m_res_id>0){
        glDeleteTextures(1, &m_res_id);
        m_res_id = 0;
    }
}

void SVRTexGL::commit() {
    m_texLock->lock();
    if(m_tex_kind == E_TEX_1D) {
        if(m_data) {
            glBindTexture(GL_TEXTURE_1D, m_res_id);
            glTexSubImage1D(GL_TEXTURE_1D,
                            0,
                            0, m_width,
                            m_informate,
                            GL_UNSIGNED_BYTE,
                            m_data->getData());
            m_data = nullptr;
        }
    }else if(m_tex_kind == E_TEX_2D) {
        if(m_data) {
            glBindTexture(GL_TEXTURE_2D, m_res_id);
            glTexSubImage2D(GL_TEXTURE_2D,
                            0,
                            0,0,
                            m_width,m_height,
                            m_informate,
                            GL_UNSIGNED_BYTE,
                            m_data->getData());
            m_data = nullptr;
        }
    }else if(m_tex_kind == E_TEX_3D) {
        if(m_data) {
            glBindTexture(GL_TEXTURE_3D, m_res_id);
            glTexSubImage3D(GL_TEXTURE_3D,
                            0,
                            0,0,0,
                            m_width,m_height,m_depth,
                            m_informate,
                            GL_UNSIGNED_BYTE,
                            m_data->getData());
            m_data = nullptr;
        }
    }else if(m_tex_kind == E_TEX_CUBE) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_res_id);
        for(s32 i = 0;i<6;i++) {
            SVDataSwapPtr t_data = m_cube_data[i];
            if(t_data) {
                glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                0,
                                0,0,
                                m_width,m_height,
                                m_informate,
                                GL_UNSIGNED_BYTE,
                                t_data->getData());
                m_cube_data[i] = nullptr;
            }
        }
    }
    m_texLock->unlock();
}
