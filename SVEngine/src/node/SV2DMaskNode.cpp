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
//    m_intensity = 1.0;
//    m_maskType = SV_E_2DMASK_FACE;
//    m_blendMode = SV_E_2DMASK_BLENDMODE_NORMAL;
//    m_tex0width = 720.0;
//    m_tex0height = 1280.0;
//    m_tex1width = 720.0;
//    m_tex1height = 1280.0;
//    m_pIndexs = MakeSharedPtr<SVDataSwap>();
//    m_pVerts = MakeSharedPtr<SVDataSwap>();
//    m_pT0 = MakeSharedPtr<SVDataSwap>();
//    m_pT1 = MakeSharedPtr<SVDataSwap>();
//    m_pC = MakeSharedPtr<SVDataSwap>();
//    m_pMtl = MakeSharedPtr<SVMtlCore>(mApp,"screennor");
//    m_maskMtl = MakeSharedPtr<SVMtlMask>(mApp, "maskNormal");
//    m_pFaceMesh = MakeSharedPtr<SVRenderMeshDvid>(mApp);
//    m_tex1width = mApp->getConfig()->getCameraWidth();
//    m_tex1height = mApp->getConfig()->getCameraHeight();
//    FaceMesh* facemesh = mApp->getDataMgr()->getFaceDataMesh()->getFaceMesh("mesh_face");
//    StanderFace *facetexcoord = mApp->getDataMgr()->getFaceDataMesh()->getStanderFace("texcoord_face");
//    if (facetexcoord) {
//        f32 texcoord0[MAX_KEYPOINTS_NUM];
//        memset(texcoord0, 0, sizeof(texcoord0));
//        m_tex0width = facetexcoord->design_img_width;
//        m_tex0height = facetexcoord->design_img_height;
//        s32 t_texcoord0_count = facetexcoord->facepoints_count;
//        for (s32 i=0; i<t_texcoord0_count*2; i++) {
//            texcoord0[i] = facetexcoord->points[i];
//        }
//        m_pT0->writeData(texcoord0, t_texcoord0_count*2*sizeof(f32));
//    }
//    if (facemesh) {
//        u16 newmesh[600*3];
//        memset(newmesh, 0, sizeof(newmesh));
//        m_meshsize = facemesh->tricount;
//        for (s32 i=0; i<m_meshsize*3; i++) {
//            newmesh[i] = facemesh->triangles[i];
//        }
//        m_pIndexs->writeData(newmesh, m_meshsize*3*sizeof(u16));
//    }
//    //这里在 iphone6 上使用 GL_DYNAMIC_DRAW 会导致切动效的时候崩溃，苹果官方文档中说明 GL_STREAM_DRAW 等同于 GL_DYNAMIC_DRAW ，暂时先这样解决。
//#if defined(TARGET_OS_IPHONE)
//    m_pFaceMesh->setVertexPoolType(GL_STREAM_DRAW);
//#else
//    m_pFaceMesh->setVertexPoolType(GL_DYNAMIC_DRAW);
//#endif
//    m_pFaceMesh->setVertexType(E_VF_V2_C_T0_T1);
//    m_pFaceMesh->setIndexPoolType(GL_STATIC_DRAW);
//    m_pFaceMesh->setIndexData(m_pIndexs, m_meshsize*3);
//    m_pFaceMesh->setTexcoord0Data(m_pT0);
//    m_pFaceMesh->setColor0Data(m_pC);
//    m_pFaceMesh->setDrawMethod(E_DM_TRIANGLES);
//    m_pFaceMesh->createMesh();
//
//    //
//    SVRendererBasePtr t_renderer = mApp->getRenderer();
//    m_mainTex = t_renderer->getSVTex(E_TEX_MAIN);
//    if(! t_renderer->getSVTex(E_TEX_HELP0) ){
//        t_renderer->createSVTex(E_TEX_HELP0,m_mainTex->getwidth(), m_mainTex->getheight(), GL_RGBA);
//    }
//    m_help0Tex = t_renderer->getSVTex(E_TEX_HELP0);
//    m_fbo = MakeSharedPtr<SVRenderTexture>(mApp,
//                                           nullptr,
//                                           false,
//                                           false);
//    mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//    //
//    m_maskPass = MakeSharedPtr<SVPass>();
//    m_maskPass->setMtl(m_maskMtl);
//    m_maskPass->setMesh(m_pFaceMesh);
//    m_maskPass->setInTex(0, m_maskTex);
//    m_maskPass->setInTex(1, m_mainTex);
//    m_maskPass->setOutTex(m_help0Tex);
//    m_maskPass->setClear(true);
//    _addPass(m_maskPass);
//    //画回
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>();
//    t_pass2->setMtl(m_pMtl);
//    t_pass2->setMesh(mApp->getDataMgr()->m_screenMesh);
//    t_pass2->setInTex(0, m_help0Tex);
//    t_pass2->setOutTex(m_mainTex);
//    t_pass2->setClear(false);
//    _addPass(t_pass2);
}

SV2DMaskNode::~SV2DMaskNode() {
//    m_pFaceMesh = nullptr;
//    m_pIndexs = nullptr;
//    m_pVerts = nullptr;
//    m_pT0 = nullptr;
//    m_pT1 = nullptr;
//    m_pC = nullptr;
//    m_maskMtl = nullptr;
//    m_maskTex = nullptr;
//    m_mainTex = nullptr;
//    m_help0Tex = nullptr;
//    m_pMtl = nullptr;
//    m_maskPass = nullptr;
//    _clearPass();
}

void SV2DMaskNode::setMask(cptr8 _path){
//    SVTexturePtr tex = mApp->getTexMgr()->getTextureSync(_path, true);
//    if (tex) {
//        m_maskTex = tex;
//    }
}

void SV2DMaskNode::setIntensity(f32 _intensity){
//    if (_intensity >= 0 && _intensity <= 1.0) {
//        m_intensity = _intensity;
//    }
}

void SV2DMaskNode::setBlendMode(SV_E_2DMASK_BLENDMODE _mode){
//    if (m_blendMode != _mode) {
//        m_blendMode = _mode;
//        SVString t_shaderName = "maskNormal";
//        if (m_blendMode == SV_E_2DMASK_BLENDMODE_NONE) {
//            t_shaderName = "maskNone";
//        }else if (m_blendMode == SV_E_2DMASK_BLENDMODE_NORMAL){
//            t_shaderName = "maskNormal";
//        }else if (m_blendMode == SV_E_2DMASK_BLENDMODE_MULTIPLY){
//            t_shaderName = "maskMultiply";
//        }else if (m_blendMode == SV_E_2DMASK_BLENDMODE_SOFTLIGHT){
//            t_shaderName = "maskSoftLight";
//        }else if (m_blendMode == SV_E_2DMASK_BLENDMODE_SCREEN){
//            t_shaderName = "maskScreen";
//        }
//        m_maskMtl = MakeSharedPtr<SVMtlMask>(mApp, t_shaderName.c_str());
//        m_maskPass->setMtl(m_maskMtl);
//        m_maskPass->setInTex(0, m_maskTex);
//        m_maskPass->setInTex(1, m_mainTex);
//        m_maskPass->setOutTex(m_help0Tex);
//    }
}

void SV2DMaskNode::setMaskType(SV_E_2DMASK_TYPE _type){
//    if (m_maskType != _type) {
//        m_maskType = _type;
//        //
//        FaceMesh* facemesh = nullptr;
//        StanderFace *facetexcoord = nullptr;
//        SVString t_tecoordFile("");
//        if (m_maskType == SV_E_2DMASK_FACE) {
//            facemesh = mApp->getDataMgr()->getFaceDataMesh()->getFaceMesh("mesh_face");
//            facetexcoord = mApp->getDataMgr()->getFaceDataMesh()->getStanderFace("texcoord_face");
//        }else if (m_maskType == SV_E_2DMASK_EYEBROW){
//            facemesh = mApp->getDataMgr()->getFaceDataMesh()->getFaceMesh("mesh_eyebrow");
//            facetexcoord = mApp->getDataMgr()->getFaceDataMesh()->getStanderFace("texcoord_eyebrow");
//        }else if (m_maskType == SV_E_2DMASK_EYELASH || m_maskType == SV_E_2DMASK_EYELID){
//            facemesh = mApp->getDataMgr()->getFaceDataMesh()->getFaceMesh("mesh_eye");
//            facetexcoord = mApp->getDataMgr()->getFaceDataMesh()->getStanderFace("texcoord_eye");
//        }
//        if (facetexcoord) {
//            f32 texcoord0[MAX_KEYPOINTS_NUM];
//            memset(texcoord0, 0, sizeof(texcoord0));
//            m_tex0width = facetexcoord->design_img_width;
//            m_tex0height = facetexcoord->design_img_height;
//            m_tex1width = mApp->getConfig()->getCameraWidth();
//            m_tex1height = mApp->getConfig()->getCameraHeight();
//            s32 t_texcoord0_count = facetexcoord->facepoints_count;
//            for (s32 i=0; i<t_texcoord0_count*2; i++) {
//                texcoord0[i] = facetexcoord->points[i];
//            }
//            m_pT0->writeData(texcoord0, t_texcoord0_count*2*sizeof(f32));
//            m_pFaceMesh->setTexcoord0Data(m_pT0);
//        }
//        if (facemesh) {
//            u16 newmesh[600*3];
//            memset(newmesh, 0, sizeof(newmesh));
//            m_meshsize = facemesh->tricount;
//            for (s32 i=0; i<m_meshsize*3; i++) {
//                newmesh[i] = facemesh->triangles[i];
//            }
//            m_pIndexs->writeData(newmesh, m_meshsize*3*sizeof(u16));
//            m_pFaceMesh->setIndexPoolType(GL_STATIC_DRAW);
//            m_pFaceMesh->setIndexData(m_pIndexs, m_meshsize*3);
//        }
//    }
}
//
//SV_E_2DMASK_TYPE SV2DMaskNode::getMaskType(){
//    return m_maskType;
//}
//
//void SV2DMaskNode::_addPass(SVPassPtr _pass) {
//    if(_pass){
//        m_passPool.append(_pass);
//    }
//}
//
//void SV2DMaskNode::_clearPass() {
//    m_passPool.destroy();
//}

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
