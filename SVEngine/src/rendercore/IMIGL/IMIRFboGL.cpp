//
// IMIRTarget.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRFboGL.h"
#include "IMIRendererGL.h"
#include "IMIRTexGL.h"
#include "IMIRTarget.h"
#include "IMIRShaderGL.h"
#include "IMIRMeshGL.h"
#include "../../mtl/IMITexture.h"

using namespace imi;

//
IMIRFboGL::IMIRFboGL(IMIInstPtr _app)
:IMIRFbo(_app)
,m_out_tex(false)
,m_fbo_last_id(0){
}

IMIRFboGL::~IMIRFboGL() {
    m_fbo_last_id = 0;
}

void IMIRFboGL::load(IMIRendererPtr _renderer,IMITargetDsp* _logic_dsp) {
    IMIRFbo::load(_renderer,_logic_dsp);
    IMIRendererGLPtr t_rm = std::dynamic_pointer_cast<IMIRendererGL>(_renderer);
    if(t_rm && m_fbo_dsp) {
        glGetIntegerv(GL_FRAMEBUFFER_BINDING,&m_fbo_last_id);
        glGenFramebuffers(1, &m_fbo_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
        s32 t_width = m_fbo_dsp->m_width;
        s32 t_height = m_fbo_dsp->m_height;
        s32 t_target_num = m_fbo_dsp->m_target_num>IMI_SUPPORT_MAX_TAREGT ? IMI_SUPPORT_MAX_TAREGT : m_fbo_dsp->m_target_num;
        for(s32 i=0;i<t_target_num;i++) {
            IMITexturePtr t_inner_tex = _renderer->getInTexture( m_fbo_dsp->m_color_texid[0] );
            if(!t_inner_tex) {
                //需要直接创建内置纹理了
                //t_inner_tex = _renderer->directCreateInnerTexture(m_color_tex[i]);
            }
            //获取GL内置纹理的Handler
            u32 t_tex_gl_handler = 0;
            IMIRTexPtr t_r_tex = t_inner_tex->getResTex();
            if(t_r_tex) {
                IMIRTexGLPtr t_r_tex_gl = DYN_TO_SHAREPTR(IMIRTexGL, t_r_tex);
                if(t_r_tex_gl) {
                    t_tex_gl_handler = t_r_tex_gl->m_res_id;
                }
            }
            if(t_tex_gl_handler<=0) {
                //fyz error
                //glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_last_id);
                return ;
            }
            glBindTexture(GL_TEXTURE_2D,t_tex_gl_handler);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,GL_TEXTURE_2D,t_tex_gl_handler,0);
        }
        //depth
        if(m_fbo_dsp->m_use_depth && m_fbo_dsp->m_use_stencil) {
            glGenRenderbuffers(1, &m_depth_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,t_width,t_height);
            m_depth_Tex = m_stencil_Tex;
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_last_id);
            return;
        }
        if(m_fbo_dsp->m_use_depth ) {
            glGenRenderbuffers(1, &m_depth_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,t_width,t_height);//GL_DEPTH_COMPONENT16
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_last_id);
            return;
        }
        if(m_fbo_dsp->m_use_stencil ) {
            glGenRenderbuffers(1, &m_stencil_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_stencil_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX8,t_width,t_height);//GL_STENCIL_INDEX16
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_last_id);
    }
}

void IMIRFboGL::unload() {
    if(m_depth_Tex == m_stencil_Tex) {
        if(m_depth_Tex!=0) {
            glDeleteBuffers(1, &m_depth_Tex);
            m_depth_Tex = 0;
            m_stencil_Tex = 0;
        }
        return ;
    }
    if(m_depth_Tex>0) {
        glDeleteBuffers(1, &m_depth_Tex);
        m_depth_Tex = 0;
    }
    if(m_stencil_Tex>0) {
        glDeleteBuffers(1, &m_stencil_Tex);
        m_stencil_Tex = 0;
    }
    IMIRFbo::unload();
}

void IMIRFboGL::resize(s32 _width,s32 _height,IMIRendererPtr _renderer) {
    if(m_fbo_dsp->m_width!=_width || m_fbo_dsp->m_height!=_height ) {
        m_fbo_dsp->m_width = _width;
        m_fbo_dsp->m_height = _height;
        //颜色重新
        //删除，重新创建
        if(m_depth_Tex == m_stencil_Tex) {
            if(m_depth_Tex!=0) {
                glDeleteBuffers(1, &m_depth_Tex);
            }
            glGenRenderbuffers(1, &m_depth_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,m_fbo_dsp->m_width,m_fbo_dsp->m_height);
            m_depth_Tex = m_stencil_Tex;
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
        }else{
            if(m_depth_Tex>0) {
                glDeleteBuffers(1, &m_depth_Tex);
                glGenRenderbuffers(1, &m_depth_Tex);
                glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
                glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,m_fbo_dsp->m_width,m_fbo_dsp->m_height);//GL_DEPTH_COMPONENT16
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            }
            if(m_stencil_Tex>0) {
                glDeleteBuffers(1, &m_stencil_Tex);
                glGenRenderbuffers(1, &m_stencil_Tex);
                glBindRenderbuffer(GL_RENDERBUFFER, m_stencil_Tex);
                glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX8,m_fbo_dsp->m_width,m_fbo_dsp->m_height);//GL_STENCIL_INDEX16
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
            }
        }
    }
}

void IMIRFboGL::bind(IMIRendererPtr _renderer) {
    if(m_fbo_dsp) {
        glGetIntegerv(GL_FRAMEBUFFER_BINDING,&m_fbo_last_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
        s32 t_target_num = m_fbo_dsp->m_target_num>IMI_SUPPORT_MAX_TAREGT ? IMI_SUPPORT_MAX_TAREGT : m_fbo_dsp->m_target_num;
        for(s32 i=0;i<t_target_num;i++) {
            IMITexturePtr t_inner_tex = _renderer->getInTexture( m_fbo_dsp->m_color_texid[0] );
            if(t_inner_tex) {
                u32 t_tex_gl_handler = 0;
                IMIRTexPtr t_r_tex = t_inner_tex->getResTex();
                IMIRTexGLPtr t_r_tex_gl = DYN_TO_SHAREPTR(IMIRTexGL, t_r_tex);
                if(t_r_tex_gl) {
                    t_tex_gl_handler = t_r_tex_gl->m_res_id;
                    glBindTexture(GL_TEXTURE_2D,t_tex_gl_handler);
//                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,GL_TEXTURE_2D,t_tex_gl_handler,0);
                }
            }
        }
        glViewport(0, 0, m_fbo_dsp->m_width, m_fbo_dsp->m_height);
        glClearColor(m_fbo_dsp->m_color_r,
                     m_fbo_dsp->m_color_g,
                     m_fbo_dsp->m_color_b,
                     m_fbo_dsp->m_color_a);
        if(m_fbo_dsp->m_use_depth && m_fbo_dsp->m_use_stencil) {
            glClearDepthf(m_fbo_dsp->m_depth_value);
            glClearStencil(m_fbo_dsp->m_stencil_value);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
        }else if(m_fbo_dsp->m_use_depth) {
            glClearDepthf(m_fbo_dsp->m_depth_value);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        }else if(m_fbo_dsp->m_use_stencil) {
            glClearStencil(m_fbo_dsp->m_stencil_value);
            glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
        }else{
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
}

void IMIRFboGL::unbind(IMIRendererPtr _renderer) {
    //error
    if(m_fbo_dsp) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_last_id);
    }
}
