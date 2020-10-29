//
// SVFaceTuneNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFaceTuneNode.h"
#include "SVScene.h"
#include "../core/SVPass.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVTexMgr.h"
#include "../basesys/SVConfig.h"
//#include "../basesys/SVStaticData.h"
//#include "../basesys/SVFaceDataMesh.h"
//#include "../rendercore/SVRenderMgr.h"
//#include "../rendercore/SVRenderMesh.h"
//#include "../rendercore/SVRenderObject.h"
//#include "../rendercore/SVRendererBase.h"
//#include "../rendercore/SVRenderTexture.h"
//#include "../rendercore/SVRenderCmd.h"
//#include "../rendercore/SVRenderScene.h"
//#include "../detect/SVDetectMgr.h"
//#include "../detect/SVKeyPointExt.h"

using namespace sv;

SVFaceTuneNode::SVFaceTuneNode(SVInstPtr _app)
: SVNode(_app) {
    ntype = "SVFaceTuneNode";
    m_name = "SVFaceTuneNode";
//    m_pIndexs = MakeSharedPtr<SVDataSwap>();
//    m_pVerts = MakeSharedPtr<SVDataSwap>();
//    m_pT0 = MakeSharedPtr<SVDataSwap>();
//    m_pMtl = MakeSharedPtr<SVMtlCore>(mApp,"screennor");
//    m_maskMtl= MakeSharedPtr<SVMtlCore>(mApp,"normal2d");
//    m_pFaceMesh = MakeSharedPtr<SVRenderMeshDvid>(mApp);
//    FaceMesh* facemesh = mApp->getDataMgr()->getFaceDataMesh()->getFaceMesh("mesh_face_tune");
//    StanderFace *standerface = mApp->getDataMgr()->getFaceDataMesh()->getStanderFace("texcoord_face_tune");
//    if (facemesh == nullptr || standerface == nullptr) {
//        return;
//    }
//    f32 texcoord0[MAX_POINTS_NUM];
//    memset(texcoord0, 0, sizeof(texcoord0));
//    u16 newmesh[600*3];
//    memset(newmesh, 0, sizeof(newmesh));
//    s32 t_texcoord0_count = standerface->facepoints_count;
//    f32 t_tex0width = standerface->design_img_width;
//    f32 t_tex0height = standerface->design_img_height;
//    for (s32 i=0; i<t_texcoord0_count; i++) {
//        texcoord0[2*i] = standerface->points[2*i]*(1.0/t_tex0width);
//        texcoord0[2*i+1] = standerface->points[2*i+1]*(1.0/t_tex0height);
//    }
//    m_meshsize = facemesh->tricount;
//    for (s32 i=0; i<m_meshsize*3; i++) {
//        newmesh[i] = facemesh->triangles[i];
//    }
//    m_pIndexs->writeData(newmesh, m_meshsize*3*sizeof(u16));
//    m_pT0->writeData(texcoord0, t_texcoord0_count*2*sizeof(f32));
//    //这里在 iphone6 上使用 GL_DYNAMIC_DRAW 会导致切动效的时候崩溃，苹果官方文档中说明 GL_STREAM_DRAW 等同于 GL_DYNAMIC_DRAW ，暂时先这样解决。
//#if defined(TARGET_OS_IPHONE)
//    m_pFaceMesh->setVertexPoolType(GL_STREAM_DRAW);
//#else
//    m_pFaceMesh->setVertexPoolType(GL_DYNAMIC_DRAW);
//#endif
//    m_pFaceMesh->setVertexType(E_VF_V2_T0);
//    m_pFaceMesh->setIndexPoolType(GL_STATIC_DRAW);
//    m_pFaceMesh->setIndexData(m_pIndexs, m_meshsize*3);
//    m_pFaceMesh->setTexcoord0Data(m_pT0);
//    m_pFaceMesh->setDrawMethod(E_DM_TRIANGLES);
//    m_pFaceMesh->createMesh();
//    //
//    SVRendererBasePtr t_renderer = mApp->getRenderer();
//    SVTexturePtr t_texmain = t_renderer->getSVTex(E_TEX_MAIN);
//    m_tex0width = t_texmain->getwidth();
//    m_tex0height = t_texmain->getheight();
//    if(! t_renderer->getSVTex(E_TEX_HELP0) ){
//        t_renderer->createSVTex(E_TEX_HELP0,t_texmain->getwidth(), t_texmain->getheight(), GL_RGBA);
//    }
//    SVTexturePtr t_texhelp0 = t_renderer->getSVTex(E_TEX_HELP0);
//    m_fbo = MakeSharedPtr<SVRenderTexture>(mApp,
//                                           nullptr,
//                                           false,
//                                           false);
//    mApp->getRenderMgr()->pushRCmdCreate(m_fbo);
//    //
//    SVPassPtr t_pass1 = MakeSharedPtr<SVPass>();
//    t_pass1->mTag = "SVFaceTuneNode_Tune";
//    t_pass1->setMtl(m_maskMtl);
//    t_pass1->setMesh(m_pFaceMesh);
//    t_pass1->setInTex(0, t_texmain);
//    t_pass1->setOutTex(t_texhelp0);
//    t_pass1->setClear(true);
//    _addPass(t_pass1);
//    //画回
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>();
//    t_pass2->mTag = "SVFaceTuneNode_DrawBack";
//    t_pass2->setMtl(m_pMtl);
//    t_pass2->setMesh(mApp->getDataMgr()->m_screenMesh);
//    t_pass2->setInTex(0, t_texhelp0);
//    t_pass2->setOutTex(t_texmain);
//    t_pass2->setClear(false);
//    _addPass(t_pass2);
}

SVFaceTuneNode::~SVFaceTuneNode() {
//    m_pFaceMesh = nullptr;
//    m_pIndexs = nullptr;
//    m_pVerts = nullptr;
//    m_pT0 = nullptr;
//    m_maskMtl = nullptr;
//    m_pMtl = nullptr;
//    _clearPass();
}

void SVFaceTuneNode::_addPass(SVPassPtr _pass) {
    if(_pass){
//        m_passPool.append(_pass);
    }
}

void SVFaceTuneNode::_clearPass() {
    m_passPool.destroy();
}

void SVFaceTuneNode::update(f32 dt){
//    SVPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(m_personID);
//    if( t_person && t_person->getExist() && t_person->getIsTuned()){
//        m_pFaceMesh->setvisible(true);
//        s32 t_ptnum = 0;
//        f32 *faceData = t_person->getFaceTuneMeshData(t_ptnum, SV_E_FACEDATA_SCENE_TUNE);
//        if (faceData) {
//            m_pVerts->writeData(faceData, t_ptnum * 2 * sizeof(f32));
//            m_pFaceMesh->setVertex2Data(m_pVerts);
//        }
//
//        f32 *texcoord_faceData = t_person->getFaceTuneMeshData(t_ptnum, SV_E_FACEDATA_SCREEN);
//        if (texcoord_faceData) {
//            f32 t_texcoord[300];
//            memcpy(t_texcoord, texcoord_faceData, t_ptnum * 2 * sizeof(f32));
//            for (s32 i = 0; i<t_ptnum; i++) {
//                t_texcoord[2*i] = t_texcoord[2*i]*(1.0/m_tex0width);
//                t_texcoord[2*i+1] = t_texcoord[2*i+1]*(1.0/m_tex0height);
//            }
//            m_pT0->writeData(t_texcoord, t_ptnum * 2 * sizeof(f32));
//            m_pFaceMesh->setTexcoord0Data(m_pT0);
//        }
//
//        //update material
//        m_maskMtl->update(dt);
//        m_maskMtl->setBlendEnable(true);
//        m_maskMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//        m_maskMtl->setModelMatrix(m_absolutMat.get());
//        m_maskMtl->setTexcoordFlip(1.0, -1.0);
//        m_maskMtl->setTexSizeIndex(0, 1.0f/m_tex0width, 1.0f/m_tex0height);
//        //
//        m_pMtl->setBlendEnable(true);
//        m_pMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//        m_pMtl->setTexcoordFlip(1.0, 1.0);
//    }else{
//        m_pFaceMesh->setvisible(false);
//    }
}

void SVFaceTuneNode::render(){
//    if (!mApp->m_pGlobalParam->m_curScene)
//        return;
//    SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//    SVPersonPtr t_person = mApp->getDetectMgr()->getPersonModule()->getPerson(1);
//    if( t_person && t_person->getExist() && t_person->getIsTuned()){
//        for(s32 i=0;i<m_passPool.size();i++){
//            if(m_passPool[i]->m_pMtl){
//                SVRenderCmdPassPtr t_cmd = MakeSharedPtr<SVRenderCmdPass>();
//                t_cmd->mTag = "SVFaceTuneNode";
//                t_cmd->setClear(m_passPool[i]->m_isClear);
//                t_cmd->setFbo(m_fbo);
//                t_cmd->setTexture(m_passPool[i]->m_outTex);
//                t_cmd->setMesh(m_passPool[i]->m_pMesh);
//                t_cmd->setMaterial(m_passPool[i]->m_pMtl);
//                t_rs->pushRenderCmd(RST_FACEMORPH, t_cmd);
//            }
//        }
//    }
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
