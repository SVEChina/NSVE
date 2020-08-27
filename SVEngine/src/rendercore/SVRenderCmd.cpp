//
// SVRenderCmd.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderCmd.h"
#include "SVRenderer.h"
#include "SVRenderMesh.h"
#include "SVRShader.h"
#include "SVRFbo.h"
#include "SVRTarget.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVShader.h"
#include "../mtl/SVSurface.h"

#include <sys/time.h>

using namespace sv;

//
SVRenderCmd::SVRenderCmd() {
    mTag = "SVRenderCmd";
}

SVRenderCmd::~SVRenderCmd() {
}

void SVRenderCmd::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
}

//普通渲染指令
SVRCmdNor::SVRCmdNor() {
    m_pMtl  = nullptr;
    m_pMesh = nullptr;
    m_pSurface = nullptr;
}

SVRCmdNor::~SVRCmdNor() {
    m_pMtl  = nullptr;
    m_pMesh = nullptr;
    m_pSurface = nullptr;
}

void SVRCmdNor::setMesh(SVRenderMeshPtr _mesh){
    m_pMesh = _mesh;
}

void SVRCmdNor::setMaterial(SVMtlCorePtr _mtl){
    m_pMtl = _mtl;
}

void SVRCmdNor::setSurface(SVSurfacePtr _surface) {
    m_pSurface = _surface;
}

void SVRCmdNor::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if ( _renderer && _target && m_pMtl && m_pMesh ) {
        bool t_ret = false;
        t_ret = _renderer->processMesh(m_pMesh);
        if(!t_ret){
            return ;
        }
        //激活材质
        t_ret =_renderer->processMtl(m_pMtl,m_pSurface);
        if(!t_ret){
            return ;
        }
        _renderer->drawMesh(m_pMesh);
    }
}

//自动拿辅助纹理
//渲染命令批次
SVRCmdPass::SVRCmdPass() {
    m_aim = E_TEX_END;
    m_aim_help = E_TEX_END;
}

SVRCmdPass::~SVRCmdPass(){
}

void SVRCmdPass::setTarget(SVINTEX _aim) {
    m_aim = _aim;
}

void SVRCmdPass::setHelpTarget(SVINTEX _aim) {
    m_aim_help = _aim;
}

void SVRCmdPass::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    //获取辅助纹理
    SVRTargetPtr t_target = _renderer->getTarget(m_aim_help);
    if(t_target && t_target->getResFbo()) {
        //绑定
        t_target->getResFbo()->bind(_renderer);
        //执行命令
        SVRCmdNor::render(_renderer, t_target);
        //解绑定
        t_target->getResFbo()->unbind(_renderer);
        //交换纹理....
        _renderer->swapInTexture(m_aim,m_aim_help);
    }
}

//fbo 重置大小
SVRCmdTargetResize::SVRCmdTargetResize(SVRFboPtr _fbo,s32 _w,s32 _h) {
    m_fbo = _fbo;
    m_width = _w;
    m_height = _h;
}

SVRCmdTargetResize::~SVRCmdTargetResize(){
    m_fbo = nullptr;
}

void SVRCmdTargetResize::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if (m_fbo) {
        m_fbo->resize(m_width,m_height,_renderer);
    }
}

//
SVRCmdTransGPU::SVRCmdTransGPU(SVTransPtr _trans):SVRenderCmd() {
    mTag = "SVRCmdTransGPU";
    m_trans = _trans;
}

SVRCmdTransGPU::~SVRCmdTransGPU() {
    m_trans = nullptr;
}

void SVRCmdTransGPU::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
//    if (m_trans) {
//        m_trans->update(0.0f);
//        m_trans->render();
//    }
}

//
SVRCmdAdapt::SVRCmdAdapt()
:m_winWidth(720)
,m_winHeight(1280){
}

SVRCmdAdapt::~SVRCmdAdapt(){
}

void SVRCmdAdapt::setWinSize(s32 _w,s32 _h){
    m_winWidth = _w;
    m_winHeight = _h;
}

void SVRCmdAdapt::render(SVRendererPtr _renderer,SVRTargetPtr _target){
 //   glViewport( 0, 0,m_winWidth,m_winHeight);
//    m_pRenderer->svClearColor(m_color_r,m_color_g,m_color_b,m_color_a);
//    m_pRenderer->svClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    SVRenderCmd::render(_renderer,_target);
}
