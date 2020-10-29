//
// SVFaceTuneNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFaceTuneNode.h"
#include "SVScene.h"

#include "../basesys/SVComData.h"
#include "../core/SVPass.h"

#include "../mtl/SVMtlLib.h"
#include "../mtl/SVSurface.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVTexMgr.h"

#include "../basesys/SVConfig.h"

#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRTargetMgr.h"

using namespace sv;

SVFaceTuneNode::SVFaceTuneNode(SVInstPtr _app)
: SVNode(_app) {
    ntype = "SVFaceTuneNode";
    m_name = "SVFaceTuneNode";
    m_maskMtl = mApp->getMtlLib()->getMtl("normal2d");
    if(m_maskMtl) {
        m_maskMtl->reloadShader();
    }
    m_pFaceMesh = mApp->getComData()->faceMesh(SV_E_FACEMESH_TUNE);
    if (m_pFaceMesh) {
        m_pFaceMesh->setDrawMethod(E_DRAW_TRIANGLES);
    }
    
    SVRTargetPtr t_use = mApp->getTargetMgr()->getTarget(E_TEX_HELP0);
    if(!t_use) {
        s32 t_w = mApp->m_global_param.sv_width;
        s32 t_h = mApp->m_global_param.sv_height;
        mApp->getTargetMgr()->createTarget(E_TEX_HELP0, t_w, t_h, false, false);
    }
}

SVFaceTuneNode::~SVFaceTuneNode() {
    m_maskMtl = nullptr;
    m_pFaceMesh = nullptr;
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
