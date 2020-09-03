//
// SV3DBox.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SV3DBox.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"
#include "../app/SVInst.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderMgr.h"
#include "../core/SVGeoGen.h"

using namespace sv;

SV3DBox::SV3DBox(SVInstPtr _app)
:SVNode(_app) {
    ntype = "SV3DBox";
    m_size.set(100.0f, 100.0f, 100.0f);
    m_aabbBox.clear();
    m_aabbBox.expand(m_size*-0.5f);
    m_aabbBox.expand(m_size*0.5f);
    m_pMesh = SVGeoGen::genAABB(mApp,m_aabbBox);
    m_drawBox = true;
}

SV3DBox::~SV3DBox() {
    m_pMesh = nullptr;
}

void SV3DBox::setSize(FVec3 _size) {
    if(m_size!=_size) {
        m_size = _size;
    }
}

void SV3DBox::update(f32 dt) {
    SVNode::update(dt);
//    if (m_pRenderObj && m_pMesh) {
//        //材质独立化
//        if(m_pMtl){
//            m_pMtl->update(dt);
//            m_pMtl->setDepthEnable(true);
//            m_pMtl->setModelMatrix(m_absolutMat);
//            m_pMtl->setTexcoordFlip(1.0, 1.0);
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(m_pMtl);
//        }else{
//            m_mtl_box->setColor(m_color.r, m_color.g, m_color.b, m_color.a);
//            m_mtl_box->update(dt * 0.001f);
//            m_mtl_box->setModelMatrix(m_absolutMat);
//            m_mtl_box->setTexcoordFlip(1.0, -1.0f);
//            m_mtl_box->setDepthEnable(true);
//            m_mtl_box->setBlendEnable(true);
//            m_mtl_box->setBlendState(MTL_BLEND_SRC_ALPHA,MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(m_mtl_box);
//        }
//    }
}

void SV3DBox::render() {
//    SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
////    if (m_pRenderObj && t_rs) {
////        m_pRenderObj->pushCmd(t_rs, m_rsType, "SV3DBox");
////    }
    SVNode::render();
}










