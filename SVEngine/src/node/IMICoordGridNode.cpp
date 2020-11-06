//
// IMICoordGridNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMICoordGridNode.h"
#include "../core/IMIGeoGen.h"
#include "../mtl/IMITexMgr.h"
#include "../basesys/IMIScene.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

#define COORD_SIZE 64*100

IMICoordGridNode::IMICoordGridNode(IMIInstPtr _app)
:IMINode(_app)
,m_unit(50.0f){
    m_rsType = RST_LASTFILTER;
    m_pMeshX = IMIGeoGen::createNetGrid(mApp,COORD_SIZE,0);
    m_pMeshY = IMIGeoGen::createNetGrid(mApp,COORD_SIZE,1);
    m_pMeshZ = IMIGeoGen::createNetGrid(mApp,COORD_SIZE,2);
    //m_gridTex = mApp->getTexMgr()->getTexture("svres/grid6.png",true);
    m_gridTex = nullptr;
}

IMICoordGridNode::~IMICoordGridNode(){
    m_pMeshX = nullptr;
    m_pMeshY = nullptr;
    m_pMeshZ = nullptr;
    m_gridTex = nullptr;
}

void IMICoordGridNode::update(f32 dt){
    IMINode::update(dt);
//    _refreshUnit();
//    //
//    if(!m_gridTex){
//       m_gridTex = mApp->getTexMgr()->getTexture("svres/grid2.png",true);
//    }
//    IMIMtlCoordPtr t_mtl_coord = MakeSharedPtr<IMIMtlCoord>(mApp);
//    t_mtl_coord->update(dt * 0.001f);
//    t_mtl_coord->setTexture(0, m_gridTex);
//    t_mtl_coord->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_REPEAT);
//    t_mtl_coord->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_REPEAT);
//    t_mtl_coord->setModelMatrix(m_absolutMat);
//    t_mtl_coord->setTexcoordFlip(1.0, -1.0f);
//    t_mtl_coord->setDepthEnable(true);
//    t_mtl_coord->setZOffEnable(true);
//    t_mtl_coord->setZOffParam(-1.0f, -1.0f);
//    t_mtl_coord->setBlendEnable(true);
//    t_mtl_coord->setBlendState(MTL_BLEND_SRC_ALPHA,MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//    m_pRenderObj->setMtl(t_mtl_coord);
}

void IMICoordGridNode::render(){
//    if ( m_visible ){
//        IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        if (m_pRenderObj) {
//            m_pRenderObj->setMesh(m_pMeshX);
//            m_pRenderObj->pushCmd(t_rs, m_rsType, "IMICoordGridNode");
//            m_pRenderObj->setMesh(m_pMeshY);
//            m_pRenderObj->pushCmd(t_rs, m_rsType, "IMICoordGridNode");
//            m_pRenderObj->setMesh(m_pMeshZ);
//            m_pRenderObj->pushCmd(t_rs, m_rsType, "IMICoordGridNode");
     //   }
//        //
//        FMat4 m_mat_unit = FMat4_identity;
//        IMIMtlGeo3dPtr t_mtl = MakeSharedPtr<IMIMtlGeo3d>(mApp);
//        t_mtl->setColor(1.0f, 1.0f, 1.0f, 1.0f);
//        t_mtl->setModelMatrix( m_mat_unit.get() );
//        t_mtl->setLineSize(5);
//        //
//        IMIRenderObjInst::pushLineCmd(t_rs,
//                                     m_rsType,
//                                     FVec3(-50.0f*m_unit,0.0f,0.0f),
//                                     FVec3(50.0f*m_unit,0.0f,0.0f),
//                                     t_mtl,
//                                     "sv_coord_axis");
//        //
//        IMIRenderObjInst::pushLineCmd(t_rs,
//                                     m_rsType,
//                                     FVec3(0.0f,0.0f,-50.0f*m_unit),
//                                     FVec3(0.0f,0.0f,50.0f*m_unit),
//                                     t_mtl,
//                                     "sv_coord_axis");
 //   }
    IMINode::render();
}

f32 IMICoordGridNode::getUnit() {
    return m_unit;
}

void IMICoordGridNode::_refreshUnit() {
}
