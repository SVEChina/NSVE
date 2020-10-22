//
// SVFaceShapeNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#include "SVFaceShapeNode.h"

#include "../basesys/SVScene.h"
#include "../basesys/SVComData.h"

#include "../mtl/SVMtlFaceShape.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVMtlLib.h"
#include "../mtl/SVSurface.h"

#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../event/SVEventMgr.h"
#include "../event/SVEvent.h"
#include "../event/SVOpEvent.h"
#include "../basesys/SVSceneMgr.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderer.h"
#include "../core/SVGeoGen.h"
#include "../core/SVPass.h"
#include "../app/SVGlobalMgr.h"
#include "../detect/SVDetectMgr.h"
#include "../detect/SVDetectST.h"

using namespace sv;

SVFaceShapeNode::SVFaceShapeNode(SVInstPtr _app)
:SVNode(_app){
    ntype = "SVFaceShapeNode";
//    m_pMtl = MakeSharedPtr<SVMtlFaceShape>(mApp);
//    m_pMesh = SVGeoGen::createRectMesh(mApp,1.0, 1.0, 36, 64);
}

SVFaceShapeNode::~SVFaceShapeNode(){
}

void SVFaceShapeNode::init(){
//    startListen();
//    SVRendererPtr t_renderer = mApp->getRenderer();
//    if(!t_renderer)
//        return ;
//    SVTexturePtr t_tex = mApp->getTexMgr()->createUnctrlTexture(mApp->m_global_param.sv_width, mApp->m_global_param.sv_height,GL_RGBA, GL_RGBA);
//    m_fbo = MakeSharedPtr<SVRenderTexture>(mApp,
//                                           t_tex,
//                                           false,
//                                           false);
//    SVTexturePtr t_texmain = t_renderer->getSVTex(E_TEX_MAIN);
//    mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//    SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlCore>(mApp,"screen");
//    t_mtl->setTexcoordFlip(1.0f, 1.0f);
//    
//    SVPassPtr t_pass1 = MakeSharedPtr<SVPass>();
//    t_pass1->setMtl(m_pMtl);
//    m_pMtl->setTexcoordFlip(1.0f, -1.0f);
//    t_pass1->setMesh(m_pMesh);
//    t_pass1->setInTex(0, t_texmain);
//    t_pass1->setOutTex(t_tex);
//    addPass(t_pass1);
//    
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>();
//    t_pass2->setMtl(t_mtl);
//    t_pass2->setInTex(0, t_tex);
//    t_pass2->setMesh(mApp->getComData()->m_screenMesh);
//    t_pass2->setOutTex(t_texmain);
//    addPass(t_pass2);
}

void SVFaceShapeNode::addPass(SVPassPtr _pass) {
    if(_pass){
        m_passPool.append(_pass);
    }
}

void SVFaceShapeNode::clearPass() {
    m_passPool.destroy();
}

void SVFaceShapeNode::destroy(){
//    stopListen();
//    clearPass();
}

void SVFaceShapeNode::update(f32 _dt){
    SVNode::update(_dt);
}

void SVFaceShapeNode::render(){
    SVNode::render();
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
    FVec2 t_scale = FVec2(1.0f/700.0f,1.0f/1004.0f);
    t_surface->setParam("u_scale", t_scale);
    FVec2 t_off = FVec2(-350.0f,-502.0f);
    t_surface->setParam("u_off", t_off);
    FVec3 t_color = FVec3(0.0f,1.0f,0.0f);
    t_surface->setParam("u_color", t_color);
    SVMtlCorePtr _mtl = mApp->getMtlLib()->getMtl("debug2d");
    if(_mtl) {
        _mtl->reloadShader();
    }
    //
    mApp->getComData()->faceMesh()->setDrawMethod(E_DRAW_POINTS);
    SVDispatch::dispatchMeshDraw(mApp,
                                 mApp->getComData()->faceMesh(),
                                 _mtl,
                                 t_surface,
                                 E_RSM_SOLID);
}

bool SVFaceShapeNode::procEvent(SVEventPtr _event){
    SVFaceShapeEventPtr pEvent = DYN_TO_SHAREPTR(SVFaceShapeEvent,_event);//dynamic_cast<SVFaceShapeEvent*>(_event);
    if (pEvent != NULL){
        m_pMtl->setEyeLarge(pEvent->m_eyeSmooth/100.0, pEvent->m_eyeSmooth/100.0);
        m_pMtl->setChinSlim(1.0-pEvent->m_faceSmooth/1000.0);
        m_pMtl->setFaceSlim(1.0-pEvent->m_faceSmooth/1000.0);
        m_pMtl->setChinUpSlim(1.0-pEvent->m_faceSmooth/1000.0);
        m_pMtl->setChinMiddleSlim(1.0-pEvent->m_faceSmooth/1000.0);
    }
    return true;
}
