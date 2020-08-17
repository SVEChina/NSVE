//
// SVRendererGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRendererGL.h"
#include "SVRenderStateGL.h"
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

void SVRendererGL::init(s32 _w,s32 _h){
    SVRenderer::init(_w,_h);
    mApp->m_global_param.m_sv_width = _w;
    mApp->m_global_param.m_sv_height = _h;
    //创建主纹理
    SVRTargetPtr t_target = createTarget(E_TEX_MAIN,true,true);
    if(t_target) {
        t_target->setRenderPath();
        mApp->getRenderMgr()->setMainRT(t_target);
    }
}

void SVRendererGL::init(s32 _w,s32 _h,bool _offline) {
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

SVRTargetPtr SVRendererGL::createTarget(SVINTEX _texid,bool _depth,bool _stencil) {
    SVRTargetPtr t_target = getTarget(_texid);
    if(t_target) {
        return t_target;
    }
    //创建主纹理
    SVTextureDsp t_tex_dsp;
    t_tex_dsp.m_imgtype = SV_IMAGE_2D;
    t_tex_dsp.m_dataFormate = SV_FORMAT_RGBA8;
    t_tex_dsp.m_width = mApp->m_global_param.m_sv_width;    //宽
    t_tex_dsp.m_height = mApp->m_global_param.m_sv_height;  //高
    t_tex_dsp.m_depth = 1;                                  //深度
    t_tex_dsp.m_minmap = false;         //是否开启mipmap
    t_tex_dsp.m_computeWrite = true;    //metal 是否可以
    t_tex_dsp.m_renderTarget = true;    //metal 是否是renderTarget
    SVTexturePtr t_main_tex = mApp->getTexMgr()->createInTexture(_texid,t_tex_dsp);
    //创建主target
    t_target = MakeSharedPtr<SVRTarget>(mApp);
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

SVRTargetPtr SVRendererGL::createTarget(SVINTEX _texid,s32 _w,s32 _h,bool _depth,bool _stencil) {
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
void SVRendererGL::drawScreen(SVINTEX _texid) {
}

//
////
//void SVRendererGL::submitTex(u32 _channel,TexUnit& _unit){
//    SVRenderStateGLPtr pState = std::static_pointer_cast<SVRenderStateGL>(m_pRState);
//    //设置纹理通道
//    s32 t_texGL = GL_TEXTURE0 + _channel;
//    u32 texid = 0;
//    SVTexturePtr t_aimTex = nullptr;
//    glActiveTexture(t_texGL);
//    if(_unit.m_texForm == E_TEX_END) {
//        t_aimTex = _unit.m_pTex;
//    }else {
//    }
//    //
//    if (!t_aimTex) {
//        return ;
//    }
//    bool t_load = t_aimTex->getbLoad();
//    if (!t_load){
//        return ;
//    }
//    //渲染器主动提交纹理
//    t_aimTex->lockData();
//    if( t_aimTex->getTextureData() ) {
//        //主动提交纹理
//        t_aimTex->setTexData(nullptr);
//    }
//    t_aimTex->unlockData();
//    //
//    texid = 0;
//    glBindTexture(GL_TEXTURE_2D, texid);
//    SVString atexture = SVString::format("aTexture%d",_channel);
//    s32 m_uni_tex = glGetUniformLocation(m_pRState->m_shaderID, atexture.c_str() );
//    if (m_uni_tex>=0) {
//        glUniform1i(m_uni_tex, _channel);
//    }
//    //最小过滤器
//    u32 t_filter = GL_TEXTURE_MIN_FILTER;
//    switch (_unit.m_min_filter) {
//        case E_T_FILTER_NEAREST:
//            t_filter = GL_NEAREST;
//            break;
//        case E_T_FILTER_LINEAR:
//            t_filter = GL_LINEAR;
//            break;
//    }
//    if( pState->m_texState[_channel].m_min_filter != t_filter) {
//        pState->m_texState[_channel].m_min_filter = t_filter;
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t_filter );
//    }
//    //最大过滤器
//    t_filter = GL_TEXTURE_MAG_FILTER;
//    switch (_unit.m_mag_filter) {
//        case E_T_FILTER_NEAREST:
//            t_filter = GL_NEAREST;
//            break;
//        case E_T_FILTER_LINEAR:
//            t_filter = GL_LINEAR;
//            break;
//    }
//    if( pState->m_texState[_channel].m_mag_filter != t_filter) {
//        pState->m_texState[_channel].m_mag_filter = t_filter;
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t_filter);
//    }
//#if defined SV_OSX
//    //环绕
//    u32 s_wrap = GL_CLAMP;
//    switch (_unit.m_s_wrap) {
//        case E_T_WRAP_CLAMP:
//            s_wrap = GL_CLAMP;
//            break;
//        case E_T_WRAP_CLAMP_TO_EDAGE:
//            s_wrap = GL_CLAMP_TO_EDGE;
//            break;
//        case E_T_WRAP_REPEAT:
//            s_wrap = GL_REPEAT;
//            break;
//        case E_T_WRAP_MIRROR:
//            s_wrap = GL_MIRRORED_REPEAT;
//            break;
//    }
//    if( pState->m_texState[_channel].m_s_wrap != s_wrap) {
//        pState->m_texState[_channel].m_s_wrap = s_wrap;
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap );
//    }
//    //
//    u32 t_wrap = GL_CLAMP;
//    switch (_unit.m_t_wrap) {
//        case E_T_WRAP_CLAMP:
//            t_wrap = GL_CLAMP;
//            break;
//        case E_T_WRAP_CLAMP_TO_EDAGE:
//            t_wrap = GL_CLAMP_TO_EDGE;
//            break;
//        case E_T_WRAP_REPEAT:
//            t_wrap = GL_REPEAT;
//            break;
//        case E_T_WRAP_MIRROR:
//            t_wrap = GL_MIRRORED_REPEAT;
//            break;
//    }
//    if( pState->m_texState[_channel].m_t_wrap != t_wrap) {
//        pState->m_texState[_channel].m_t_wrap = t_wrap;
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap);
//    }
//#else
//    //环绕
//    u32 s_wrap = GL_CLAMP_TO_EDGE;
//    switch (_unit.m_s_wrap) {
//        case E_T_WRAP_CLAMP:
//            s_wrap = GL_CLAMP_TO_EDGE;
//            break;
//        case E_T_WRAP_CLAMP_TO_EDAGE:
//            s_wrap = GL_CLAMP_TO_EDGE;
//            break;
//        case E_T_WRAP_REPEAT:
//            s_wrap = GL_REPEAT;
//            break;
//        case E_T_WRAP_MIRROR:
//            s_wrap = GL_MIRRORED_REPEAT;
//            break;
//    }
//    if( pState->m_texState[_channel].m_s_wrap != s_wrap) {
//        pState->m_texState[_channel].m_s_wrap = s_wrap;
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap );
//    }
//    //
//    u32 t_wrap = GL_CLAMP_TO_EDGE;
//    switch (_unit.m_t_wrap) {
//        case E_T_WRAP_CLAMP:
//            t_wrap = GL_CLAMP_TO_EDGE;
//            break;
//        case E_T_WRAP_CLAMP_TO_EDAGE:
//            t_wrap = GL_CLAMP_TO_EDGE;
//            break;
//        case E_T_WRAP_REPEAT:
//            t_wrap = GL_REPEAT;
//            break;
//        case E_T_WRAP_MIRROR:
//            t_wrap = GL_MIRRORED_REPEAT;
//            break;
//    }
//    if( pState->m_texState[_channel].m_t_wrap != t_wrap) {
//        pState->m_texState[_channel].m_t_wrap = t_wrap;
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap);
//    }
//#endif
//}

////提交融合参数
//void SVRendererGL::submitBlend(SVBlendParam& _param){
////    assert(_param.srcParam >= 0 && _param.srcParam < NUM_BLEND_FUNC && "SVRendererGL::submitBlend(): bad blend source function");
////    assert(_param.dstParam >= 0 && _param.dstParam < NUM_BLEND_FUNC && "SVRendererGL::submitBlend(): bad blend destination function");
////    static const GLuint blend_functions[] = {
////        0,
////        GL_ZERO,
////        GL_ONE,
////        GL_SRC_COLOR,
////        GL_ONE_MINUS_SRC_COLOR,
////        GL_SRC_ALPHA,
////        GL_ONE_MINUS_SRC_ALPHA,
////        GL_DST_COLOR,
////        GL_ONE_MINUS_DST_COLOR,
////        GL_DST_ALPHA,
////        GL_ONE_MINUS_DST_ALPHA
////    };
////    if (_param.enable) {
////        if (!glIsEnabled(GL_BLEND)) {
////            glEnable(GL_BLEND);
////        }
////        glBlendFunc(blend_functions[_param.srcParam], blend_functions[_param.dstParam]);
////    } else {
////        if (glIsEnabled(GL_BLEND)) {
////            glDisable(GL_BLEND);
////        }
////    }
//}

////提交模板参数
//void SVRendererGL::submitStencil(SVStencilParam& _param){
//    if (_param.clear) {
//        //glClearStencil(0);
//        glClear(GL_STENCIL_BUFFER_BIT);
//    }
//    if (_param.enable) {
//        if (!glIsEnabled(GL_STENCIL_TEST)) {
//            glEnable(GL_STENCIL_TEST);
//        }
//        glStencilFunc(_param.passMethod, _param.refValue, _param.maskValue);
//        glStencilOp(_param.sfail, _param.zfail, _param.zpass);
//    } else {
//        if (glIsEnabled(GL_STENCIL_TEST)) {
//            glDisable(GL_STENCIL_TEST);
//        }
//    }
//}

////提交深度参数
//void SVRendererGL::submitDepth(SVDepthParam& _param){
//    if (_param.clear) {
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glClearDepthf(1.0f);
//    }
//    if (_param.enable) {
//        if (!glIsEnabled(GL_DEPTH_TEST)) {
//            glEnable(GL_DEPTH_TEST);
//        }
//    } else {
//        if (glIsEnabled(GL_DEPTH_TEST)) {
//            glDisable(GL_DEPTH_TEST);
//        }
//    }
//}

////提交zfighting
//void SVRendererGL::submitZOff(SVZOffParam& _param) {
//    if (_param.enable) {
//        if (!glIsEnabled(GL_POLYGON_OFFSET_FILL)) {
//            glEnable(GL_POLYGON_OFFSET_FILL);
//        }
//        glPolygonOffset(_param.m_factor,_param.m_unit);
//    } else {
//        if (glIsEnabled(GL_POLYGON_OFFSET_FILL)) {
//            glPolygonOffset(0.0f,0.0f);
//            glDisable(GL_POLYGON_OFFSET_FILL);
//        }
//    }
//}

////提交隐藏面参数
//void SVRendererGL::submitCull(SVCullFaceParam& _param){
//    if (_param.enable) {
//        if (!glIsEnabled(GL_CULL_FACE)) {
//            glEnable(GL_CULL_FACE);
//        }
//        glFrontFace(_param.frontFace);
//        glCullFace(_param.cullFace);
//    } else {
//        if (glIsEnabled(GL_CULL_FACE)) {
//            glDisable(GL_CULL_FACE);
//        }
//    }
//}
//
////提交线宽
//void SVRendererGL::submitLineWidth(f32 _width){
//    glLineWidth(_width);
//}
////绑定fbo
//void SVRendererGL::svBindFrameBuffer(u32 _id) {
//    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
//    if( m_pRStateGL->m_fbo!=_id ) {
//        m_pRStateGL->m_fbo = _id;
//        glBindFramebuffer(GL_FRAMEBUFFER, m_pRStateGL->m_fbo);
//    }
//}
//
//void SVRendererGL::svBindClearColor(u32 _id) {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//}
//
//void SVRendererGL::svBindColorBuffer(u32 _id) {
//    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
//    if( m_pRStateGL->m_colorBufferID!=_id ) {
//        m_pRStateGL->m_colorBufferID = _id;
//        glBindFramebuffer(GL_RENDERBUFFER, _id);
//    }
//}
//
////顶点缓存
//void SVRendererGL::svBindVertexBuffer(u32 _id) {
//    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
//    if( m_pRStateGL->m_vertexBufID!=_id ) {
//        m_pRStateGL->m_vertexBufID = _id;
//        glBindBuffer(GL_ARRAY_BUFFER, _id);
//    }
//}
//
////索引缓存
//void SVRendererGL::svBindIndexBuffer(u32 _id) {
//    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
//    if( m_pRStateGL->m_indexBufID!=_id ) {
//        m_pRStateGL->m_indexBufID = _id;
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
//    }
//}
//
////视口
//void SVRendererGL::svPushViewPort(u32 _x,u32 _y,u32 _w,u32 _h) {
//    SVRenderer::svPushViewPort(_x,_y,_w,_h);
//    glViewport(_x, _y, _w, _h);
//}
//
//void SVRendererGL::svPopViewPort() {
//    m_vpStack.pop();
//    if(m_vpStack.size()>0) {
//        VPParam t_vp = m_vpStack.top();
//        glViewport(t_vp.m_x, t_vp.m_y, t_vp.m_width, t_vp.m_height);
//    }
//}
