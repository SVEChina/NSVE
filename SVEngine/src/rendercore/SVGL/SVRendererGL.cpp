//
// SVRendererGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRendererGL.h"
#include "SVRTexGL.h"
#include "SVRTechGL.h"
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
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"
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

//处理材质
bool SVRendererGL::processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface) {
    if(_mtl && _mtl->getShader() ) {
        if(_surface ) {
            //更新uniform
            _mtl->getShader()->submitParam(_surface->m_tbl);
            //更新纹理
            
        }
        //
        bool t_ret = _mtl->getShader()->active();
        if(t_ret) {
            //提交纹理
            
            //设置状态
            //blend
            //stencil
            //cull
            //alpha
            //depth
        }
        return true;
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

bool SVRendererGL::processTexture(SVRTexPtr _tex,s32 _chn,s32 _type) {
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
    
}
