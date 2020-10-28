//
// SVFacePointNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#include "SVFacePointNode.h"

#include "../basesys/SVScene.h"
#include "../basesys/SVComData.h"

#include "../mtl/SVMtlFaceShape.h"
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
    
}

SVFacePointNode::~SVFacePointNode(){
    
}

void SVFacePointNode::update(f32 _dt){
    SVNode::update(_dt);
    
}


void SVFacePointNode::render(){
    SVNode::render();
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
    SVMtlCorePtr _mtl = mApp->getMtlLib()->getMtl("debug2d");
    if(_mtl) {
        _mtl->reloadShader();
    }
    SVRenderMeshPtr t_mesh = mApp->getComData()->faceMesh();
    SVPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
    if( t_person && t_person->getExist() ){
        f32 *t_keyPt = t_person->getFaceData();
        //顶点描述
        SVVertStreamDspPtr t_vert_dsp= t_mesh->getStreamDsp();
        t_vert_dsp->setBufType(E_BFT_DYNAMIC_DRAW);
        t_vert_dsp->setVertCnt(106);
        t_vert_dsp->setSigleStreamData(E_VF_V2, t_keyPt, 106*2*sizeof(f32));
    }
    
    mApp->getComData()->faceMesh()->setDrawMethod(E_DRAW_POINTS);
    SVDispatch::dispatchMeshDraw(mApp,
                                 t_mesh,
                                 _mtl,
                                 t_surface,
                                 E_RSM_SOLID);
}
