//
// SVIOSInstreamNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVIOSInstreamNode.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"
#include "../app/SVInst.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVComData.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTextureIOS.h"
#include "../mtl/SVMtlCore.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../core/SVGeoGen.h"

using namespace sv;

SVIOSInstreamNode::SVIOSInstreamNode(SVInstPtr _app)
:SVNode(_app){
    ntype = "SVIOSInstreamNode";
    m_tt = E_TEX_INSTREAM;
    m_pMtl = MakeSharedPtr<SVMtlCore>(mApp,"screennorbgra");
}

SVIOSInstreamNode::~SVIOSInstreamNode() {
    destroy();
    m_pMtl = nullptr;
}

void SVIOSInstreamNode::init(SV_TEXIN _tt){
    m_tt = _tt;
}

void SVIOSInstreamNode::destroy(){
}

void SVIOSInstreamNode::update(f32 dt) {
    SVNode::update(dt);
//    if(m_pRenderObj && m_pMtl){
//        m_pMtl->setTexcoordFlip(1.0f, -1.0f);
//        m_pMtl->setTexture(0, m_tt);    //那第一张纹理
//        m_pMtl->setModelMatrix(m_absolutMat);
//        m_pMtl->update(dt);
//        m_pRenderObj->setMtl(m_pMtl);
//        m_pRenderObj->setMesh(mApp->getComData()->m_screenMesh);
//    }
}

void SVIOSInstreamNode::render() {
//    SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//    if (m_pRenderObj ) {
//        m_pRenderObj->pushCmd(t_rs, RST_SKY, "SVIOSInstreamNode");
//    }
}








