//
// IMIRenderCmd.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRenderCmd.h"
#include "IMIRenderer.h"
#include "IMIRenderMesh.h"
#include "IMIRShader.h"
#include "IMIRFbo.h"
#include "IMIRTarget.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIShader.h"
#include "../mtl/IMISurface.h"

#include <sys/time.h>

using namespace imi;

//
IMIRenderCmd::IMIRenderCmd() {
    mTag = "IMIRenderCmd";
}

IMIRenderCmd::~IMIRenderCmd() {
}

bool IMIRenderCmd::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    return false;
}

//普通渲染指令
IMIRCmdNor::IMIRCmdNor() {
    m_pMtl  = nullptr;
    m_pMesh = nullptr;
    m_pSurface = nullptr;
}

IMIRCmdNor::~IMIRCmdNor() {
    m_pMtl  = nullptr;
    m_pMesh = nullptr;
    m_pSurface = nullptr;
}

void IMIRCmdNor::setMesh(IMIRenderMeshPtr _mesh){
    m_pMesh = _mesh;
}

void IMIRCmdNor::setMaterial(IMIMtlCorePtr _mtl){
    m_pMtl = _mtl;
}

void IMIRCmdNor::setSurface(IMISurfacePtr _surface) {
    m_pSurface = _surface;
}

bool IMIRCmdNor::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    if ( _renderer && _target && m_pMtl && m_pMesh ) {
        bool t_ret = false;
        if(mTag == "IMIMesh3d" ) {
            int a = 0;
        }
        //激活材质
        t_ret =_renderer->processMtl(m_pMtl,m_pSurface);
        if(!t_ret){
            return false;
        }
        //处理MESH
        t_ret = _renderer->processMesh(m_pMesh);
        if(!t_ret){
            return false;
        }
        _renderer->drawMesh(m_pMesh);
        return true;
    }
    return false;
}

//自动拿辅助纹理
//渲染命令批次
IMIRCmdPass::IMIRCmdPass() {
    m_aim_swap = E_TEX_END;
    m_aim_use = E_TEX_END;
}

IMIRCmdPass::~IMIRCmdPass(){
}

//设置目标target
void IMIRCmdPass::setSwapTarget(IMI_TEXIN _aim) {
    m_aim_swap = _aim;
}

//设置辅助target
void IMIRCmdPass::setUseTarget(IMI_TEXIN _aim) {
    m_aim_use = _aim;
}

bool IMIRCmdPass::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    bool t_flag = false;
    //获取辅助target
    IMIRTargetPtr t_target = _renderer->getTarget(m_aim_use);
    if(t_target && t_target->getResFbo()) {
        //绑定
        t_target->getResFbo()->bind(_renderer);
        //执行命令
        t_flag = IMIRCmdNor::render(_renderer, t_target);
        //解绑定
        t_target->getResFbo()->unbind(_renderer);
        //交换纹理....
        if( m_aim_swap != E_TEX_END && t_flag) {
            _renderer->swapInTexture(m_aim_swap,m_aim_use);
        }
    }
    return t_flag;
}

//fbo 重置大小
IMIRCmdTargetResize::IMIRCmdTargetResize(IMIRFboPtr _fbo,s32 _w,s32 _h) {
    m_fbo = _fbo;
    m_width = _w;
    m_height = _h;
}

IMIRCmdTargetResize::~IMIRCmdTargetResize(){
    m_fbo = nullptr;
}

bool IMIRCmdTargetResize::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    if (m_fbo) {
        m_fbo->resize(m_width,m_height,_renderer);
    }
    return true;
}

//
IMIRCmdTransGPU::IMIRCmdTransGPU(IMITransPtr _trans):IMIRenderCmd() {
    mTag = "IMIRCmdTransGPU";
    m_trans = _trans;
}

IMIRCmdTransGPU::~IMIRCmdTransGPU() {
    m_trans = nullptr;
}

bool IMIRCmdTransGPU::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
//    if (m_trans) {
//        m_trans->update(0.0f);
//        m_trans->render();
//    }
    return true;
}

//
IMIRCmdAdapt::IMIRCmdAdapt()
:m_winWidth(720)
,m_winHeight(1280){
}

IMIRCmdAdapt::~IMIRCmdAdapt(){
}

void IMIRCmdAdapt::setWinSize(s32 _w,s32 _h){
    m_winWidth = _w;
    m_winHeight = _h;
}

bool IMIRCmdAdapt::render(IMIRendererPtr _renderer,IMIRTargetPtr _target){
 //   glViewport( 0, 0,m_winWidth,m_winHeight);
//    m_pRenderer->svClearColor(m_color_r,m_color_g,m_color_b,m_color_a);
//    m_pRenderer->svClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    IMIRenderCmd::render(_renderer,_target);
    return true;
}
