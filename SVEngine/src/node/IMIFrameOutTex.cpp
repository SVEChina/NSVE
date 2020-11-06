//
// IMIFrameOutTex.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFrameOutTex.h"
#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMIComData.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../rendercore/IMIRenderer.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIMtlCore.h"
#include "../core/IMIGeoGen.h"

using namespace imi;

IMIFrameOutTex::IMIFrameOutTex(IMIInstPtr _app)
:IMIFrameOutNode(_app){
    ntype = "IMIFrameOutTex";
    m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp,"rgba");
    m_pMesh = mApp->getComData()->screenMesh();
    IMIRendererPtr t_renderer = mApp->getRenderer();
    if( t_renderer ) {
//#if defined (IMI_IOS)
//        IMITexturePtr t_tex = t_renderer->createIMITexIOS(E_TEX_OUTSTREAM,
//                                                     mApp->m_global_param.sv_width,
//                                                     mApp->m_global_param.sv_height,
//                                                     GL_RGBA); //GL_RGBA
//        m_fbo = MakeSharedPtr<IMIRenderTexture>(mApp,t_tex,false,false);
//        mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//#else
//        IMITexturePtr t_tex = t_renderer->createIMITex(E_TEX_OUTSTREAM,
//                                                     mApp->m_global_param.sv_width,
//                                                     mApp->m_global_param.sv_height,
//                                                     GL_RGBA); //GL_RGBA
//        m_fbo = MakeSharedPtr<IMIRenderTexture>(mApp,t_tex,false,false);
//        mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//#endif
    }
}

IMIFrameOutTex::~IMIFrameOutTex(){
    m_pMtl = nullptr;
    m_pMesh= nullptr;
}

void IMIFrameOutTex::update(f32 _dt){
    IMINode::update(_dt);
    IMIRendererPtr t_renderer = mApp->getRenderer();
    if(m_pMtl){
        //m_pMtl->setModelMatrix(m_absolutMat);
        //m_pMtl->setTexture(0,E_TEX_MAIN);    //那第一张纹理
        m_pMtl->setBlendEnable(false);
        m_pMtl->update(_dt);
    }
}

s32 IMIFrameOutTex::getTexId(){
    return 0;
}

void IMIFrameOutTex::render(){
//    IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//    IMIRendererPtr t_renderer = mApp->getRenderer();
//    IMITexturePtr t_out_tex = t_renderer->getIMITex(E_TEX_OUTSTREAM);
//    if (t_rs && false  == t_rs->isSuspend() ) {
//                IMIRCmdPassPtr t_cmd = MakeSharedPtr<IMIRCmdPass>();
//                t_cmd->mTag = "IMIFrameOutTex";
//                t_cmd->setFbo(m_fbo);
//                t_cmd->setTexture(t_out_tex);
//                t_cmd->setMesh(mApp->getComData()->m_screenMesh);
//                t_cmd->setMaterial(m_pMtl);
//                t_rs->pushRenderCmd(RST_DATATRANS, t_cmd);
//    }
}
