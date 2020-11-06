//
// IMIFaceTuneNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFaceTuneNode.h"
#include "IMIScene.h"

#include "../app/IMIDispatch.h"
#include "../basesys/IMIComData.h"
#include "../basesys/IMICameraMgr.h"
#include "../core/IMIPass.h"

#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMISurface.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMITexMgr.h"

#include "../detect/IMIDetectMgr.h"
#include "../detect/IMIDetectST.h"

#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRTarget.h"
#include "../rendercore/IMIRTargetMgr.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
using namespace imi;

IMIFaceTuneNode::IMIFaceTuneNode(IMIInstPtr _app)
: IMINode(_app) {
    ntype = "IMIFaceTuneNode";
    m_name = "IMIFaceTuneNode";
    m_tuneMtl = mApp->getMtlLib()->getMtl("mask2d");
    if(m_tuneMtl) {
        m_tuneMtl->setBlendEnable(true);
        m_tuneMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
        m_tuneMtl->reloadShader();
    }
    m_tuneMesh = mApp->getComData()->faceMesh(IMI_E_FACEMESH_TUNE);
    if (m_tuneMesh) {
        m_tuneMesh->setDrawMethod(E_DRAW_TRIANGLES);
    }
    m_tuneSurface = MakeSharedPtr<IMISurface>();
    //
    IMIRTargetPtr t_use = mApp->getTargetMgr()->getTarget(E_TEX_HELP0);
    if(!t_use) {
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        mApp->getTargetMgr()->createTarget(E_TEX_HELP0, t_w, t_h, false, false);
    }
}

IMIFaceTuneNode::~IMIFaceTuneNode() {
    m_tuneMtl = nullptr;
    m_tuneMesh = nullptr;
    m_tuneSurface = nullptr;
}

void IMIFaceTuneNode::update(f32 dt){
    //
    IMIPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
    if( t_person && t_person->getExist() && m_tuneMesh && m_tuneMtl && m_tuneSurface){
        IMITexturePtr _tex = mApp->getTexMgr()->getInTexture(E_TEX_CAMERA);
        m_tuneSurface->setTexture(1, 0, _tex);
        s32 t_width = mApp->m_global_param.sv_width;
        s32 t_height = mApp->m_global_param.sv_height;
        FVec2 t_resolution = FVec2(t_width, t_height);
        m_tuneSurface->setParam("uResolution", t_resolution);
        m_tuneSurface->setParam("uTex0size", t_resolution);
        m_tuneSurface->setParam("uTex1size", t_resolution);
        FVec2 texcoordClip = FVec2(1.0f,1.0f);
        m_tuneSurface->setParam("texcoord0Clip", texcoordClip);
        m_tuneSurface->setParam("texcoord1Clip", texcoordClip);
        FVec2 t_invert0 = FVec2(1.0f,-1.0f);
        m_tuneSurface->setParam("uInvert", t_invert0);
        
        //顶点描述
        IMIVertStreamDspPtr t_vert_dsp= m_tuneMesh->getStreamDsp();
        t_vert_dsp->setBufType(E_BFT_DYNAMIC_DRAW);
        s32 t_ptNum = 0;
        f32 *t_vertexPts = t_person->getFaceData(t_ptNum, IMI_E_FACEDATA_TUNED, true);
        t_vert_dsp->setVertCnt(t_ptNum);
        t_vert_dsp->setSigleStreamData(E_VF_V2, t_vertexPts, t_ptNum*2*sizeof(f32));
        f32 *t_keyPts = t_person->getFaceData(t_ptNum, IMI_E_FACEDATA_TUNED);
        t_vert_dsp->setSigleStreamData(E_VF_T0, t_keyPts, t_ptNum*2*sizeof(f32));
    }
}

void IMIFaceTuneNode::render(){
    IMIPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
    if(t_person && t_person->getExist() && m_tuneMesh && m_tuneMtl && m_tuneSurface) {
        IMIRTargetPtr t_mainTarget = mApp->getTargetMgr()->getTarget(E_TEX_MAIN);
        IMIRCmdPassPtr t_pass1 = MakeSharedPtr<IMIRCmdPass>();
        t_pass1->mTag = "IMIFaceTuneNode";
        t_pass1->setSwapTarget(E_TEX_MAIN);
        t_pass1->setUseTarget(E_TEX_HELP0);
        t_pass1->setMesh(m_tuneMesh);
        t_pass1->setSurface(m_tuneSurface);
        t_pass1->setMaterial(m_tuneMtl);
        t_mainTarget->pushCommand(t_pass1, E_RSM_FACEMORPH);
    }
}

//序列化接口
void IMIFaceTuneNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue) {
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    _toJsonData(_allocator, locationObj);
    //    if (m_mtlFace2D && m_mtlFace2D->getMaskTexture()) {
    //        IMITexturePtr maskTexture = m_mtlFace2D->getMaskTexture();
    //        IMIString texName = maskTexture->getname();
    //        s32 pos = texName.rfind('/');
    //        m_texName = IMIString::substr(texName.c_str(), pos+1);
    //        locationObj.AddMember("texture", RAPIDJSON_NAMESPACE::StringRef(m_texName.c_str()), _allocator);
    //    }
    _objValue.AddMember("IMIFaceTuneNode", locationObj, _allocator);
}

void IMIFaceTuneNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
//    _fromJsonData(item);
//    if (item.HasMember("texture") && item["texture"].IsString()) {
//        IMIString t_textureName = item["texture"].GetString();
//        IMIString t_texturePath = m_rootPath + t_textureName;
//        IMITexturePtr tex = mApp->getTexMgr()->getTextureSync(t_texturePath.c_str(), true);
//        m_maskMtl->setTexture(0, tex);
//    }
}
