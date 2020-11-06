//
// IMIFaceShapeNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIFaceShapeNode.h"

#include "../basesys/IMIScene.h"
#include "../basesys/IMIComData.h"

#include "../mtl/IMIMtlFaceShape.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMISurface.h"

#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../event/IMIEventMgr.h"
#include "../event/IMIEvent.h"
#include "../event/IMIOpEvent.h"
#include "../basesys/IMISceneMgr.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../rendercore/IMIRenderer.h"
#include "../core/IMIGeoGen.h"
#include "../core/IMIPass.h"
#include "../app/IMIGlobalMgr.h"
#include "../detect/IMIDetectMgr.h"
#include "../detect/IMIDetectST.h"

using namespace imi;

IMIFaceShapeNode::IMIFaceShapeNode(IMIInstPtr _app)
:IMINode(_app){
    ntype = "IMIFaceShapeNode";
//    m_pMtl = MakeSharedPtr<IMIMtlFaceShape>(mApp);
//    m_pMesh = IMIGeoGen::createRectMesh(mApp,1.0, 1.0, 36, 64);
}

IMIFaceShapeNode::~IMIFaceShapeNode(){
}

void IMIFaceShapeNode::init(){
//    startListen();
//    IMIRendererPtr t_renderer = mApp->getRenderer();
//    if(!t_renderer)
//        return ;
//    IMITexturePtr t_tex = mApp->getTexMgr()->createUnctrlTexture(mApp->m_global_param.sv_width, mApp->m_global_param.sv_height,GL_RGBA, GL_RGBA);
//    m_fbo = MakeSharedPtr<IMIRenderTexture>(mApp,
//                                           t_tex,
//                                           false,
//                                           false);
//    IMITexturePtr t_texmain = t_renderer->getIMITex(E_TEX_MAIN);
//    mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//    IMIMtlCorePtr t_mtl = MakeSharedPtr<IMIMtlCore>(mApp,"screen");
//    t_mtl->setTexcoordFlip(1.0f, 1.0f);
//    
//    IMIPassPtr t_pass1 = MakeSharedPtr<IMIPass>();
//    t_pass1->setMtl(m_pMtl);
//    m_pMtl->setTexcoordFlip(1.0f, -1.0f);
//    t_pass1->setMesh(m_pMesh);
//    t_pass1->setInTex(0, t_texmain);
//    t_pass1->setOutTex(t_tex);
//    addPass(t_pass1);
//    
//    IMIPassPtr t_pass2 = MakeSharedPtr<IMIPass>();
//    t_pass2->setMtl(t_mtl);
//    t_pass2->setInTex(0, t_tex);
//    t_pass2->setMesh(mApp->getComData()->m_screenMesh);
//    t_pass2->setOutTex(t_texmain);
//    addPass(t_pass2);
}

void IMIFaceShapeNode::addPass(IMIPassPtr _pass) {
    if(_pass){
        m_passPool.append(_pass);
    }
}

void IMIFaceShapeNode::clearPass() {
    m_passPool.destroy();
}

void IMIFaceShapeNode::destroy(){
//    stopListen();
//    clearPass();
}

void IMIFaceShapeNode::update(f32 _dt){
    IMINode::update(_dt);
}

void IMIFaceShapeNode::render(){
    IMINode::render();
    
}

bool IMIFaceShapeNode::procEvent(IMIEventPtr _event){
    IMIFaceShapeEventPtr pEvent = DYN_TO_SHAREPTR(IMIFaceShapeEvent,_event);//dynamic_cast<IMIFaceShapeEvent*>(_event);
    if (pEvent != NULL){
        m_pMtl->setEyeLarge(pEvent->m_eyeSmooth/100.0, pEvent->m_eyeSmooth/100.0);
        m_pMtl->setChinSlim(1.0-pEvent->m_faceSmooth/1000.0);
        m_pMtl->setFaceSlim(1.0-pEvent->m_faceSmooth/1000.0);
        m_pMtl->setChinUpSlim(1.0-pEvent->m_faceSmooth/1000.0);
        m_pMtl->setChinMiddleSlim(1.0-pEvent->m_faceSmooth/1000.0);
    }
    return true;
}
