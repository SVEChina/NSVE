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
#include "SVRenderer.h"

using namespace sv;

SVRenderMesh::SVRenderMesh(SVInstPtr _app)
:SVGBaseEx(_app){
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_id = -1;
}

SVRenderMesh::~SVRenderMesh() {
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_id = -1;
}

void SVRenderMesh::bindRes(s32 _instid) {
    m_rmesh_id = _instid;
}

void SVRenderMesh::unbindRes() {
    m_rmesh_id = -1;
}

SVRMeshResPtr SVRenderMesh::getResBuffer() {
    if(mApp->getRenderer()) {
        return mApp->getRenderer()->getResBuf(m_rmesh_id);
    }
    return nullptr;
}

void SVRenderMesh::setIndexDsp(SVIndexStreamDspPtr _dsp) {
    m_index_dsp = _dsp;
}

void SVRenderMesh::setVertDsp(SVVertStreamDspPtr _dsp) {
    m_vert_dsp = _dsp;
}

void SVRenderMesh::setInstanceDsp(SVInstStreamDspPtr _dsp) {
    m_instance_dsp = _dsp;
}

bool SVRenderMesh::useIndex() {
    if(m_index_dsp) {
        return true;
    }
    return false;
}

bool SVRenderMesh::useInstance() {
    if(m_instance_dsp) {
        return true;
    }
    return false;
}

SVIndexStreamDspPtr SVRenderMesh::getIndexDsp() {
    return m_index_dsp;
}

SVVertStreamDspPtr SVRenderMesh::getStreamDsp() {
    return m_vert_dsp;
}

SVInstStreamDspPtr SVRenderMesh::getInstanceDsp() {
    return m_instance_dsp;
}

SVRMeshDsp* SVRenderMesh::getRMeshDsp() {
    return &m_rmesh_dsp;
}

void SVRenderMesh::setDrawMethod(s32 _method) {
    m_rmesh_dsp.m_draw_method = _method;
}

void SVRenderMesh::setDrawVertNum(s32 _vertexNum){
    m_rmesh_dsp.m_draw_num = _vertexNum;
}

void SVRenderMesh::setIndexData(SVDataSwapPtr _data,s32 _num){
    if(m_index_dsp) {
        //m_index_dsp->setInstData(_data);
        setDrawVertNum(_num);
    }
}

void SVRenderMesh::setInstanceData(SVDataSwapPtr _pdata, u32 _instanceCount){
    if(m_instance_dsp) {
        //m_instance_dsp->setInstData(_pdata);
    }
}

void SVRenderMesh::setVertexData(SVDataSwapPtr _data){
    if(m_vert_dsp) {
        //m_vert_dsp->setInstData(_pdata);
    }
}

void SVRenderMesh::setVertexData(SVDataSwapPtr _data,s32 _streamnum) {
    if(m_vert_dsp) {
        //m_vert_dsp->setVertData(_data, _streamnum);
    }
}
