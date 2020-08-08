//
// SVRenderCmd.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderCmd.h"
#include "SVFboObject.h"
#include "SVRenderScene.h"
#include "SVRenderTexture.h"
#include "SVRenderer.h"
#include "SVRenderMesh.h"
#include "SVRShader.h"
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

//渲染命令批次
SVRCmdPass::SVRCmdPass() {
    m_fbo = nullptr;
    m_tex = nullptr;
}

SVRCmdPass::~SVRCmdPass(){
    m_fbo = nullptr;
    m_tex = nullptr;
    m_pMtl = nullptr;
    m_pMesh = nullptr;
}

void SVRCmdPass::setFbo(SVRenderTexturePtr _fbo) {
    m_fbo = _fbo;
}

void SVRCmdPass::setTexture(SVTexturePtr _tex) {
    m_tex = _tex;
}

void SVRCmdPass::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
//    if(m_fbo && m_tex ) {
//        m_fbo->setTexture(m_tex);
//        m_fbo->bind();
//        m_fbo->clear();
////        if(m_pMtl && m_pMesh) {
////            if (m_pMtl->submitMtl()) {
////                m_pMesh->render(m_pRenderer);
////                m_pMtl->recoverMtl();
////            }
////        }
//        m_fbo->unbind();
//    }
}

SVRCmdPassCollection::SVRCmdPassCollection(){
    m_fbo = nullptr;
    m_tex = nullptr;
    m_MtlArray.clear();
    m_MeshArray.clear();
}

SVRCmdPassCollection::~SVRCmdPassCollection(){
    m_fbo = nullptr;
    m_tex = nullptr;
    m_MtlArray.clear();
    m_MeshArray.clear();
}

void SVRCmdPassCollection::render(SVRendererPtr _renderer,SVRTargetPtr _target){
//    if(m_fbo && m_tex ) {
//        m_fbo->setTexture(m_tex);
//        m_fbo->bind();
//        m_fbo->clear();
////        for(int i=0;i<m_MtlArray.size();i++){
////            SVMtlCorePtr t_mtl = m_MtlArray.get(i);
////            SVRenderMeshPtr t_mesh = m_MeshArray.get(i);
////            if(t_mtl && t_mesh) {
////                if (t_mtl->submitMtl()) {
////                    t_mesh->render(m_pRenderer);
////                    t_mtl->recoverMtl();
////                }
////            }
////        }
//        m_fbo->unbind();
//    }
}

void SVRCmdPassCollection::setFbo(SVRenderTexturePtr _fbo){
    m_fbo = _fbo;
}

void SVRCmdPassCollection::setTexture(SVTexturePtr _tex){
    m_tex = _tex;
}

void SVRCmdPassCollection::addMtlMesh(SVMtlCorePtr _mtl , SVRenderMeshPtr _mesh){
    m_MtlArray.append(_mtl);
    m_MeshArray.append(_mesh);
}

//fbo 重置大小
SVRCmdFboResize::SVRCmdFboResize(SVRFboPtr _fbo,s32 _w,s32 _h) {
    m_fbo = _fbo;
    m_width = _w;
    m_height = _h;
}

SVRCmdFboResize::~SVRCmdFboResize(){
    m_fbo = nullptr;
}

void SVRCmdFboResize::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if (m_fbo) {
        m_fbo->resize(m_width,m_height);
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
