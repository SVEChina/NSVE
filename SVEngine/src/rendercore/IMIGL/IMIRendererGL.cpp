//
// IMIRendererGL.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRendererGL.h"
#include "IMIRTexGL.h"
#include "IMIRFboGL.h"
#include "IMIRShaderGL.h"
#include "IMIRMeshGL.h"
//
#include "../IMIRenderMgr.h"
#include "../IMIRTarget.h"
#include "../IMIRenderMesh.h"
#include "../../app/IMIInst.h"
#include "../../app/IMIGlobalParam.h"
#include "../../app/IMIDispatch.h"
#include "../../base/IMICompileConfig.h"
#include "../../basesys/IMIComData.h"
#include "../../mtl/IMITexMgr.h"
#include "../../mtl/IMITexture.h"
#include "../../mtl/IMIMtlLib.h"
#include "../../mtl/IMIMtlCore.h"
#include "../../mtl/IMIShader.h"
#include "../../mtl/IMISurface.h"

using namespace imi;

IMIRendererGL::IMIRendererGL(IMIInstPtr _app)
:IMIRenderer(_app)
,m_cur_program(0) {
    //构建对象池
    m_rfbo_pool = MakeSharedPtr<PoolFboGL>(_app);
    m_rmesh_pool = MakeSharedPtr<PoolMeshGL>(_app);
    m_rshader_pool = MakeSharedPtr<PoolShaderGL>(_app);
    m_rtex_pool = MakeSharedPtr<PoolTexGL>(_app);
}

IMIRendererGL::~IMIRendererGL(){
    m_cur_program = 0;
    m_rfbo_pool = nullptr;
    m_rmesh_pool = nullptr;
    m_rshader_pool = nullptr;
    m_rtex_pool = nullptr;
}

IMIRendererGLPtr IMIRendererGL::share() {
    return std::dynamic_pointer_cast<IMIRendererGL>(shareObject());
}

void IMIRendererGL::init(s32 _version){
    IMIRenderer::init();
    m_gl_version = _version;
}

void IMIRendererGL::init(s32 _version,bool _offline) {
    m_gl_version = _version;
}

void IMIRendererGL::info() {
    const GLubyte* tt1 = glGetString(GL_VERSION);
    const GLubyte* tt2 = glGetString(GL_VENDOR);
    const GLubyte* tt3 = glGetString(GL_RENDERER);
}

void IMIRendererGL::resize(s32 _w,s32 _h) {
}

IMIRTexPtr IMIRendererGL::createResTexture() {
    if(m_rtex_pool) {
        return m_rtex_pool->applyObject();
    }
    return nullptr;
}

//shader
IMIRShaderPtr IMIRendererGL::createResShader() {
    if(m_rshader_pool) {
        return m_rshader_pool->applyObject();
    }
    return nullptr;
}

//buf-vbo 等
IMIRMeshResPtr IMIRendererGL::createResBuf() {
    if(m_rmesh_pool) {
        return m_rmesh_pool->applyObject();
    }
    return nullptr;
}

//fbo
IMIRFboPtr IMIRendererGL::createResFbo() {
    if(m_rfbo_pool) {
        return m_rfbo_pool->applyObject();
    }
    return nullptr;
}

//销毁纹理资源
void IMIRendererGL::destroyResTexture(s32 _uid){
    if(m_rtex_pool) {
        m_rtex_pool->removeObject(_uid);
    }
}

//销毁shader资源
void IMIRendererGL::destroyResShader(s32 _uid)  {
    if(m_rshader_pool) {
        m_rshader_pool->removeObject(_uid);
    }
}

//销毁buf资源
void IMIRendererGL::destroyResBuf(s32 _uid) {
    if(m_rmesh_pool) {
        m_rmesh_pool->removeObject(_uid);
    }
}

//销毁fbo资源
void IMIRendererGL::destroyResFbo(s32 _uid) {
    if(m_rfbo_pool) {
        m_rfbo_pool->removeObject(_uid);
    }
}

//获取纹理资源
IMIRTexPtr IMIRendererGL::getResTexture(s32 _uid) const {
    if(m_rtex_pool) {
        return m_rtex_pool->getObject(_uid);
    }
    return nullptr;
}

//获取shader资源
IMIRShaderPtr IMIRendererGL::getResShader(s32 _uid) const{
    if(m_rshader_pool) {
        return m_rshader_pool->getObject(_uid);
    }
    return nullptr;
}

//获取buf资源
IMIRMeshResPtr IMIRendererGL::getResBuf(s32 _uid) const{
    if(m_rmesh_pool) {
        return m_rmesh_pool->getObject(_uid);
    }
    return nullptr;
}

//获取fbo资源
IMIRFboPtr IMIRendererGL::getResFbo(s32 _uid) const {
    if(m_rfbo_pool) {
        return m_rfbo_pool->getObject(_uid);
    }
    return nullptr;
}

void IMIRendererGL::bindTarget(s32 _poolid) {
    IMIRFboPtr t_fbo = getResFbo(_poolid);
    if(t_fbo) {
        t_fbo->bind(share());
    }
}

void IMIRendererGL::unbindTarget(s32 _poolid) {
    IMIRFboPtr t_fbo = getResFbo(_poolid);
    if(t_fbo) {
        t_fbo->unbind(share());
    }
}

//处理材质
bool IMIRendererGL::processMtl(IMIMtlCorePtr _mtl,IMISurfacePtr _surface) {
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
                IMIString t_name = t_shader_dsp->m_samplers[i].m_name;
                if(t_name != "") {
                    IMITexturePtr t_tex = _surface->getTexture(t_name.c_str());
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
            }else{
                glDisable(GL_BLEND);
            }
            //stencil
            if( _mtl->m_stencil_enable ) {
                glEnable(GL_STENCIL);
            }else{
                glDisable(GL_STENCIL);
            }
            //cull
            if( _mtl->m_cull_enable ) {
                glEnable(GL_CULL_FACE);
                if( _mtl->m_frontFace == IMI_CCW) {
                    glFrontFace(GL_CCW);
                }else{
                    glFrontFace(GL_CW);
                }
                if( _mtl->m_cullFace == IMI_BACK) {
                    glCullFace(GL_BACK);
                }else{
                    glCullFace(GL_FRONT);
                }
            }else{
                glDisable(GL_CULL_FACE);
            }
            //alpha
            if( _mtl->m_alpha_enable ) {
                
            }else{
                
            }
            //depth
            if( _mtl->m_depth_enable ) {
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
bool IMIRendererGL::processMesh(IMIRenderMeshPtr _mesh) {
    if(_mesh && _mesh->getResBuffer() ) {
        _mesh->getResBuffer()->process( share() );
        return true;
    }
    return false;
}

bool IMIRendererGL::processTexture(IMIRTexPtr _tex,s32 _index,cptr8 _samplename) {
    IMIRTexGLPtr t_r_gl_tex = std::dynamic_pointer_cast<IMIRTexGL>(_tex);
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
void IMIRendererGL::drawMesh(IMIRenderMeshPtr _mesh ) {
    if(_mesh && _mesh->getResBuffer() ) {
        _mesh->getResBuffer()->draw( share() );
    }
}

//屏幕空间绘制
void IMIRendererGL::drawScreen(IMI_TEXIN _texid) {
    IMITexturePtr t_tex = getInTexture(_texid);
    if(!t_tex){
        return ;
    }
#if  defined(IMI_IOS)
    glPushGroupMarkerEXT(0,"drawScreen");
#endif    
    IMISurfacePtr t_surface = MakeSharedPtr<IMISurface>();
    t_surface->setTexture(1,0,t_tex);
    FVec2 t_invert = FVec2(1.0f,1.0f);
    t_surface->setParam("u_invert", t_invert);
    //激活材质
    IMIMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("screen");
    IMIRenderMeshPtr t_mesh = mApp->getComData()->screenMesh();
    if(t_mtl && t_mesh) {
        t_mtl->reloadShader();
        bool t_ret = processMtl(t_mtl,t_surface);
        if(!t_ret) {
            t_surface = nullptr;
#if  defined(IMI_IOS)
    glPopGroupMarkerEXT();
#endif
            return ;
        }
        t_ret = processMesh(t_mesh);
        if(!t_ret) {
            t_surface = nullptr;
#if  defined(IMI_IOS)
    glPopGroupMarkerEXT();
#endif
            return ;
        }
        drawMesh(t_mesh);
    }
    t_surface = nullptr;
#if  defined(IMI_IOS)
    glPopGroupMarkerEXT();
#endif
}

void IMIRendererGL::debugMesh2d(IMIRenderMeshPtr _mesh) {
    IMISurfacePtr t_surface = MakeSharedPtr<IMISurface>();
    FVec2 t_scale = FVec2(1.0f,1.0f);
    t_surface->setParam("u_scale", t_scale);
    FVec2 t_off = FVec2(0.0f,0.0f);
    t_surface->setParam("u_off", t_off);
    FVec3 t_color = FVec3(0.0f,1.0f,0.0f);
    t_surface->setParam("u_color", t_color);
    IMIMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("debug2d");
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

void IMIRendererGL::debugMesh3d(IMIRenderMeshPtr _mesh) {
    IMISurfacePtr t_surface = MakeSharedPtr<IMISurface>();
//    FVec2 t_scale = FVec2(1.0f,1.0f);
//    t_surface->setParam("u_scale", t_scale);
    FVec3 t_color = FVec3(0.0f,1.0f,0.0f);
    t_surface->setParam("u_color", t_color);
    IMIMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("debug3d");
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
