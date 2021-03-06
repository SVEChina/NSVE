//
// SVRendererGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRendererGL.h"
#include "SVRTexGL.h"
#include "SVRFboGL.h"
#include "SVRShaderGL.h"
#include "SVRMeshGL.h"
//
#include "../SVRenderMgr.h"
#include "../SVRTarget.h"
#include "../SVRenderMesh.h"
#include "../../app/SVInst.h"
#include "../../app/SVGlobalParam.h"
#include "../../app/SVDispatch.h"
#include "../../base/SVCompileConfig.h"
#include "../../basesys/SVComData.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"
#include "../../mtl/SVMtlLib.h"
#include "../../mtl/SVMtlCore.h"
#include "../../mtl/SVShader.h"
#include "../../mtl/SVSurface.h"

using namespace sv;

SVRendererGL::SVRendererGL(SVInstPtr _app)
:SVRenderer(_app)
,m_cur_program(0) {
    //构建对象池
    m_rfbo_pool = MakeSharedPtr<PoolFboGL>(_app);
    m_rmesh_pool = MakeSharedPtr<PoolMeshGL>(_app);
    m_rshader_pool = MakeSharedPtr<PoolShaderGL>(_app);
    m_rtex_pool = MakeSharedPtr<PoolTexGL>(_app);
}

SVRendererGL::~SVRendererGL(){
    m_cur_program = 0;
    m_rfbo_pool = nullptr;
    m_rmesh_pool = nullptr;
    m_rshader_pool = nullptr;
    m_rtex_pool = nullptr;
}

SVRendererGLPtr SVRendererGL::share() {
    return std::dynamic_pointer_cast<SVRendererGL>(shareObject());
}

void SVRendererGL::init(s32 _version){
    SVRenderer::init();
    m_gl_version = _version;
}

void SVRendererGL::init(s32 _version,bool _offline) {
    m_gl_version = _version;
}

void SVRendererGL::info() {
    const GLubyte* tt1 = glGetString(GL_VERSION);
    const GLubyte* tt2 = glGetString(GL_VENDOR);
    const GLubyte* tt3 = glGetString(GL_RENDERER);
}

void SVRendererGL::resize(s32 _w,s32 _h) {
}

SVRTexPtr SVRendererGL::createResTexture() {
    if(m_rtex_pool) {
        return m_rtex_pool->applyObject();
    }
    return nullptr;
}

//shader
SVRShaderPtr SVRendererGL::createResShader() {
    if(m_rshader_pool) {
        return m_rshader_pool->applyObject();
    }
    return nullptr;
}

//buf-vbo 等
SVRMeshResPtr SVRendererGL::createResBuf() {
    if(m_rmesh_pool) {
        return m_rmesh_pool->applyObject();
    }
    return nullptr;
}

//fbo
SVRFboPtr SVRendererGL::createResFbo() {
    if(m_rfbo_pool) {
        return m_rfbo_pool->applyObject();
    }
    return nullptr;
}

//销毁纹理资源
void SVRendererGL::destroyResTexture(s32 _uid){
    if(m_rtex_pool) {
        m_rtex_pool->removeObject(_uid);
    }
}

//销毁shader资源
void SVRendererGL::destroyResShader(s32 _uid)  {
    if(m_rshader_pool) {
        m_rshader_pool->removeObject(_uid);
    }
}

//销毁buf资源
void SVRendererGL::destroyResBuf(s32 _uid) {
    if(m_rmesh_pool) {
        m_rmesh_pool->removeObject(_uid);
    }
}

//销毁fbo资源
void SVRendererGL::destroyResFbo(s32 _uid) {
    if(m_rfbo_pool) {
        m_rfbo_pool->removeObject(_uid);
    }
}

//获取纹理资源
SVRTexPtr SVRendererGL::getResTexture(s32 _uid) const {
    if(m_rtex_pool) {
        return m_rtex_pool->getObject(_uid);
    }
    return nullptr;
}

//获取shader资源
SVRShaderPtr SVRendererGL::getResShader(s32 _uid) const{
    if(m_rshader_pool) {
        return m_rshader_pool->getObject(_uid);
    }
    return nullptr;
}

//获取buf资源
SVRMeshResPtr SVRendererGL::getResBuf(s32 _uid) const{
    if(m_rmesh_pool) {
        return m_rmesh_pool->getObject(_uid);
    }
    return nullptr;
}

//获取fbo资源
SVRFboPtr SVRendererGL::getResFbo(s32 _uid) const {
    if(m_rfbo_pool) {
        return m_rfbo_pool->getObject(_uid);
    }
    return nullptr;
}

void SVRendererGL::bindTarget(s32 _poolid) {
    SVRFboPtr t_fbo = getResFbo(_poolid);
    if(t_fbo) {
        t_fbo->bind(share());
    }
}

void SVRendererGL::unbindTarget(s32 _poolid) {
    SVRFboPtr t_fbo = getResFbo(_poolid);
    if(t_fbo) {
        t_fbo->unbind(share());
    }
}

//处理材质
bool SVRendererGL::processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface) {
    if(_mtl && _mtl->getShader() ) {
        if(_surface ) {
            _mtl->getShader()->submitParam(_surface->m_tbl);
        }
        bool t_ret = _mtl->getShader()->active();   //active的时候传递了uniform
        if(t_ret) {
            //提交sampler
            //根据shader中的描述来添加纹理
            ShaderDsp* t_shader_dsp = _mtl->getShader()->getShaderDsp();
            s32 t_sampler_index = 0;
            for(s32 i = 0; i<t_shader_dsp->m_samplers.size(); i++ ) {
                SVString t_name = t_shader_dsp->m_samplers[i].m_name;
                if(t_name != "") {
                    SVTexturePtr t_tex = _surface->getTexture(t_name.c_str());
                    if(t_tex) {
                        processTexture(t_tex->getResTex(),
                                       t_sampler_index++,
                                       t_name.c_str() );
                    }else{
                        s32 t_stage = t_shader_dsp->m_samplers[i].m_stage;
                        s32 t_chn = t_shader_dsp->m_samplers[i].m_chn;
                        //向surface上找目标纹理
                        t_tex = _surface->getTexture(t_stage,t_chn);
                        if(t_tex) {
                            processTexture(t_tex->getResTex(),
                                           t_sampler_index++,
                                           t_name.c_str() );
                        }
                    }
                }
            }
            //设置状态
            //blend
            if( _mtl->m_blend_enable ) {
                glEnable(GL_BLEND);
                s32 src_param = GL_SRC_ALPHA;
                s32 dst_param = GL_ONE_MINUS_SRC_COLOR;
                switch( _mtl->m_blend_src_param )  {
                    case BLEND_ZERO:
                        src_param = GL_ZERO; break;
                    case BLEND_ONE:
                        src_param = GL_ONE; break;
                    case BLEND_SRC_COLOR:
                        src_param = GL_SRC_COLOR; break;
                    case BLEND_ONE_MINUS_SRC_COLOR:
                        src_param = GL_ONE_MINUS_SRC_COLOR; break;
                    case BLEND_SRC_ALPHA:
                        src_param = GL_SRC_ALPHA; break;
                    case BLEND_ONE_MINUS_SRC_ALPHA:
                        src_param = GL_ONE_MINUS_SRC_ALPHA; break;
                    case BLEND_DST_COLOR:
                        src_param = GL_DST_COLOR; break;
                    case BLEND_ONE_MINUS_DST_COLOR:
                        src_param = GL_ONE_MINUS_DST_COLOR; break;
                    case BLEND_DST_ALPHA:
                        src_param = GL_DST_ALPHA; break;
                    case BLEND_ONE_MINUS_DEST_ALPHA:
                        src_param = GL_ONE_MINUS_DST_ALPHA; break;
                    case BLEND_SRC1_COLOR:
                        src_param = GL_ONE; break;
                    case BLEND_ONE_MINUS_SRC1_COLOR:
                        src_param = GL_ONE; break;
                    case BLEND_SRC1_ALPHA:
                        src_param = GL_ONE; break;
                    case BLEND_ONE_MINUS_SRC1_ALPHA:
                        src_param = GL_ONE; break;
                }
                //
                switch( _mtl->m_blend_dst_param )  {
                    case BLEND_ZERO:
                        dst_param = GL_ZERO; break;
                    case BLEND_ONE:
                        dst_param = GL_ONE; break;
                    case BLEND_SRC_COLOR:
                        dst_param = GL_SRC_COLOR; break;
                    case BLEND_ONE_MINUS_SRC_COLOR:
                        dst_param = GL_ONE_MINUS_SRC_COLOR; break;
                    case BLEND_SRC_ALPHA:
                        dst_param = GL_SRC_ALPHA; break;
                    case BLEND_ONE_MINUS_SRC_ALPHA:
                        dst_param = GL_ONE_MINUS_SRC_ALPHA; break;
                    case BLEND_DST_COLOR:
                        dst_param = GL_DST_COLOR; break;
                    case BLEND_ONE_MINUS_DST_COLOR:
                        dst_param = GL_ONE_MINUS_DST_COLOR; break;
                    case BLEND_DST_ALPHA:
                        dst_param = GL_DST_ALPHA; break;
                    case BLEND_ONE_MINUS_DEST_ALPHA:
                        dst_param = GL_ONE_MINUS_DST_ALPHA; break;
                    case BLEND_SRC1_COLOR:
                        dst_param = GL_ONE; break;
                    case BLEND_ONE_MINUS_SRC1_COLOR:
                        dst_param = GL_ONE; break;
                    case BLEND_SRC1_ALPHA:
                        dst_param = GL_ONE; break;
                    case BLEND_ONE_MINUS_SRC1_ALPHA:
                        dst_param = GL_ONE; break;
                }
                glBlendFunc(src_param,dst_param);
            } else if(_mtl->m_blend_separate_enable) {
                glEnable(GL_BLEND);
                glBlendFuncSeparate(
                    sv2glEnum(_mtl->m_blend_separate_src_rgb),
                    sv2glEnum(_mtl->m_blend_separate_dst_rgb),
                    sv2glEnum(_mtl->m_blend_separate_src_alpha),
                    sv2glEnum(_mtl->m_blend_separate_dst_alpha)
                );
                glBlendEquation(sv2glEnum(_mtl->m_blend_separate_equation));
            } else {
                glDisable(GL_BLEND);
            }
            
            //stencil
            if(_mtl->m_stencil_enable) {
                glEnable(GL_STENCIL);
            }else{
                glDisable(GL_STENCIL);
            }
            //cull
            if(_mtl->m_cull_enable) {
                glEnable(GL_CULL_FACE);
                if( _mtl->m_frontFace == SV_CCW) {
                    glFrontFace(GL_CCW);
                }else{
                    glFrontFace(GL_CW);
                }
                if( _mtl->m_cullFace == SV_BACK) {
                    glCullFace(GL_BACK);
                }else{
                    glCullFace(GL_FRONT);
                }
            }else{
                glDisable(GL_CULL_FACE);
            }
            
            //alpha
            if(_mtl->m_alpha_enable) {
                
            }else{
                
            }
            //depth
            if(_mtl->m_depth_enable) {
                glEnable(GL_DEPTH_TEST);
                //m_depth_method
            }else{
                glDisable(GL_DEPTH_TEST);
            }
        }
        return t_ret;
    }
    return false;
}

//处理mesh
bool SVRendererGL::processMesh(SVRenderMeshPtr _mesh) {
    if(_mesh && _mesh->getResBuffer() ) {
        _mesh->getResBuffer()->process( share() );
        return true;
    }
    return false;
}

bool SVRendererGL::processTexture(SVRTexPtr _tex,s32 _index,cptr8 _samplename) {
    SVRTexGLPtr t_r_gl_tex = std::dynamic_pointer_cast<SVRTexGL>(_tex);
    if(t_r_gl_tex) {
        t_r_gl_tex->commit();
        s32 t_tex_handle = glGetUniformLocation(m_cur_program, _samplename);
        if(t_tex_handle>=0) {
            glActiveTexture(GL_TEXTURE0 + _index);
            glBindTexture(GL_TEXTURE_2D, t_r_gl_tex->m_res_id );
            glUniform1i(t_tex_handle, _index);
        }
    }
    return true;
}

//处理mesh
void SVRendererGL::drawMesh(SVRenderMeshPtr _mesh ) {
    if(_mesh && _mesh->getResBuffer() ) {
        _mesh->getResBuffer()->draw( share() );
    }
}

//屏幕空间绘制
void SVRendererGL::drawScreen(SV_TEXIN _texid) {
    SVTexturePtr t_tex = getInTexture(_texid);
    if(!t_tex){
        return ;
    }
#if  defined(SV_IOS)
    glPushGroupMarkerEXT(0,"drawScreen");
#endif    
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
    t_surface->setTexture(1,0,t_tex);
    FVec2 t_invert = FVec2(1.0f,1.0f);
    t_surface->setParam("u_invert", t_invert);
    //激活材质
    SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("screen");
    SVRenderMeshPtr t_mesh = mApp->getComData()->screenMesh();
    if(t_mtl && t_mesh) {
        t_mtl->reloadShader();
        bool t_ret = processMtl(t_mtl,t_surface);
        if(!t_ret) {
            t_surface = nullptr;
#if  defined(SV_IOS)
    glPopGroupMarkerEXT();
#endif
            return ;
        }
        t_ret = processMesh(t_mesh);
        if(!t_ret) {
            t_surface = nullptr;
#if  defined(SV_IOS)
    glPopGroupMarkerEXT();
#endif
            return ;
        }
        drawMesh(t_mesh);
    }
    t_surface = nullptr;
#if  defined(SV_IOS)
    glPopGroupMarkerEXT();
#endif
}

void SVRendererGL::debugMesh2d(SVRenderMeshPtr _mesh) {
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
    FVec2 t_scale = FVec2(1.0f,1.0f);
    t_surface->setParam("u_scale", t_scale);
    FVec2 t_off = FVec2(0.0f,0.0f);
    t_surface->setParam("u_off", t_off);
    FVec3 t_color = FVec3(0.0f,1.0f,0.0f);
    t_surface->setParam("u_color", t_color);
    SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("debug2d");
    if(t_mtl && _mesh) {
        t_mtl->reloadShader();
        bool t_ret = processMtl(t_mtl,t_surface);
        if(!t_ret) {
            t_surface = nullptr;
            return ;
        }
        _mesh->setDrawMethod(E_DRAW_POINTS);
        t_ret = processMesh(_mesh);
        if(!t_ret) {
            t_surface = nullptr;
            return ;
        }
        drawMesh(_mesh);
    }
    t_surface = nullptr;
}

void SVRendererGL::debugMesh3d(SVRenderMeshPtr _mesh) {
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
//    FVec2 t_scale = FVec2(1.0f,1.0f);
//    t_surface->setParam("u_scale", t_scale);
    FVec3 t_color = FVec3(0.0f,1.0f,0.0f);
    t_surface->setParam("u_color", t_color);
    SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("debug3d");
    if(t_mtl && _mesh) {
        t_mtl->reloadShader();
        bool t_ret = processMtl(t_mtl,t_surface);
        if(!t_ret) {
            t_surface = nullptr;
            return ;
        }
        _mesh->setDrawMethod(E_DRAW_POINTS);
        t_ret = processMesh(_mesh);
        if(!t_ret) {
            t_surface = nullptr;
            return ;
        }
        drawMesh(_mesh);
    }
    t_surface = nullptr;
}
