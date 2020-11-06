//
// IMIFacePointNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIFacePointNode.h"

#include "../basesys/IMIScene.h"
#include "../basesys/IMIComData.h"

#include "../mtl/IMITexMgr.h"
#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMISurface.h"

#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"

#include "../detect/IMIDetectMgr.h"

#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMIConfig.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../mtl/IMIMtlCore.h"
#include "../core/IMIGeoGen.h"
#include "../detect/IMIDetectMgr.h"
#include "../detect/IMIDetectST.h"

using namespace imi;

IMIFacePointNode::IMIFacePointNode(IMIInstPtr _app)
:IMINode(_app){
    ntype = "IMIFacePointNode";
    m_pMtl = mApp->getMtlLib()->getMtl("debug2d");
    if(m_pMtl) {
        m_pMtl->reloadShader();
    }
    m_pMesh = mApp->getComData()->faceMesh(IMI_E_FACEMESH_TUNE);
    if (m_pMesh) {
        m_pMesh->setDrawMethod(E_DRAW_POINTS);
    }
}

IMIFacePointNode::~IMIFacePointNode(){
    m_pMtl = nullptr;
    m_pMesh = nullptr;
}

void IMIFacePointNode::update(f32 _dt){
    IMINode::update(_dt);
    
}


void IMIFacePointNode::render(){
    IMINode::render();
    if (m_pMtl && m_pMesh) {
        s32 t_width = mApp->m_global_param.sv_width*0.5;
        s32 t_height = mApp->m_global_param.sv_height*0.5;
        IMISurfacePtr t_surface = MakeSharedPtr<IMISurface>();
        FVec2 t_scale = FVec2(1.0f/t_width, 1.0f/t_height);
        t_surface->setParam("u_scale", t_scale);
        FVec2 t_off = FVec2(0.0f, 0.0f);
        t_surface->setParam("u_off", t_off);
        FVec3 t_color = FVec3(1.0f,0.0f,0.0f);
        t_surface->setParam("u_color", t_color);
        //
        IMIPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
        if( t_person && t_person->getExist() ){
            s32 t_ptNum = 0;
            f32 *t_keyPt = t_person->getFaceData(t_ptNum, IMI_E_FACEDATA_TUNED, true);
            //顶点描述
            IMIVertStreamDspPtr t_vert_dsp= m_pMesh->getStreamDsp();
            t_vert_dsp->setBufType(E_BFT_DYNAMIC_DRAW);
            t_vert_dsp->setVertCnt(t_ptNum);
            t_vert_dsp->setSigleStreamData(E_VF_V2, t_keyPt, t_ptNum*2*sizeof(f32));
        }
        IMIDispatch::dispatchMeshDraw(mApp,
                                     m_pMesh,
                                     m_pMtl,
                                     t_surface,
                                     E_RSM_SOLID);
    }
    
}
