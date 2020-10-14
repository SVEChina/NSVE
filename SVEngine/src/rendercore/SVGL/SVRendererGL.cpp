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
,m_cur_program(0){
}

SVRendererGL::~SVRendererGL(){
    m_cur_program = 0;
}

SVRendererGLPtr SVRendererGL::share() {
    return std::dynamic_pointer_cast<SVRendererGL>(shareObject());
}

void SVRendererGL::init(s32 _w,s32 _h,s32 _version){
    SVRenderer::init(_w,_h);
    //构建一个主RT的业务
    //
    m_gl_version = _version;
    mApp->m_global_param.m_sv_width = _w;
    mApp->m_global_param.m_sv_height = _h;
    //创建主纹理
    SVRTargetPtr t_target = createTarget(E_TEX_MAIN,true,true);
    if(t_target) {
        mApp->getRenderMgr()->setMainRT(t_target);
    }
}

void SVRendererGL::init(s32 _w,s32 _h,s32 _version,bool _offline) {
    m_gl_version = _version;
    mApp->m_global_param.m_sv_width = _w;
    mApp->m_global_param.m_sv_height = _h;
    //创建主纹理
    SVRTargetPtr t_target = createTarget(E_TEX_MAIN,true,true);
    if(t_target) {
        mApp->getRenderMgr()->setMainRT(t_target);
    }
}

void SVRendererGL::resize(s32 _w,s32 _h) {
//    m_inWidth = _w;
//    m_inHeight = _h;
//    //重置size
//    mApp->m_global_param.m_sv_width = _w;
//    mApp->m_global_param.m_sv_height = _h;
//    //重新创建主纹理
//    SVTexturePtr t_tex = createSVTex(E_TEX_MAIN,_w,_h,GL_RGBA);
}

SVRTexPtr SVRendererGL::createResTexture() {
    return MakeSharedPtr<SVRTexGL>(mApp);
}

//shader
SVRShaderPtr SVRendererGL::createResShader() {
    return MakeSharedPtr<SVRShaderGL>(mApp);
}

//buf-vbo 等
SVRMeshResPtr SVRendererGL::createResBuf() {
    return MakeSharedPtr<SVRMeshGL>(mApp);
}

//fbo
SVRFboPtr SVRendererGL::createResFbo() {
    return MakeSharedPtr<SVRFboGL>(mApp);
}

SVRTargetPtr SVRendererGL::createTarget(SV_TEXIN _texid,bool _depth,bool _stencil) {
    SVRTargetPtr t_target = getTarget(_texid);
    if(t_target) {
        return t_target;
    }
    //创建主纹理
    SVTextureDsp t_tex_dsp;
    t_tex_dsp.m_image_type = SV_IMAGE_2D;
    t_tex_dsp.m_data_formate = SV_FORMAT_RGBA8;
    t_tex_dsp.m_width = mApp->m_global_param.m_sv_width;    //宽
    t_tex_dsp.m_height = mApp->m_global_param.m_sv_height;  //高
    t_tex_dsp.m_depth = 1;                                  //深度
    t_tex_dsp.m_minmap = false;         //是否开启mipmap
    t_tex_dsp.m_computeWrite = true;    //metal 是否可以
    t_tex_dsp.m_renderTarget = true;    //metal 是否是renderTarget
    SVTexturePtr t_main_tex = createInTexture(_texid,t_tex_dsp);
    //创建主target
    t_target = MakeSharedPtr<SVRTarget>(mApp,_texid);
    SVTargetDsp* t_dsp = t_target->getTargetDsp();
    t_dsp->m_color_texid[0] = _texid;
    t_dsp->m_target_num = 1;
    t_dsp->m_width = mApp->m_global_param.m_sv_width;
    t_dsp->m_height = mApp->m_global_param.m_sv_height;
    t_dsp->m_use_depth = true;
    t_dsp->m_use_stencil = true;
    //创建RT
    SVDispatch::dispatchTargetCreate(mApp,t_target);
    //增加target
    _addTarget(_texid,t_target);
    return t_target;
}

SVRTargetPtr SVRendererGL::createTarget(SV_TEXIN _texid,s32 _w,s32 _h,bool _depth,bool _stencil) {
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
