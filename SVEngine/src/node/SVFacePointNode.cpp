//
// SVFacePointNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#include "SVFacePointNode.h"

#include "../basesys/SVScene.h"
#include "../basesys/SVComData.h"

#include "../mtl/SVTexMgr.h"
#include "../mtl/SVMtlLib.h"
#include "../mtl/SVSurface.h"

#include "../app/SVInst.h"
#include "../app/SVDispatch.h"

#include "../detect/SVDetectMgr.h"

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
    m_pMtl = mApp->getMtlLib()->getMtl("debug2d");
    if(m_pMtl) {
        m_pMtl->reloadShader();
    }
    m_pMesh = mApp->getComData()->faceMesh(SV_E_FACEMESH_TUNE);
    if (m_pMesh) {
        m_pMesh->setDrawMethod(E_DRAW_POINTS);
    }
}

SVFacePointNode::~SVFacePointNode(){
    m_pMtl = nullptr;
    m_pMesh = nullptr;
}

void SVFacePointNode::update(f32 _dt){
    SVNode::update(_dt);
    
}


void SVFacePointNode::render(){
    SVNode::render();
    if (m_pMtl && m_pMesh) {
        s32 t_width = mApp->m_global_param.sv_width*0.5;
        s32 t_height = mApp->m_global_param.sv_height*0.5;
        SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
        FVec2 t_scale = FVec2(1.0f/t_width, 1.0f/t_height);
        t_surface->setParam("u_scale", t_scale);
        FVec2 t_off = FVec2(0.0f, 0.0f);
        t_surface->setParam("u_off", t_off);
        FVec3 t_color = FVec3(1.0f,0.0f,0.0f);
        t_surface->setParam("u_color", t_color);
        //
        SVPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
        if( t_person && t_person->getExist() ){
            s32 t_ptNum = 0;
            f32 *t_keyPt = t_person->getFaceData(t_ptNum, SV_E_FACEDATA_TUNE);
            //顶点描述
            SVVertStreamDspPtr t_vert_dsp= m_pMesh->getStreamDsp();
            t_vert_dsp->setBufType(E_BFT_DYNAMIC_DRAW);
            t_vert_dsp->setVertCnt(t_ptNum);
            t_vert_dsp->setSigleStreamData(E_VF_V2, t_keyPt, t_ptNum*2*sizeof(f32));
        }
        SVDispatch::dispatchMeshDraw(mApp,
                                     m_pMesh,
                                     m_pMtl,
                                     t_surface,
                                     E_RSM_SOLID);
    }
    
}
