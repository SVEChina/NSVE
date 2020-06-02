//
// SVRenderMesh.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderMesh.h"
#include "../app/SVInst.h"
#include "../app/SVGlobalMgr.h"
#include "../base/SVDataSwap.h"
#include "SVRenderMgr.h"
//
#include "SVGL/SVRendererGL.h"
#include "SVGL/SVRResGL.h"
#include "SVGL/SVResGLMesh.h"
//
#if defined(SV_IOS) || defined(SV_OSX)
#include "SVMetal/SVRendererMetal.h"
#include "SVMetal/SVResMetalMesh.h"
#endif
//
#include "SVVulkan/SVRendererVK.h"

using namespace sv;

SVRenderMesh::SVRenderMesh(SVInstPtr _app)
:SVGBaseEx(_app){
    m_created = false;
}

SVRenderMesh::~SVRenderMesh() {
    m_created = false;
}

//void SVRenderMesh::_resetMeshData(){
//    m_renderMeshData.indexNum = 0;
//    m_renderMeshData.pointNum = 0;
//    m_renderMeshData.instanceCount = 0;
//    m_renderMeshData.pDataIndex = nullptr;
//    m_renderMeshData.pDataVertex = nullptr;
//    m_renderMeshData.pDataInsOffset = nullptr;
//    m_renderMeshData.dirty = false;
//}
//
//void SVRenderMesh::_resetMeshConf(){
//    m_renderMeshConf.vftype = E_VF_V2;
//    m_renderMeshConf.seqMode = 1;
//    m_renderMeshConf.drawmethod = E_DM_TRIANGLES;
//    m_renderMeshConf.vertPoolType = GL_STATIC_DRAW;
//    m_renderMeshConf.indexPoolType = GL_STATIC_DRAW;
//    m_renderMeshConf.bVisible = true;
//    m_renderMeshConf.dirty = false;
//}

void SVRenderMesh::create(SVRendererPtr _renderer){
//    SVRendererPtr t_renderBasePtr = mApp->getRenderer();
//    SVRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<SVRendererGL>(t_renderBasePtr);
//    if (t_renderGLPtr) {
//        //渲染器类型E_RENDERER_GLES,
//        m_objVBOPtr = MakeSharedPtr<SVResGLRenderMesh>(mApp);
//    }
//    SVRendererVKPtr t_rendeVKPtr = std::dynamic_pointer_cast<SVRendererVK>(t_renderBasePtr);
//    if (t_rendeVKPtr) {
//        //渲染器类型E_RENDERER_VUNKAN,
//    }
//    #if defined(SV_IOS) || defined(SV_OSX)
//    SVRendererMetalPtr t_rendeMetalPtr = std::dynamic_pointer_cast<SVRendererMetal>(t_renderBasePtr);
//    if (t_rendeMetalPtr) {
//        //渲染器类型E_RENDERER_METAL
//        m_objVBOPtr = MakeSharedPtr<SVResMetalRenderMesh>(mApp);
//    }
//    #endif
//    if (m_objVBOPtr) {
//        _updateData();
//        m_objVBOPtr->create(_renderer);
//    }
}

void SVRenderMesh::destroy(SVRendererPtr _renderer) {
}

void SVRenderMesh::setIndexPoolType(u32 itype) {
}

void SVRenderMesh::setVertexPoolType(u32 vtype) {
}

void SVRenderMesh::setDrawMethod(DRAWMETHOD drawtype) {
}

void SVRenderMesh::setSeqMode(s32 _mode) {
}

void SVRenderMesh::setVertexType(VFTYPE type,s32 _channel) {
}

void SVRenderMesh::setVertNum(s32 _vertexNum){
}

void SVRenderMesh::setIndexData(SVDataSwapPtr _data,s32 _num){
}

void SVRenderMesh::setVertexData(SVDataSwapPtr _data,s32 _channel,VFTYPE type){
}

void SVRenderMesh::setInstanceOffsetData(SVDataSwapPtr _pdata, u32 _instanceCount){
//    if (_pdata) {
//        m_renderMeshData.pDataInsOffset = _pdata;
//        m_renderMeshData.instanceCount = _instanceCount;
//        m_renderMeshData.dirty = true;
//    }
}

void SVRenderMesh::createMesh(){
//    if (!m_created) {
//        m_created = true;
//        mApp->getRenderMgr()->pushRCmdCreate(THIS_TO_SHAREPTR(SVRenderMesh));
//    }
}

void SVRenderMesh::render(SVRendererPtr _renderer) {
}
