//
// SVFrameOutTex.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFrameOutTex.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVComData.h"
#include "../app/SVInst.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderObject.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderScene.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtlCore.h"
#include "../core/SVGeoGen.h"

using namespace sv;

SVFrameOutTex::SVFrameOutTex(SVInstPtr _app)
:SVFrameOutNode(_app){
    ntype = "SVFrameOutTex";
    m_pMtl = MakeSharedPtr<SVMtlCore>(mApp,"rgba");
    m_pMesh = mApp->getComData()->screenMesh();
    SVRendererPtr t_renderer = mApp->getRenderer();
    if( t_renderer ) {
//#if defined (SV_IOS)
//        SVTexturePtr t_tex = t_renderer->createSVTexIOS(E_TEX_OUTSTREAM,
//                                                     mApp->m_global_param.m_sv_width,
//                                                     mApp->m_global_param.m_sv_height,
//                                                     GL_RGBA); //GL_RGBA
//        m_fbo = MakeSharedPtr<SVRenderTexture>(mApp,t_tex,false,false);
//        mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//#else
//        SVTexturePtr t_tex = t_renderer->createSVTex(E_TEX_OUTSTREAM,
//                                                     mApp->m_global_param.m_sv_width,
//                                                     mApp->m_global_param.m_sv_height,
//                                                     GL_RGBA); //GL_RGBA
//        m_fbo = MakeSharedPtr<SVRenderTexture>(mApp,t_tex,false,false);
//        mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//#endif
    }
}

SVFrameOutTex::~SVFrameOutTex(){
    m_pMtl = nullptr;
    m_pMesh= nullptr;
}

void SVFrameOutTex::update(f32 _dt){
    SVNode::update(_dt);
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(m_pMtl){
        //m_pMtl->setModelMatrix(m_absolutMat);
        //m_pMtl->setTexture(0,E_TEX_MAIN);    //那第一张纹理
        m_pMtl->setBlendEnable(false);
        m_pMtl->update(_dt);
    }
}

s32 SVFrameOutTex::getTexId(){
    return 0;
}

void SVFrameOutTex::render(){
//    SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//    SVRendererPtr t_renderer = mApp->getRenderer();
//    SVTexturePtr t_out_tex = t_renderer->getSVTex(E_TEX_OUTSTREAM);
//    if (t_rs && false  == t_rs->isSuspend() ) {
//                SVRCmdPassPtr t_cmd = MakeSharedPtr<SVRCmdPass>();
//                t_cmd->mTag = "SVFrameOutTex";
//                t_cmd->setFbo(m_fbo);
//                t_cmd->setTexture(t_out_tex);
//                t_cmd->setMesh(mApp->getComData()->m_screenMesh);
//                t_cmd->setMaterial(m_pMtl);
//                t_rs->pushRenderCmd(RST_DATATRANS, t_cmd);
//    }
}
