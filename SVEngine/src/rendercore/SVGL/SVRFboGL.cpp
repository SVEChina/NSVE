//
// SVRTarget.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRFboGL.h"
#include "SVRendererGL.h"
#include "../SVRTarget.h"

using namespace sv;

//
SVRFboGL::SVRFboGL(SVInstPtr _app)
: SVRFbo(_app)
, m_out_tex(false){
}

SVRFboGL::~SVRFboGL() {
}

void SVRFboGL::create(SVRendererPtr _renderer) {
    SVRFbo::create(_renderer);
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    SVRTargetPtr t_target = std::dynamic_pointer_cast<SVRTarget>(m_logic_obj);
    if(t_rm && t_target) {
        SVTargetDsp* t_dsp = t_target->getTargetDsp();
        glGenFramebuffers(1, &m_fbo_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
        m_width = t_dsp->m_width;
        m_height = t_dsp->m_height;
        m_target_num = t_dsp->m_target_num>SV_SUPPORT_MAX_TAREGT ? SV_SUPPORT_MAX_TAREGT : t_dsp->m_target_num;
//        //color
//        if(t_dsp->m_gl_tex>0) {
//            m_out_tex = true;
//            m_color_tex[0] = t_dsp->m_gl_tex;
//        }else{
//            //需要自己创建
//            m_out_tex = false;
//            glGenTextures(m_target_num, m_color_tex);
//        }
        for(s32 i=0;i<m_target_num;i++) {
            glBindTexture(GL_TEXTURE_2D, m_color_tex[i]);
            glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGBA,
                m_width,
                m_height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                0);
            //设置param
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            //绑定
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,GL_TEXTURE_2D,m_color_tex[i],0);
        }
        //depth
        if(t_dsp->m_use_depth && t_dsp->m_use_stencil) {
            glGenRenderbuffers(1, &m_depth_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,m_width,m_height);
            m_depth_Tex = m_stencil_Tex;
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
            return;
        }
        if(t_dsp->m_use_depth ) {
            glGenRenderbuffers(1, &m_depth_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,m_width,m_height);//GL_DEPTH_COMPONENT16
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            return;
        }
        if(t_dsp->m_use_stencil ) {
            glGenRenderbuffers(1, &m_stencil_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_stencil_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX8,m_width,m_height);//GL_STENCIL_INDEX16
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
        }
    }
}

void SVRFboGL::destroy(SVRendererPtr _renderer) {
    //
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
    SVRFbo::destroy(_renderer);
}

void SVRFboGL::resize(s32 _width,s32 _height,SVRendererPtr _renderer) {
    if(m_width!=_width || m_height!=_height ) {
        m_width = _width;
        m_height = _height;
        //颜色重新
        
        //删除，重新创建
        if(m_depth_Tex == m_stencil_Tex) {
            if(m_depth_Tex!=0) {
                glDeleteBuffers(1, &m_depth_Tex);
            }
            glGenRenderbuffers(1, &m_depth_Tex);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
            glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,m_width,m_height);
            m_depth_Tex = m_stencil_Tex;
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
        }else{
            if(m_depth_Tex>0) {
                glDeleteBuffers(1, &m_depth_Tex);
                glGenRenderbuffers(1, &m_depth_Tex);
                glBindRenderbuffer(GL_RENDERBUFFER, m_depth_Tex);
                glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,m_width,m_height);//GL_DEPTH_COMPONENT16
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_Tex);
            }
            if(m_stencil_Tex>0) {
                glDeleteBuffers(1, &m_stencil_Tex);
                glGenRenderbuffers(1, &m_stencil_Tex);
                glBindRenderbuffer(GL_RENDERBUFFER, m_stencil_Tex);
                glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX8,m_width,m_height);//GL_STENCIL_INDEX16
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_stencil_Tex);
            }
        }
    }
}

