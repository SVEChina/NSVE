//
// IMIBGRAInstreamNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//


#include "IMIBGRAInstreamNode.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMICameraNode.h"
#include "../mtl/IMIMtlCore.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../core/IMIGeoGen.h"
#include "../basesys/IMIConfig.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMITexMgr.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../basesys/IMIComData.h"

using namespace imi;

//
IMIBGRAInstreamNode::IMIBGRAInstreamNode(IMIInstPtr _app)
:IMINode(_app) {
    IMIBGRAInstreamNode(_app,100,100);
}

IMIBGRAInstreamNode::IMIBGRAInstreamNode(IMIInstPtr _app,f32 _w,f32 _h)
:IMINode(_app) {
    ntype = "IMIBGRAInstreamNode";
    m_rsType = RST_SOLID_3D;
    m_canSelect = false;
    m_pMesh = nullptr;
    setSpriteSize(_w,_h);
}

IMIBGRAInstreamNode::~IMIBGRAInstreamNode() {
    m_pMesh = nullptr;
    m_pTex = nullptr;
}

//
void IMIBGRAInstreamNode::setSpriteSize(f32 _w,f32 _h) {
    m_width = _w;
    m_height = _h;
    m_pMesh = IMIGeoGen::genRect(mApp, m_width, m_height,m_aabbBox);
}

void IMIBGRAInstreamNode::setTexture(IMITexturePtr _tex){
    m_pTex = _tex;
}

void IMIBGRAInstreamNode::update(f32 dt) {
    IMINode::update(dt);
//    if (m_pRenderObj && m_pMesh) {
//        if(m_pMtl){
//            m_pMtl->setBlendEnable(true);
//            m_pMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//            m_pMtl->setModelMatrix(m_absolutMat);
//            m_pMtl->setTexcoordFlip(1.0f, -1.0f);
//            m_pMtl->update(dt);
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(m_pMtl);
//        }else{
//            //创建新的材质
//            IMIMtlCorePtr t_mtl = MakeSharedPtr<IMIMtlCore>(mApp, "normal2dBGRA");
//            t_mtl->setBlendEnable(false);
//            t_mtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//            t_mtl->setModelMatrix(m_absolutMat);
//            t_mtl->setTexcoordFlip(1.0f, -1.0f);
//            t_mtl->setTexture(0,m_pTex);
//            t_mtl->setBlendEnable(true);
//            t_mtl->setBlendState(MTL_BLEND_SRC_ALPHA,MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//            t_mtl->update(dt);
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(t_mtl);
//        }
//    }
}

void IMIBGRAInstreamNode::render() {
    if (m_visible ){
//        IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        if (m_pRenderObj) {
//            m_pRenderObj->pushCmd(t_rs, m_rsType, "IMIBGRAInstreamNode");
//        }
    }
    IMINode::render();
}
