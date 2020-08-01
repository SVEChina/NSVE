//
// SVSpriteNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#include "SVSpriteNode.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVCameraNode.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVMtl2D.h"
#include "../rendercore/SVRenderMesh.h"
#include "../core/SVGeoGen.h"
#include "../basesys/SVConfig.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTexMgr.h"
#include "../app/SVInst.h"
#include "../rendercore/SVRenderObject.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../basesys/SVComData.h"

using namespace sv;

//
SVSpriteNode::SVSpriteNode(SVInstPtr _app)
:SVNode(_app) {
    ntype = "SVSpriteNode";
    m_rsType = RST_SOLID_3D;
    m_canSelect = false;
    m_pTex = nullptr;
    m_pMesh = nullptr;
    setSize(100,100);
}

SVSpriteNode::SVSpriteNode(SVInstPtr _app,f32 _w,f32 _h)
:SVNode(_app) {
    ntype = "SVSpriteNode";
    m_rsType = RST_SOLID_3D;
    m_canSelect = false;
    m_pTex = nullptr;
    m_pMesh = nullptr;
    setSize(_w,_h);
}

SVSpriteNode::~SVSpriteNode() {
    m_pMesh = nullptr;
    m_pMtl = nullptr;
    m_pTex = nullptr;
}

//
void SVSpriteNode::setSize(f32 _w,f32 _h) {
    m_width = _w;
    m_height = _h;
    if( m_pMesh ){
        //更新数据
        V3_T0 t_verts[4];
        t_verts[0].x = -0.5f * m_width;
        t_verts[0].y = -0.5f * m_height;
        t_verts[0].z = 0.0f;
        t_verts[0].t0x = 0.0f;
        t_verts[0].t0y = 0.0f;
        t_verts[1].x = 0.5f * m_width;
        t_verts[1].y = -0.5f * m_height;
        t_verts[1].z = 0.0f;
        t_verts[1].t0x = 1.0f;
        t_verts[1].t0y = 0.0f;
        t_verts[2].x = -0.5f * m_width;
        t_verts[2].y = 0.5f * m_height;
        t_verts[2].z = 0.0f;
        t_verts[2].t0x = 0.0f;
        t_verts[2].t0y = 1.0f;
        t_verts[3].x = 0.5f * m_width;
        t_verts[3].y = 0.5f * m_height;
        t_verts[3].z = 0.0f;
        t_verts[3].t0x = 1.0f;
        t_verts[3].t0y = 1.0f;
        SVDataSwapPtr _data = MakeSharedPtr<SVDataSwap>();
        _data->appendData(t_verts, sizeof(V3_T0)*4);
        m_pMesh->setVertexData(_data);
    }else{
        //创建mesh
        m_pMesh = SVGeoGen::genRect(mApp, m_width, m_height,m_aabbBox);
    }
}

f32 SVSpriteNode::getWidth(){
    return m_width;
}

f32 SVSpriteNode::getHeight(){
    return m_height;
}

void SVSpriteNode::setTexture(cptr8 _path){
    m_pTex = mApp->getTexMgr()->getTexture(_path,true);
}

void SVSpriteNode::setTexture(SVTEXINID _textype){
    //m_inTexType = _textype;
}

void SVSpriteNode::setTexture(SVTexturePtr _tex){
    if (m_pTex) {
        m_pTex = nullptr;
    }
    m_pTex = _tex;
}

SVTexturePtr SVSpriteNode::getTexture() {
    return m_pTex;
}

void SVSpriteNode::syncTexSize() {
    if(m_pTex) {
        s32 t_w = m_pTex->getTextureDsp()->m_width;
        s32 t_h = m_pTex->getTextureDsp()->m_height;
        setSize(t_w,t_h);
    }
}

void SVSpriteNode::update(f32 dt) {
    SVNode::update(dt);
//    if ( m_pMesh ) {
//        if(m_pMtl){
//            m_pMtl->setBlendEnable(true);
//            m_pMtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//            m_pMtl->setModelMatrix(m_absolutMat);
//            m_pMtl->setTexcoordFlip(m_texcoordX, m_texcoordY);
//            if(m_inTexType == E_TEX_END) {
//                m_pMtl->setTexture(0,m_pTex);
//            }else{
//                SVTexturePtr t_tex = mApp->getRenderer()->getSVTex(m_inTexType);
//                m_pMtl->setTexture(0,t_tex);
//            }
//            m_pMtl->update(dt);
//            SVMtl2DPtr t_mtl2D = DYN_TO_SHAREPTR(SVMtl2D, m_pMtl);
//            if (t_mtl2D) {
//                t_mtl2D->setAlpha(m_alpha);
//            }
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(m_pMtl);
//        }else{
//            //创建新的材质
//            SVMtl2DPtr t_mtl = MakeSharedPtr<SVMtl2D>(mApp, "normal2d_c");
//            t_mtl->setModelMatrix(m_absolutMat);
//            t_mtl->setTexcoordFlip(m_texcoordX, m_texcoordY);
//            t_mtl->setBlendEnable(true);
//            t_mtl->setBlendState(MTL_BLEND_ONE, MTL_BLEND_ONE_MINUS_SRC_ALPHA);
//            t_mtl->setAlpha(1.0f);
//            if(m_inTexType == E_TEX_END) {
//                t_mtl->setTexture(0,m_pTex);
//            }else{
//                SVTexturePtr t_tex = mApp->getRenderer()->getSVTex(m_inTexType);
//                t_mtl->setTexture(0,t_tex);
//            }
//            t_mtl->update(dt);
//            m_pRenderObj->setMesh(m_pMesh);
//            m_pRenderObj->setMtl(t_mtl);
//            m_pMtl = t_mtl;
//        }
//    }
}

void SVSpriteNode::render() {
    if ( m_visible ){
//        SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        if (m_pRenderObj) {
//            m_pRenderObj->pushCmd(t_rs, m_rsType, "SVSpriteNode");
//        }
    }
    SVNode::render();
}

//序列化
void SVSpriteNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue){
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    //_toJsonData(_allocator, locationObj);
    locationObj.AddMember("spriteW", m_width, _allocator);
    locationObj.AddMember("spriteH", m_height, _allocator);
    //s32 pos = m_pTexPath.rfind('/');
    //m_pTexName = SVString::substr(m_pTexPath.c_str(), pos+1);
    //locationObj.AddMember("texture", RAPIDJSON_NAMESPACE::StringRef(m_pTexName.c_str()), _allocator);
    //locationObj.AddMember("textype", s32(m_inTexType), _allocator);
    //_objValue.AddMember("SVSpriteNode", locationObj, _allocator);
}

void SVSpriteNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item){
    _fromJsonData(item);
//    if (item.HasMember("spriteW") && item["spriteW"].IsFloat()) {
//        m_width = item["spriteW"].GetFloat();
//    }
//    if (item.HasMember("spriteH") && item["spriteH"].IsFloat()) {
//        m_height = item["spriteH"].GetFloat();
//    }
//    setSize(m_width, m_height);
//    if (item.HasMember("texture") && item["texture"].IsString()) {
//        SVString t_textureName = item["texture"].GetString();
//        SVString t_texturePath = m_rootPath + t_textureName;
//        setTexture(t_texturePath.c_str(), m_enableMipMap);
//    }
//    if (item.HasMember("textype") && item["textype"].IsInt()) {
//        m_inTexType = SVTEXINID(item["textype"].GetInt());
//    }
    m_dirty = true;
}
