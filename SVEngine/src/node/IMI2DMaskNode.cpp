//
// IMI2DMaskNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMI2DMaskNode.h"
#include "IMIScene.h"

#include "../app/IMIDispatch.h"
#include "../basesys/IMIComData.h"
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

using namespace imi;

IMI2DMaskNode::IMI2DMaskNode(IMIInstPtr _app)
: IMINode(_app) {
    ntype = "IMI2DMaskNode";
    m_name = "IMI2DMaskNode";
    m_maskMtl = mApp->getMtlLib()->getMtl("mask2d");
    if(m_maskMtl) {
        m_maskMtl->reloadShader();
    }
    m_maskMesh = mApp->getComData()->faceMesh(IMI_E_FACEMESH_SIMPILITY);
    if (m_maskMesh) {
        m_maskMesh->setDrawMethod(E_DRAW_TRIANGLES);
        IMIVertStreamDspPtr t_vert_dsp= m_maskMesh->getStreamDsp();
        t_vert_dsp->push(E_VF_V2);
        t_vert_dsp->push(E_VF_T0);
        t_vert_dsp->push(E_VF_T1);
//        t_vert_dsp->push(E_VF_C0);
    }
    m_maskSurface = MakeSharedPtr<IMISurface>();
    m_maskTarget = mApp->getTargetMgr()->getTarget(E_TEX_HELP0);
    if(!m_maskTarget) {
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        m_maskTarget = mApp->getTargetMgr()->createTarget(E_TEX_HELP0, t_w, t_h, false, false);
        m_maskTarget->pushStreamQuene(E_RSM_SOLID);
        mApp->getRenderMgr()->addRTarget(m_maskTarget,true);
    }
}

IMI2DMaskNode::~IMI2DMaskNode() {
    m_maskMtl = nullptr;
    m_maskMesh = nullptr;
    m_maskSurface = nullptr;
}

void IMI2DMaskNode::update(f32 dt){
    IMITexturePtr _tex = mApp->getTexMgr()->getInTexture(E_TEX_MAIN);
    m_maskSurface->setTexture(1, 1, _tex);
//    FVec2 t_invert = FVec2(1.0f,1.0f);
//    m_maskSurface->setParam("uInvert0", t_invert);
    //
    IMIPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
    if( t_person && t_person->getExist() && m_maskMesh && m_maskMtl && m_surface){
        //顶点描述
        IMIVertStreamDspPtr t_vert_dsp= m_maskMesh->getStreamDsp();
        t_vert_dsp->setBufType(E_BFT_DYNAMIC_DRAW);
        s32 t_ptNum = 0;
        f32 *t_vertexPts = t_person->getFaceData(t_ptNum, IMI_E_FACEDATA_SIMPLITY);
        t_vert_dsp->setVertCnt(t_ptNum);
        t_vert_dsp->setSigleStreamData(E_VF_V2, t_vertexPts, t_ptNum*2*sizeof(f32));
        f32 *t_keyPts = t_person->getFaceData(t_ptNum, IMI_E_FACEDATA_SIMPLITY);
        f32 t_texcoordPts[t_ptNum*2];
        memcpy(t_texcoordPts, t_keyPts, t_ptNum*2*sizeof(f32));
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        for (s32 i = 0; i<t_ptNum; i++) {
            t_texcoordPts[2*i] = t_texcoordPts[2*i]/(t_w*1.0);
            t_texcoordPts[2*i+1] = (t_h-t_texcoordPts[2*i+1])/(t_h*1.0);
        }
        t_vert_dsp->setSigleStreamData(E_VF_T1, t_texcoordPts, t_ptNum*2*sizeof(f32));
    }
}

void IMI2DMaskNode::render(){
    if (m_maskMtl && m_maskSurface && m_maskMesh && m_maskTarget) {
        IMIDispatch::dispatchMeshDraw(mApp,
                                     m_maskMesh,
                                     m_maskMtl,
                                     m_maskSurface,
                                     m_maskTarget,
                                     E_RSM_SOLID,
                                     "IMI2DMaskNode");
//        IMIRTargetPtr t_target = mApp->getTargetMgr()->getTarget(E_TEX_MAIN);
//        IMIRCmdPassPtr t_pass1 = MakeSharedPtr<IMIRCmdPass>();
//        t_pass1->mTag = "IMI2DMaskNode";
//        t_pass1->setSwapTarget(E_TEX_MAIN);
//        t_pass1->setUseTarget(E_TEX_HELP0);
//        t_pass1->setMesh(m_maskMesh);
//        t_pass1->setSurface(m_maskSurface);
//        t_pass1->setMaterial(m_maskMtl);
//        t_target->pushCommand(t_pass1, E_RSM_SOLID);
    }
}

//序列化接口
void IMI2DMaskNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue) {
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    _toJsonData(_allocator, locationObj);
    //    if (m_mtlFace2D && m_mtlFace2D->getMaskTexture()) {
    //        IMITexturePtr maskTexture = m_mtlFace2D->getMaskTexture();
    //        IMIString texName = maskTexture->getname();
    //        s32 pos = texName.rfind('/');
    //        m_texName = IMIString::substr(texName.c_str(), pos+1);
    //        locationObj.AddMember("texture", RAPIDJSON_NAMESPACE::StringRef(m_texName.c_str()), _allocator);
    //    }
//    _objValue.AddMember("IMI2DMaskNode", locationObj, _allocator);
}

void IMI2DMaskNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
//    _fromJsonData(item);
//    if (item.HasMember("texture") && item["texture"].IsString()) {
//        IMIString t_textureName = item["texture"].GetString();
//        IMIString t_texturePath = m_rootPath + t_textureName;
//        setMask(t_texturePath);
//    }
//    if (item.HasMember("intensity") && item["intensity"].IsFloat()) {
//        f32 t_intensity = item["intensity"].GetFloat();
//        setIntensity(t_intensity);
//    }
//    if (item.HasMember("masktype") && item["masktype"].IsInt()) {
//        s32 t_maskType = item["masktype"].GetInt();
//        setMaskType(IMI_E_2DMASK_TYPE(t_maskType));
//    }
//    if (item.HasMember("blendmode") && item["blendmode"].IsInt()) {
//        s32 t_blendMode = item["blendmode"].GetInt();
//        setBlendMode((IMI_E_2DMASK_BLENDMODE)t_blendMode);
//    }
//    m_personID = 1;
}
