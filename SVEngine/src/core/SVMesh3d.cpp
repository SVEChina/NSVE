//
// SVMesh.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMesh3d.h"
#include "../app/SVInst.h"
#include "../base/SVDataSwap.h"
#include "../work/SVTdCore.h"
#include "../mtl/SVMtlGLTF.h"
#include "../mtl/SVMtlLib.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

SVMesh3d::SVMesh3d(SVInstPtr _app)
:SVGBaseEx(_app){
    m_rendermesh = nullptr;
}

SVMesh3d::~SVMesh3d() {
    m_rendermesh = nullptr;
}

SVRenderMeshPtr SVMesh3d::getRenderMesh(){
    return m_rendermesh;
}

void SVMesh3d::setName(cptr8 _name) {
    m_name = _name;
}

cptr8 SVMesh3d::getName(){
    return m_name.c_str();
}

void SVMesh3d::setBox(SVBoundBox& _box) {
    m_box = _box;
}

SVBoundBox SVMesh3d::getBox() {
    return m_box;
}

//数据操作
void SVMesh3d::setData(SVDataSwapPtr _data,VFTYPE _vtf,s32 _count,s32 _seqMode) {
//    //m_rendermesh = MakeSharedPtr<SVRenderMesh>(mApp);
//    m_pRenderMesh->setVertexType(_vtf);
//    //m_pRenderMesh->setSeqMode(_seqMode);
//    m_pRenderMesh->setDrawVertNum(_count);
//    m_pRenderMesh->setVertexData(_data);
//    m_pRenderMesh->setDrawMethod(E_DRAW_LINE_LOOP);
//    //m_pRenderMesh->createMesh();
}


void SVMesh3d::update(f32 _dt,FMat4& _mat) {
//    if(m_pMtl) {
//        //m_pMtl->setModelMatrix(_mat.get());
//        m_pMtl->setBlendEnable(true);
//        m_pMtl->setDepthEnable(true);
//        m_pMtl->update(_dt);
//    }
}

void SVMesh3d::render() {
//    //先渲染自己
//    SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//    if(m_pRenderMesh && t_rs) {
//        SVRCmdNorPtr t_cmd = MakeSharedPtr<SVRCmdNor>();
//        if(m_pMtl) {
//            //t_cmd->setMaterial(m_pMtl->clone());
//        }else{
////            //走默认材质
////            SVMtlCorePtr t_mtl_default = SVMtlLib::getSkinMtl(mApp);
////            t_cmd->setMaterial(t_mtl_default);
//        }
//        t_cmd->setMesh(m_pRenderMesh);
//        t_cmd->setRenderer(mApp->getRenderer());
//        t_cmd->mTag = "SVMesh";
//        t_rs->pushRenderCmd(RST_MASK2D, t_cmd);
//    }
}

////
//void SVMesh3d::createShadow() {
////    //先渲染自己
////    SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
////    if(m_pRenderMesh && t_rs) {
////        SVRCmdNorPtr t_cmd = MakeSharedPtr<SVRCmdNor>();
////        if(m_pMtl) {
////            SVMtlCorePtr t_mtl= MakeSharedPtr<SVMtlCore>(mApp,"depth3d");
//                //t_mtl->setParam("mmat", m_mat_unit);
////            t_mtl->setModelMatrix(m_pMtl->m_LogicParamMatrix.m_mat_model);
////            t_mtl->setBlendEnable(true);
////            t_mtl->setDepthEnable(true);
////            t_cmd->setMaterial(t_mtl);
////        }else{
////            //走默认材质
////            SVMtlCorePtr t_mtl_default = SVMtlLib::getSkinMtl(mApp);
////            t_cmd->setMaterial(t_mtl_default);
////        }
////        t_cmd->setMesh(m_pRenderMesh);
////        t_cmd->setRenderer(mApp->getRenderer());
////        t_cmd->mTag = "SVMeshShadow";
////        t_rs->pushRenderCmd(RST_SHADOW, t_cmd);
////    }
//}

