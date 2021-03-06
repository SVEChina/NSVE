//
// SVSpriteNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#include "SVSpriteNode.h"
#include "../app/SVDispatch.h"
#include "../app/SVInst.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVComData.h"
#include "../core/SVGeoGen.h"
#include "../mtl/SVMtlLib.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVSurface.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTexMgr.h"
#include "../rendercore/SVRenderMesh.h"

using namespace sv;

//
SVSpriteNode::SVSpriteNode(SVInstPtr _app)
:SVNode(_app) {
    ntype = "SVSpriteNode";
    m_rsType = RST_SOLID_3D;
    m_canSelect = false;
    m_pTex = nullptr;
    m_pMesh = nullptr;
    setSize(400.0f,400.0f);
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
    m_pTex = nullptr;
}

//
void SVSpriteNode::setSize(f32 _w,f32 _h) {
    m_width = _w;
    m_height = _h;
    f32 t_texcoord_size = 1.0f;
    if( m_pMesh ){
        //更新数据
        V3_T0 t_verts[4];
        t_verts[0].x = -0.5f * m_width;
        t_verts[0].y = -0.5f * m_height;
        t_verts[0].z = 0.0f;
        t_verts[0].t0x = 0.0f * t_texcoord_size;
        t_verts[0].t0y = 0.0f * t_texcoord_size;
        t_verts[1].x = 0.5f * m_width;
        t_verts[1].y = -0.5f * m_height;
        t_verts[1].z = 0.0f;
        t_verts[1].t0x = 1.0f * t_texcoord_size;
        t_verts[1].t0y = 0.0f * t_texcoord_size;
        t_verts[2].x = -0.5f * m_width;
        t_verts[2].y = 0.5f * m_height;
        t_verts[2].z = 0.0f;
        t_verts[2].t0x = 0.0f * t_texcoord_size;
        t_verts[2].t0y = 1.0f * t_texcoord_size;
        t_verts[3].x = 0.5f * m_width;
        t_verts[3].y = 0.5f * m_height;
        t_verts[3].z = 0.0f;
        t_verts[3].t0x = 1.0f * t_texcoord_size;
        t_verts[3].t0y = 1.0f * t_texcoord_size;
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

void SVSpriteNode::setTexture(SV_TEXIN _textype){
    m_pTex = mApp->getTexMgr()->getInTexture(_textype);
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
//        s32 t_w = m_pTex->m_texture_dsp.m_width;
//        s32 t_h = m_pTex->m_texture_dsp.m_height;
//        setSize(t_w,t_h);
    }
}

void SVSpriteNode::update(f32 _dt) {
    SVNode::update(_dt);
    if(m_surface) {
        m_surface->setTexture( 1,0 ,m_pTex);
        FVec2 t_tex_clip = FVec2(-1.0f,1.0f);
        m_surface->setParam("texcoordClip", t_tex_clip);
        if( mApp->m_rcore == E_R_METAL_OSX || mApp->m_rcore == E_R_METAL_IOS ) {
            //metal需要转至一下矩阵
            FMat4 tt = transpose(m_localMat);
            m_surface->setParam("matModel",tt);
        }else{
            m_surface->setParam("matModel",m_localMat);
        }
    }
}

void SVSpriteNode::render() {
    if ( m_visible && m_pMesh){
        SVDispatch::dispatchMeshDraw(mApp, m_pMesh, m_mtl,m_surface,E_RSM_SOLID);
    }
    SVNode::render();
}

//序列化
void SVSpriteNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue){
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    locationObj.AddMember("spriteW", m_width, _allocator);
    locationObj.AddMember("spriteH", m_height, _allocator);
}

void SVSpriteNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item){
    _fromJsonData(item);
    m_dirty = true;
}
