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
#include "SVRBufferGL.h"
//
#include "../SVRenderMgr.h"
#include "../SVRTarget.h"
#include "../SVRenderTexture.h"
#include "../SVRenderMesh.h"
#include "../../app/SVInst.h"
#include "../../app/SVGlobalParam.h"
#include "../../base/SVCompileConfig.h"
#include "../../mtl/SVTexture.h"
#include "../../mtl/SVMtlCore.h"
#include "../../mtl/SVShader.h"

using namespace sv;

SVRendererGL::SVRendererGL(SVInstPtr _app)
:SVRenderer(_app)
,m_cur_program(0){
}

SVRendererGL::~SVRendererGL(){
    m_pRState = nullptr;
    m_pRenderTex = nullptr;
    m_cur_program = 0;
}

void SVRendererGL::init(s32 _w,s32 _h){
    SVRenderer::init(_w,_h);
    m_inWidth = _w;
    m_inHeight = _h;
    mApp->m_pGlobalParam->m_inner_width = _w;
    mApp->m_pGlobalParam->m_inner_height = _h;
    //
    SVRFboGLPtr t_fbo = std::dynamic_pointer_cast<SVRFboGL>( createResFbo() );
    if(t_fbo) {
        //t_fbo->init(_target,_targetTex);
    }
    //
    SVRTargetPtr t_target = MakeSharedPtr<SVRTarget>(mApp);
    //t_target->init();
    t_target->bindRes(t_fbo);
    //设置主RTarget
    mApp->getRenderMgr()->setMainRT(t_target);
}

void SVRendererGL::init(s32 _w,s32 _h,bool _offline) {
    
}

void SVRendererGL::resize(s32 _w,s32 _h) {
//    //
//    m_inWidth = _w;
//    m_inHeight = _h;
//    //重置size
//    mApp->m_pGlobalParam->m_inner_width = _w;
//    mApp->m_pGlobalParam->m_inner_height = _h;
//    //重新创建主纹理
//    SVTexturePtr t_tex = createSVTex(E_TEX_MAIN,_w,_h,GL_RGBA);
//    //重新创建主FBO
//    m_pRenderTex = MakeSharedPtr<SVRenderTexture>(mApp,
//                                                  t_tex,
//                                                  true,
//                                                  true);
//    mApp->getRenderMgr()->pushRCmdCreate(m_pRenderTex);
//    m_pRenderTex->setTexture(t_tex);
}

SVRTexPtr SVRendererGL::createResTexture() {
    return MakeSharedPtr<SVRTexGL>(mApp);
}

//shader
SVRShaderPtr SVRendererGL::createResShader() {
    return MakeSharedPtr<SVRShaderGL>(mApp);
}

//buf-vbo 等
SVRBufferPtr SVRendererGL::createResBuf() {
    return MakeSharedPtr<SVRBufferGL>(mApp);
}

//fbo
SVRFboPtr SVRendererGL::createResFbo() {
    return MakeSharedPtr<SVRFboGL>(mApp);
}

//处理技术
void SVRendererGL::processTech(SVRTechPtr _tech) {
    if(!_tech)
        return ;
}

//处理材质
void SVRendererGL::processMtl(SVMtlCorePtr _mtl) {
    if(!_mtl)
        return ;
    if( _mtl->m_shader && _mtl->m_shader->getResShader() ) {
        _mtl->m_shader->getResShader()->process( std::dynamic_pointer_cast<SVRendererGL>(shareObject()) );
    }
}

//处理mesh
void SVRendererGL::processMesh(SVRenderMeshPtr _mesh) {
    if(_mesh && _mesh->getResBuffer() ) {
        _mesh->getResBuffer()->process( std::dynamic_pointer_cast<SVRendererGL>(shareObject()) );
    }
}

//
void SVRendererGL::submitTex(u32 _channel,TexUnit& _unit){
    SVRenderStateGLPtr pState = std::static_pointer_cast<SVRenderStateGL>(m_pRState);
    //设置纹理通道
    s32 t_texGL = GL_TEXTURE0 + _channel;
    u32 texid = 0;
    SVTexturePtr t_aimTex = nullptr;
    glActiveTexture(t_texGL);
    if(_unit.m_texForm == E_TEX_END) {
        t_aimTex = _unit.m_pTex;
    }else {
        t_aimTex = m_svTex[_unit.m_texForm];
    }
    //
    if (!t_aimTex) {
        return ;
    }
    bool t_load = t_aimTex->getbLoad();
    if (!t_load){
        return ;
    }
    t_aimTex->commit();
    texid = 0;
    glBindTexture(GL_TEXTURE_2D, texid);
    SVString atexture = SVString::format("aTexture%d",_channel);
    s32 m_uni_tex = glGetUniformLocation(m_pRState->m_shaderID, atexture.c_str() );
    if (m_uni_tex>=0) {
        glUniform1i(m_uni_tex, _channel);
    }
    //
    if(_channel == 0) {
        s32 m_uni_clip = glGetUniformLocation(m_pRState->m_shaderID, "texcoordClip" );
        if (m_uni_clip>=0) {
            glUniform2fv(m_uni_clip, 1 , _unit.m_texcoordFlip);
        }
    }
    //最小过滤器
    u32 t_filter = GL_TEXTURE_MIN_FILTER;
    switch (_unit.m_min_filter) {
        case E_T_FILTER_NEAREST:
            t_filter = GL_NEAREST;
            break;
        case E_T_FILTER_LINEAR:
            t_filter = GL_LINEAR;
            break;
    }
    if( pState->m_texState[_channel].m_min_filter != t_filter) {
        pState->m_texState[_channel].m_min_filter = t_filter;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t_filter );
    }
    //最大过滤器
    t_filter = GL_TEXTURE_MAG_FILTER;
    switch (_unit.m_mag_filter) {
        case E_T_FILTER_NEAREST:
            t_filter = GL_NEAREST;
            break;
        case E_T_FILTER_LINEAR:
            t_filter = GL_LINEAR;
            break;
    }
    if( pState->m_texState[_channel].m_mag_filter != t_filter) {
        pState->m_texState[_channel].m_mag_filter = t_filter;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t_filter);
    }
#if defined SV_OSX
    //环绕
    u32 s_wrap = GL_CLAMP;
    switch (_unit.m_s_wrap) {
        case E_T_WRAP_CLAMP:
            s_wrap = GL_CLAMP;
            break;
        case E_T_WRAP_CLAMP_TO_EDAGE:
            s_wrap = GL_CLAMP_TO_EDGE;
            break;
        case E_T_WRAP_REPEAT:
            s_wrap = GL_REPEAT;
            break;
        case E_T_WRAP_MIRROR:
            s_wrap = GL_MIRRORED_REPEAT;
            break;
    }
    if( pState->m_texState[_channel].m_s_wrap != s_wrap) {
        pState->m_texState[_channel].m_s_wrap = s_wrap;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap );
    }
    //
    u32 t_wrap = GL_CLAMP;
    switch (_unit.m_t_wrap) {
        case E_T_WRAP_CLAMP:
            t_wrap = GL_CLAMP;
            break;
        case E_T_WRAP_CLAMP_TO_EDAGE:
            t_wrap = GL_CLAMP_TO_EDGE;
            break;
        case E_T_WRAP_REPEAT:
            t_wrap = GL_REPEAT;
            break;
        case E_T_WRAP_MIRROR:
            t_wrap = GL_MIRRORED_REPEAT;
            break;
    }
    if( pState->m_texState[_channel].m_t_wrap != t_wrap) {
        pState->m_texState[_channel].m_t_wrap = t_wrap;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap);
    }
#else
    //环绕
    u32 s_wrap = GL_CLAMP_TO_EDGE;
    switch (_unit.m_s_wrap) {
        case E_T_WRAP_CLAMP:
            s_wrap = GL_CLAMP_TO_EDGE;
            break;
        case E_T_WRAP_CLAMP_TO_EDAGE:
            s_wrap = GL_CLAMP_TO_EDGE;
            break;
        case E_T_WRAP_REPEAT:
            s_wrap = GL_REPEAT;
            break;
        case E_T_WRAP_MIRROR:
            s_wrap = GL_MIRRORED_REPEAT;
            break;
    }
    if( pState->m_texState[_channel].m_s_wrap != s_wrap) {
        pState->m_texState[_channel].m_s_wrap = s_wrap;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap );
    }
    //
    u32 t_wrap = GL_CLAMP_TO_EDGE;
    switch (_unit.m_t_wrap) {
        case E_T_WRAP_CLAMP:
            t_wrap = GL_CLAMP_TO_EDGE;
            break;
        case E_T_WRAP_CLAMP_TO_EDAGE:
            t_wrap = GL_CLAMP_TO_EDGE;
            break;
        case E_T_WRAP_REPEAT:
            t_wrap = GL_REPEAT;
            break;
        case E_T_WRAP_MIRROR:
            t_wrap = GL_MIRRORED_REPEAT;
            break;
    }
    if( pState->m_texState[_channel].m_t_wrap != t_wrap) {
        pState->m_texState[_channel].m_t_wrap = t_wrap;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap);
    }
#endif
 
}

//提交unifrom matrix
void SVRendererGL::submitUniformMatrix(cptr8 _name,f32* _data){
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniformMatrix4fv(m_uni_m, 1, GL_FALSE, _data);
    }
}

//提交unifrom matrix
void SVRendererGL::submitUniformMatrixArray(cptr8 _name,f32* _data,s32 _size){
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniformMatrix4fv(m_uni_m, _size, GL_FALSE, _data);
    }
}

//提交unifrom i1
void SVRendererGL::submitUniformi(cptr8 _name,s32 _data) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform1i(m_uni_m, _data);
    }
}
//提交unifrom i2
void SVRendererGL::submitUniformi2(cptr8 _name,s32 _data1,s32 _data2) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform2i(m_uni_m, _data1,_data2);
    }
}

//提交unifrom i3
void SVRendererGL::submitUniformi3(cptr8 _name,s32 _data1,s32 _data2,s32 _data3) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform3i(m_uni_m, _data1,_data2,_data3);
    }
}

//提交unifrom i4
void SVRendererGL::submitUniformi4(cptr8 _name,s32 _data1,s32 _data2,s32 _data3,s32 _data4) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform4i(m_uni_m, _data1,_data2,_data3,_data4);
    }
}

//提交unifrom f1
void SVRendererGL::submitUniformf(cptr8 _name,f32 _data){
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform1f(m_uni_m, _data);
    }
}

//提交unifrom f2
void SVRendererGL::submitUniformf2(cptr8 _name,f32 _data1,f32 _data2) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform2f(m_uni_m, _data1,_data2);
    }
}
//提交unifrom f3
void SVRendererGL::submitUniformf3(cptr8 _name,f32 _data1,f32 _data2,f32 _data3) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform3f(m_uni_m,_data1,_data2,_data3);
    }
}

//提交unifrom f4
void SVRendererGL::submitUniformf4(cptr8 _name,f32 _data1,f32 _data2,f32 _data3,f32 _data4) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform4f(m_uni_m,_data1,_data2,_data3,_data4);
    }
}

//提交unifrom s32 v1
void SVRendererGL::submitUniformi1v(cptr8 _name,s32* _data,s32 _size) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform1iv(m_uni_m, _size , _data);
    }
}

//提交unifrom s32 v2
void SVRendererGL::submitUniformi2v(cptr8 _name,s32* _data,s32 _size) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform2iv(m_uni_m, _size , _data);
    }
}

//提交unifrom s32 v3
void SVRendererGL::submitUniformi3v(cptr8 _name,s32* _data,s32 _size) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform3iv(m_uni_m, _size , _data);
    }
}

//提交unifrom s32 v4
void SVRendererGL::submitUniformi4v(cptr8 _name,s32* _data,s32 _size) {
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform4iv(m_uni_m, _size , _data);
    }
}

//提交unifrom f32 v1
void SVRendererGL::submitUniformf1v(cptr8 _name,f32* _data,s32 _size){
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform1fv(m_uni_m, _size , _data);
    }
}

//提交unifrom f32 v2
void SVRendererGL::submitUniformf2v(cptr8 _name,f32* _data,s32 _size){
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform2fv(m_uni_m, _size , _data);
    }
}

//提交unifrom f32 v3
void SVRendererGL::submitUniformf3v(cptr8 _name,f32* _data,s32 _size){
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform3fv(m_uni_m, _size , _data);
    }
}
//提交unifrom f32 v4
void SVRendererGL::submitUniformf4v(cptr8 _name,f32* _data,s32 _size){
    s32 m_uni_m = glGetUniformLocation(m_pRState->m_shaderID, _name);
    if(m_uni_m>=0) {
        glUniform4fv(m_uni_m, _size , _data);
    }
}

//提交融合参数
void SVRendererGL::submitBlend(SVBlendParam& _param){
    assert(_param.srcParam >= 0 && _param.srcParam < NUM_BLEND_FUNC && "SVRendererGL::submitBlend(): bad blend source function");
    assert(_param.dstParam >= 0 && _param.dstParam < NUM_BLEND_FUNC && "SVRendererGL::submitBlend(): bad blend destination function");
    static const GLuint blend_functions[] = {
        0,
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_COLOR,
        GL_ONE_MINUS_DST_COLOR,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA
    };
    if (_param.enable) {
        if (!glIsEnabled(GL_BLEND)) {
            glEnable(GL_BLEND);
        }
        glBlendFunc(blend_functions[_param.srcParam], blend_functions[_param.dstParam]);
    } else {
        if (glIsEnabled(GL_BLEND)) {
            glDisable(GL_BLEND);
        }
    }
}

//提交模板参数
void SVRendererGL::submitStencil(SVStencilParam& _param){
    if (_param.clear) {
        //glClearStencil(0);
        glClear(GL_STENCIL_BUFFER_BIT);
    }
    if (_param.enable) {
        if (!glIsEnabled(GL_STENCIL_TEST)) {
            glEnable(GL_STENCIL_TEST);
        }
        glStencilFunc(_param.passMethod, _param.refValue, _param.maskValue);
        glStencilOp(_param.sfail, _param.zfail, _param.zpass);
    } else {
        if (glIsEnabled(GL_STENCIL_TEST)) {
            glDisable(GL_STENCIL_TEST);
        }
    }
}

//提交深度参数
void SVRendererGL::submitDepth(SVDepthParam& _param){
    if (_param.clear) {
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearDepthf(1.0f);
    }
    if (_param.enable) {
        if (!glIsEnabled(GL_DEPTH_TEST)) {
            glEnable(GL_DEPTH_TEST);
        }
    } else {
        if (glIsEnabled(GL_DEPTH_TEST)) {
            glDisable(GL_DEPTH_TEST);
        }
    }
}

//提交zfighting
void SVRendererGL::submitZOff(SVZOffParam& _param) {
    if (_param.enable) {
        if (!glIsEnabled(GL_POLYGON_OFFSET_FILL)) {
            glEnable(GL_POLYGON_OFFSET_FILL);
        }
        glPolygonOffset(_param.m_factor,_param.m_unit);
    } else {
        if (glIsEnabled(GL_POLYGON_OFFSET_FILL)) {
            glPolygonOffset(0.0f,0.0f);
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
    }
}

//提交隐藏面参数
void SVRendererGL::submitCull(SVCullFaceParam& _param){
    if (_param.enable) {
        if (!glIsEnabled(GL_CULL_FACE)) {
            glEnable(GL_CULL_FACE);
        }
        glFrontFace(_param.frontFace);
        glCullFace(_param.cullFace);
    } else {
        if (glIsEnabled(GL_CULL_FACE)) {
            glDisable(GL_CULL_FACE);
        }
    }
}

//提交线宽
void SVRendererGL::submitLineWidth(f32 _width){
    glLineWidth(_width);
}

//提交点大小
void SVRendererGL::submitPointSize(f32 _size){
    
}

//绑定fbo
void SVRendererGL::svBindFrameBuffer(u32 _id) {
    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
    if( m_pRStateGL->m_fbo!=_id ) {
        m_pRStateGL->m_fbo = _id;
        glBindFramebuffer(GL_FRAMEBUFFER, m_pRStateGL->m_fbo);
    }
}

void SVRendererGL::svBindClearColor(u32 _id) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SVRendererGL::svBindColorBuffer(u32 _id) {
    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
    if( m_pRStateGL->m_colorBufferID!=_id ) {
        m_pRStateGL->m_colorBufferID = _id;
        glBindFramebuffer(GL_RENDERBUFFER, _id);
    }
}

//顶点缓存
void SVRendererGL::svBindVertexBuffer(u32 _id) {
    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
    if( m_pRStateGL->m_vertexBufID!=_id ) {
        m_pRStateGL->m_vertexBufID = _id;
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }
}

//索引缓存
void SVRendererGL::svBindIndexBuffer(u32 _id) {
    SVRenderStateGLPtr m_pRStateGL = std::dynamic_pointer_cast<SVRenderStateGL>(m_pRState);
    if( m_pRStateGL->m_indexBufID!=_id ) {
        m_pRStateGL->m_indexBufID = _id;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }
}

//视口
void SVRendererGL::svPushViewPort(u32 _x,u32 _y,u32 _w,u32 _h) {
    SVRenderer::svPushViewPort(_x,_y,_w,_h);
    glViewport(_x, _y, _w, _h);
}

void SVRendererGL::svPopViewPort() {
    m_vpStack.pop();
    if(m_vpStack.size()>0) {
        VPParam t_vp = m_vpStack.top();
        glViewport(t_vp.m_x, t_vp.m_y, t_vp.m_width, t_vp.m_height);
    }
}

//设置清理颜色
void SVRendererGL::svClearColor(f32 _r,f32 _g,f32 _b,f32 _a) {
    glClearColor(_r,_g,_b,_a);
}

//设置清理掩码
void SVRendererGL::svClear(s32 _mask) {
    glClear(_mask);
}

void SVRendererGL::svUpdateVertexFormate(VFTYPE _vf,s32 _count,s32 _mode) {
}

