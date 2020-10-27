//
// SVFacePointNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#include "SVFacePointNode.h"
#include "SVScene.h"
#include "../app/SVInst.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderMesh.h"
#include "../mtl/SVMtlCore.h"
#include "../core/SVGeoGen.h"
#include "../detect/SVDetectMgr.h"
#include "../detect/SVDetectST.h"
using namespace sv;

SVFacePointNode::SVFacePointNode(SVInstPtr _app)
:SVNode(_app){
    ntype = "SVFacePointNode";
    
}

SVFacePointNode::~SVFacePointNode(){
    
}

void SVFacePointNode::update(f32 _dt){
    SVNode::update(_dt);
    
}


void SVFacePointNode::render(){
//    SVMtlCorePtr _mtl = mApp->getMtlLib()->getMtl("debug2d");
//    if(_mtl) {
//        _mtl->reloadShader();
//    }
//    //
//    mApp->getComData()->faceMesh()->setDrawMethod(E_DRAW_POINTS);
//    SVDispatch::dispatchMeshDraw(mApp,
//                                 mApp->getComData()->faceMesh(),
//                                 _mtl,
//                                 t_surface,
//                                 E_RSM_SOLID);
}
