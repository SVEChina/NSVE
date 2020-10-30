//
// SVFaceTuneNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFaceTuneNode.h"
#include "SVScene.h"

#include "../app/SVDispatch.h"
#include "../basesys/SVComData.h"
#include "../core/SVPass.h"

#include "../mtl/SVMtlLib.h"
#include "../mtl/SVSurface.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVTexMgr.h"

#include "../detect/SVDetectMgr.h"
#include "../detect/SVDetectST.h"

#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRTargetMgr.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderMgr.h"
using namespace sv;

SVFaceTuneNode::SVFaceTuneNode(SVInstPtr _app)
: SVNode(_app) {
    ntype = "SVFaceTuneNode";
    m_name = "SVFaceTuneNode";
    m_tuneMtl = mApp->getMtlLib()->getMtl("normal2d");
    if(m_tuneMtl) {
        m_tuneMtl->reloadShader();
    }
    m_tuneMesh = mApp->getComData()->faceMesh(SV_E_FACEMESH_TUNE);
    if (m_tuneMesh) {
        m_tuneMesh->setDrawMethod(E_DRAW_POINTS);
    }
    m_tuneSurface = MakeSharedPtr<SVSurface>();
    m_faceTuneTarget = mApp->getTargetMgr()->getTarget(E_TEX_HELP0);
    if(!m_faceTuneTarget) {
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        m_faceTuneTarget = mApp->getTargetMgr()->createTarget(E_TEX_HELP0, t_w, t_h, false, false);
        m_faceTuneTarget->pushStreamQuene(E_RSM_SOLID);
        mApp->getRenderMgr()->addRTarget(m_faceTuneTarget,true);
    }
}

SVFaceTuneNode::~SVFaceTuneNode() {
    m_tuneMtl = nullptr;
    m_tuneMesh = nullptr;
    m_tuneSurface = nullptr;
}

void SVFaceTuneNode::update(f32 dt){
    SVTexturePtr _tex = mApp->getTexMgr()->getInTexture(E_TEX_MAIN);
    m_tuneSurface->setTexture(1, 0, _tex);
    FVec2 t_invert = FVec2(1.0f,1.0f);
    m_tuneSurface->setParam("u_invert", t_invert);
    //
    SVPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
    if( t_person && t_person->getExist() && m_tuneMesh){
        //顶点描述
        SVVertStreamDspPtr t_vert_dsp= m_tuneMesh->getStreamDsp();
        t_vert_dsp->setBufType(E_BFT_DYNAMIC_DRAW);
        s32 t_ptNum = 0;
        f32 *t_vertexPts = t_person->getFaceData(t_ptNum, SV_E_FACEDATA_TUNE);
        t_vert_dsp->setVertCnt(t_ptNum);
        t_vert_dsp->setSigleStreamData(E_VF_V2, t_vertexPts, t_ptNum*2*sizeof(f32));
        f32 *t_keyPts = t_person->getFaceData(t_ptNum, SV_E_FACEDATA_ORIGINAL);
        f32 t_texcoordPts[t_ptNum*2];
        memcpy(t_texcoordPts, t_keyPts, t_ptNum*2*sizeof(f32));
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        for (s32 i = 0; i<t_ptNum; i++) {
            t_texcoordPts[2*i] = t_texcoordPts[2*i]/(t_w*1.0);
            t_texcoordPts[2*i+1] = (t_h-t_texcoordPts[2*i+1])/(t_h*1.0);
        }
        t_vert_dsp->setSigleStreamData(E_VF_T0, t_texcoordPts, t_ptNum*2*sizeof(f32));
    }
}

void SVFaceTuneNode::render(){
    if(m_faceTuneTarget && m_tuneMesh && m_tuneMtl) {
        SVDispatch::dispatchMeshDraw(mApp,
                                     m_tuneMesh,
                                     m_tuneMtl,
                                     m_tuneSurface,
                                     m_faceTuneTarget,
                                     E_RSM_SOLID,
                                     "SVDrawFaceTune");
//        SVRCmdPassPtr t_pass1 = MakeSharedPtr<SVRCmdPass>();
//        t_pass1->mTag = "SVFaceTuneNode";
//        t_pass1->setSwapTarget(E_TEX_MAIN);
//        t_pass1->setUseTarget(E_TEX_HELP0);
//        t_pass1->setMesh(m_tuneMesh);
//        t_pass1->setSurface(m_tuneSurface);
//        t_pass1->setMaterial(m_tuneMtl);
//        t_target->pushCommand(t_pass1, E_RSM_SOLID);
    }
}

//序列化接口
void SVFaceTuneNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue) {
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    _toJsonData(_allocator, locationObj);
    //    if (m_mtlFace2D && m_mtlFace2D->getMaskTexture()) {
    //        SVTexturePtr maskTexture = m_mtlFace2D->getMaskTexture();
    //        SVString texName = maskTexture->getname();
    //        s32 pos = texName.rfind('/');
    //        m_texName = SVString::substr(texName.c_str(), pos+1);
    //        locationObj.AddMember("texture", RAPIDJSON_NAMESPACE::StringRef(m_texName.c_str()), _allocator);
    //    }
    _objValue.AddMember("SVFaceTuneNode", locationObj, _allocator);
}

void SVFaceTuneNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
//    _fromJsonData(item);
//    if (item.HasMember("texture") && item["texture"].IsString()) {
//        SVString t_textureName = item["texture"].GetString();
//        SVString t_texturePath = m_rootPath + t_textureName;
//        SVTexturePtr tex = mApp->getTexMgr()->getTextureSync(t_texturePath.c_str(), true);
//        m_maskMtl->setTexture(0, tex);
//    }
}
