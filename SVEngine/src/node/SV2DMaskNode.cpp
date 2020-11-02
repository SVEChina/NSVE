//
// SV2DMaskNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SV2DMaskNode.h"
#include "SVScene.h"
#include "../core/SVPass.h"
#include "../core/SVVertDef.h"
#include "../mtl/SVTexture.h"
//#include "../mtl/SVMtlMask.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVTexMgr.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../detect/SVDetectMgr.h"

using namespace sv;

SV2DMaskNode::SV2DMaskNode(SVInstPtr _app)
: SVNode(_app) {
    ntype = "SV2DMaskNode";
}

SV2DMaskNode::~SV2DMaskNode() {

}

void SV2DMaskNode::update(f32 dt){
//    SVPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(m_personID);
//    if( m_maskTex && t_person && t_person->getExist() && (m_intensity != 0)){
//        m_pFaceMesh->setvisible(true);
//        s32 t_ptnum = 0;
//        s32 t_texcoordnum = 0;
//        if (m_maskType == SV_E_2DMASK_FACE) {
//            f32 *ptsData = t_person->getFaceWithMouthMeshData(t_ptnum, SV_E_FACEDATA_SCENE);
//            if (ptsData) {
//                m_pVerts->writeData(ptsData, t_ptnum * 2 * sizeof(f32));
//            }
//            f32 *texcoordData = t_person->getFaceWithMouthMeshData(t_texcoordnum, SV_E_FACEDATA_SCREEN);
//            if (texcoordData) {
//                m_pT1->writeData(texcoordData, t_texcoordnum * 2 * sizeof(f32));
//            }
//            //颜色
//            C color[t_ptnum];
//            memset(&color[0], 250, sizeof(C)*t_ptnum);
//            m_pC->writeData(&color[0], sizeof(C)*t_ptnum);
//
//        }else if (m_maskType == SV_E_2DMASK_EYEBROW){
//            f32 *ptsData = t_person->getEyebrowMeshData(t_ptnum, SV_E_FACEDATA_SCENE);
//            if (ptsData) {
//                m_pVerts->writeData(ptsData, t_ptnum * 2 * sizeof(f32));
//            }
//            f32 *texcoordData = t_person->getEyebrowMeshData(t_texcoordnum, SV_E_FACEDATA_SCREEN);
//            if (texcoordData) {
//                m_pT1->writeData(texcoordData, t_texcoordnum * 2 * sizeof(f32));
//            }
//            //颜色
//            C color[t_ptnum];
//            memset(&color[0], 250, sizeof(C)*t_ptnum);
//            m_pC->writeData(&color[0], sizeof(C)*t_ptnum);
//
//        }else if (m_maskType == SV_E_2DMASK_EYELASH || m_maskType == SV_E_2DMASK_EYELID){
//            f32 *ptsData = t_person->getEyeMeshData(t_ptnum, SV_E_FACEDATA_SCENE);
//            if (ptsData) {
//                m_pVerts->writeData(ptsData, t_ptnum * 2 * sizeof(f32));
//            }
//            f32 *texcoordData = t_person->getEyeMeshData(t_texcoordnum, SV_E_FACEDATA_SCREEN);
//            if (texcoordData) {
//                m_pT1->writeData(texcoordData, t_texcoordnum * 2 * sizeof(f32));
//            }
//            //颜色
//            C color[t_ptnum];
//            memset(&color[0], 250, sizeof(C)*t_ptnum);
//            //这里处理了下！！！！！！！！！!!!!!后16点个透明度为0
//            for (s32 i = 0; i<16; i++) {
//                color[t_ptnum-i-1].a = 0;
//            }
//            m_pC->writeData(&color[0], sizeof(C)*t_ptnum);
//        }
//        m_pFaceMesh->setVertex2Data(m_pVerts);
//        m_pFaceMesh->setTexcoord1Data(m_pT1);
//        m_pFaceMesh->setColor0Data(m_pC);
//        //update material
//        m_pMtl->setBlendEnable(true);
//        m_pMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//        m_pMtl->setTexcoordFlip(1.0, 1.0);
//        //
//        m_maskMtl->update(dt);
//        m_maskMtl->setBlendEnable(true);
//        m_maskMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//        m_maskMtl->setIntensity(m_intensity);
//        m_maskMtl->setModelMatrix(m_absolutMat.get());
//        m_maskMtl->setTexture(0, m_maskTex);
//        m_maskMtl->setTexcoordFlip(1.0, 1.0);
//        m_maskMtl->setTexSizeIndex(0, 1.0f/m_tex0width, 1.0f/m_tex0height);
//        m_maskMtl->setTexSizeIndex(1, 1.0f/(m_tex1width), 1.0f/m_tex1height);
//    }else{
//        m_pFaceMesh->setvisible(false);
//    }
}

void SV2DMaskNode::render(){
//    if (!mApp->m_pGlobalParam->m_curScene)
//        return;
//    SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//    SVPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(m_personID);
//    if( m_maskTex && t_person && t_person->getExist() && (m_intensity != 0) && m_maskTex){
//        for(s32 i=0;i<m_passPool.size();i++){
//            if(m_passPool[i]->m_pMtl){
//                SVRenderCmdPassPtr t_cmd = MakeSharedPtr<SVRenderCmdPass>();
//                t_cmd->mTag = m_name;
//                t_cmd->setClear(m_passPool[i]->m_isClear);
//                t_cmd->setFbo(m_fbo);
//                t_cmd->setTexture(m_passPool[i]->m_outTex);
//                t_cmd->setMesh(m_passPool[i]->m_pMesh);
//                t_cmd->setMaterial(m_passPool[i]->m_pMtl);
//                t_rs->pushRenderCmd(RST_MASK2D, t_cmd);
//            }
//        }
//    }
}

//序列化接口
void SV2DMaskNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue) {
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    _toJsonData(_allocator, locationObj);
    //    if (m_mtlFace2D && m_mtlFace2D->getMaskTexture()) {
    //        SVTexturePtr maskTexture = m_mtlFace2D->getMaskTexture();
    //        SVString texName = maskTexture->getname();
    //        s32 pos = texName.rfind('/');
    //        m_texName = SVString::substr(texName.c_str(), pos+1);
    //        locationObj.AddMember("texture", RAPIDJSON_NAMESPACE::StringRef(m_texName.c_str()), _allocator);
    //    }
//    _objValue.AddMember("SV2DMaskNode", locationObj, _allocator);
}

void SV2DMaskNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
//    _fromJsonData(item);
//    if (item.HasMember("texture") && item["texture"].IsString()) {
//        SVString t_textureName = item["texture"].GetString();
//        SVString t_texturePath = m_rootPath + t_textureName;
//        setMask(t_texturePath);
//    }
//    if (item.HasMember("intensity") && item["intensity"].IsFloat()) {
//        f32 t_intensity = item["intensity"].GetFloat();
//        setIntensity(t_intensity);
//    }
//    if (item.HasMember("masktype") && item["masktype"].IsInt()) {
//        s32 t_maskType = item["masktype"].GetInt();
//        setMaskType(SV_E_2DMASK_TYPE(t_maskType));
//    }
//    if (item.HasMember("blendmode") && item["blendmode"].IsInt()) {
//        s32 t_blendMode = item["blendmode"].GetInt();
//        setBlendMode((SV_E_2DMASK_BLENDMODE)t_blendMode);
//    }
//    m_personID = 1;
}
