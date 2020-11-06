//
// IMIBillboardNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//


#include "IMIBillboardNode.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMICameraNode.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMIMtlBillboard.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../core/IMIGeoGen.h"
#include "../basesys/IMIConfig.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMITexMgr.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../basesys/IMIComData.h"

using namespace imi;

//
IMIBillboardNode::IMIBillboardNode(IMIInstPtr _app)
:IMISpriteNode(_app) {
    ntype = "IMIBillboardNode";
    m_inTexType = E_TEX_END;
    m_pTexPath = "default";
    m_rsType = RST_SOLID_3D;
    m_canSelect = false;
    m_pTex = nullptr;
    m_pMesh = nullptr;
    m_viewPos.set(0.0f, 0.0f, 0.0f);
    m_up.set(0.0f, 0.0f, 0.0f);
    setTexcoord(1.0,-1.0);
//    setSize(100,100);
//    m_pMtl = MakeSharedPtr<IMIMtlBillboard>(_app);
//    m_pMtl->setDepthEnable(false);
//    m_pMtl->setBlendEnable(true);
//    m_pMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
}

IMIBillboardNode::IMIBillboardNode(IMIInstPtr _app,f32 _w,f32 _h)
:IMISpriteNode(_app) {
    ntype = "IMIBillboardNode";
    m_inTexType = E_TEX_END;
    m_rsType = RST_SOLID_3D;
    m_canSelect = false;
    m_pTex = nullptr;
    m_pMesh = nullptr;
    setTexcoord(1.0,-1.0);
    setSize(_w,_h);
}

IMIBillboardNode::~IMIBillboardNode() {
    m_pMesh = nullptr;
    m_pTex = nullptr;
}

//
void IMIBillboardNode::setSize(f32 _w,f32 _h) {
    m_width = _w;
    m_height = _h;
    m_pMesh = IMIGeoGen::genRect(mApp, m_width, m_height,m_aabbBox);
}

void IMIBillboardNode::syncTexSize() {
    if(m_inTexType == E_TEX_END) {
        m_pTex = mApp->getTexMgr()->getTexture(m_pTexPath.c_str(),true);
    }else {
        //m_pTex = mApp->getRenderer()->getIMITex(m_inTexType);
    }
    if(m_pTex) {
//        s32 t_w = m_pTex->getwidth();
//        s32 t_h = m_pTex->getheight();
//        setSize(t_w,t_h);
    }
}

void IMIBillboardNode::setTexcoord(f32 _x,f32 _y){
    m_texcoordX=_x;
    m_texcoordY=_y;
}

void IMIBillboardNode::setTexture(cptr8 _path, bool enableMipMap){
    if(m_pTexPath!=_path) {
        m_pTexPath = _path;
        m_pTex = mApp->getTexMgr()->getTexture(m_pTexPath.c_str(),true);
    }
}

void IMIBillboardNode::setViewPos(FVec3 &_pos){
    m_viewPos = _pos;
}

void IMIBillboardNode::setUp(FVec3 &_up){
    m_up = _up;
}

cptr8 IMIBillboardNode::getTexturePath(){
//    if (m_pTex) {
//        return m_pTex->getname();
//    }
    return m_pTexPath.c_str();
}

void IMIBillboardNode::setTexture(IMI_TEXIN _textype){
    m_inTexType = _textype;
}

void IMIBillboardNode::setTexture(IMITexturePtr _tex){
    if (m_pTex) {
        m_pTex = nullptr;
    }
    m_pTex = _tex;
}

void IMIBillboardNode::setMesh(IMIRenderMeshPtr _mesh){
    if (_mesh) {
        m_pMesh = _mesh;
    }
}

void IMIBillboardNode::update(f32 dt) {
    IMINode::update(dt);
//    if (m_pRenderObj && m_pMesh) {
//        if(m_pMtl){
//            IMIMtlBillboardPtr t_billboard = DYN_TO_SHAREPTR(IMIMtlBillboard, m_pMtl);
//            if (t_billboard) {
//                t_billboard->setObjectPos(getPosition());
//                t_billboard->setViewPos(m_viewPos);
//                t_billboard->setUp(m_up);
//            }
//            m_pMtl->setModelMatrix(m_absolutMat);
//            m_pMtl->setTexcoordFlip(m_texcoordX, m_texcoordY);
//            if(m_inTexType == E_TEX_END) {
//                m_pMtl->setTexture(0,m_pTex);
//            }else{
//                IMITexturePtr t_tex = mApp->getRenderer()->getIMITex(m_inTexType);
//                m_pMtl->setTexture(0,t_tex);
//            }
//            m_pMtl->update(dt);
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(m_pMtl);
//        }else{
//            //创建新的材质
//            IMIMtlCorePtr t_mtl = MakeSharedPtr<IMIMtlCore>(mApp, "normal2d");
//            t_mtl->setModelMatrix(m_absolutMat);
//            t_mtl->setTexcoordFlip(m_texcoordX, m_texcoordY);
//            t_mtl->setBlendEnable(true);
//            t_mtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//            if(m_inTexType == E_TEX_END) {
//                t_mtl->setTexture(0,m_pTex);
//            }else{
//                IMITexturePtr t_tex = mApp->getRenderer()->getIMITex(m_inTexType);
//                t_mtl->setTexture(0,t_tex);
//            }
//            t_mtl->update(dt);
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(t_mtl);
//        }
//    }
}

void IMIBillboardNode::render() {
    if (m_visible){
//        IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        if (m_pRenderObj) {
//            m_pRenderObj->pushCmd(t_rs, m_rsType, "IMIBillboardNode");
//        }
    }
    IMINode::render();
}

//序列化
void IMIBillboardNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue){
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    //_toJsonData(_allocator, locationObj);
    locationObj.AddMember("spriteW", m_width, _allocator);
    locationObj.AddMember("spriteH", m_height, _allocator);
    s32 pos = m_pTexPath.rfind('/');
    m_pTexName = IMIString::substr(m_pTexPath.c_str(), pos+1);
    locationObj.AddMember("texture", RAPIDJSON_NAMESPACE::StringRef(m_pTexName.c_str()), _allocator);
    locationObj.AddMember("textype", s32(m_inTexType), _allocator);
    _objValue.AddMember("IMISpriteNode", locationObj, _allocator);
}

void IMIBillboardNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item){
    _fromJsonData(item);
    if (item.HasMember("spriteW") && item["spriteW"].IsFloat()) {
        m_width = item["spriteW"].GetFloat();
    }
    if (item.HasMember("spriteH") && item["spriteH"].IsFloat()) {
        m_height = item["spriteH"].GetFloat();
    }
    setSize(m_width, m_height);
    if (item.HasMember("texture") && item["texture"].IsString()) {
        IMIString t_textureName = item["texture"].GetString();
        IMIString t_texturePath = m_rootPath + t_textureName;
        //setTexture(t_texturePath.c_str(), m_enableMipMap);
    }
    if (item.HasMember("textype") && item["textype"].IsInt()) {
        m_inTexType = IMI_TEXIN(item["textype"].GetInt());
    }
    m_dirty = true;
}
