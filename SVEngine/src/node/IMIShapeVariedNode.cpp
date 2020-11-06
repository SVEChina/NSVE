//
// IMIShapeVariedNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIShapeVariedNode.h"
#include "../basesys/IMIScene.h"
//#include "../app/IMIInst.h"
//#include "../event/IMIEventMgr.h"
//#include "../event/IMIEvent.h"
//#include "../event/IMIOpEvent.h"
//#include "../basesys/IMISceneMgr.h"
//#include "../basesys/IMIComData.h"
//#include "../rendercore/IMIRenderMgr.h"
//
//#include "../rendercore/IMIRenderMesh.h"
//#include "../rendercore/IMIRenderCmd.h"
//
//#include "../rendercore/IMIRenderer.h"
//#include "../core/IMIGeoGen.h"
//#include "../core/IMIPass.h"
//#include "../app/IMIGlobalMgr.h"
//#include "../mtl/IMIMtlFaceShape.h"
//#include "../mtl/IMIMtlShapeVaried.h"
//#include "../mtl/IMITexMgr.h"
//#include "../detect/IMIDetectMgr.h"
//#include "../detect/IMIDetectST.h"

using namespace imi;

IMIShapeVariedNode::IMIShapeVariedNode(IMIInstPtr _app)
:IMINode(_app){
    ntype = "IMIFaceShapeVariedNode";
//    m_pMtl = MakeSharedPtr<IMIMtlFaceShapeVaried>(mApp);
//    m_pMesh =  mApp->getComData()->m_screenMesh;
}

IMIShapeVariedNode::~IMIShapeVariedNode(){
    
}

void IMIShapeVariedNode::addPass(IMIPassPtr _pass) {
//    if(_pass){
//        m_passPool.append(_pass);
//    }
}

void IMIShapeVariedNode::clearPass() {
    m_passPool.clear();
}

void IMIShapeVariedNode::init(){
//    IMIRendererPtr t_renderer = mApp->getRenderer();
//    if(!t_renderer)
//        return ;
//    IMITexturePtr t_tex = mApp->getTexMgr()->createUnctrlTexture(mApp->m_global_param.sv_width, mApp->m_global_param.sv_height,GL_RGBA, GL_RGBA);
//    IMITexturePtr teximg = mApp->getTexMgr()->getTexture("svres/filterimg/mask", true);
//    m_fbo = MakeSharedPtr<IMIRenderTexture>(mApp,
//                                           t_tex,
//                                           false,
//                                           false);
//    mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//    IMIMtlCorePtr t_mtl = MakeSharedPtr<IMIMtlCore>(mApp,"screen");
//    t_mtl->setTexcoordFlip(1.0f, 1.0f);
//
//    IMIPassPtr t_pass1 = MakeSharedPtr<IMIPass>();
//    t_pass1->setMtl(m_pMtl);
//    m_pMtl->setTexcoordFlip(1.0f, 1.0f);
//    t_pass1->setMesh(m_pMesh);
//    t_pass1->setInTex(0, t_renderer->getIMITex(E_TEX_MAIN));
//    t_pass1->setInTex(1, teximg);
//    t_pass1->setOutTex(t_tex);
//    addPass(t_pass1);
//
//    IMIPassPtr t_pass2 = MakeSharedPtr<IMIPass>();
//    t_pass2->setMtl(t_mtl);
//    t_pass2->setInTex(0, t_tex);
//    t_pass2->setMesh(mApp->getComData()->screenMesh();
//    t_pass2->setOutTex(t_renderer->getIMITex(E_TEX_MAIN));
//    addPass(t_pass2);
}

void IMIShapeVariedNode::destroy(){
//    exit();
//    clearPass();
}

void IMIShapeVariedNode::update(f32 _dt){
//    IMINode::update(_dt);
//    for(s32 i=0;i<m_passPool.size();i++){
//        if(m_passPool[i]->m_pMtl){
//            m_passPool[i]->m_pMtl->update(_dt);
//        }
//    }
}

void IMIShapeVariedNode::render(){
//    IMIPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
//    if( t_person && t_person->getExist() ){
//        t_person->getFaceData();
//        IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        if (t_rs && false  == t_rs->isSuspend() ) {
//            for(s32 i=0;i<m_passPool.size();i++){
//                if(m_passPool[i]->m_pMtl){
//                    IMIRCmdPassPtr t_cmd = MakeSharedPtr<IMIRCmdPass>();
//                    t_cmd->mTag = "IMIFaceShapeNode";
//                    t_cmd->setFbo(m_fbo);
//                    t_cmd->setTexture(m_passPool[i]->m_outTex);
//                    t_cmd->setMesh(m_passPool[i]->m_pMesh);
//                    t_cmd->setMaterial(m_passPool[i]->m_pMtl->clone());
//                    t_rs->pushRenderCmd(RST_FACEMORPH, t_cmd);
//                }
//            }
//        }
//    }
}
