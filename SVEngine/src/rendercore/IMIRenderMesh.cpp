//
// IMIRenderMesh.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRenderMesh.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../app/IMIGlobalMgr.h"
#include "../base/IMIDataSwap.h"
#include "IMIRenderMgr.h"
#include "IMIRenderer.h"

using namespace imi;

IMIRenderMesh::IMIRenderMesh(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_id = -1;
}

IMIRenderMesh::~IMIRenderMesh() {
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_id = -1;
}

IMIRenderMeshPtr IMIRenderMesh::share() {
    return std::dynamic_pointer_cast<IMIRenderMesh>(shareObject()) ;
}

void IMIRenderMesh::dispatch() {
    IMIDispatch::dispatchMeshCreate(mApp, share());
}

void IMIRenderMesh::bindRes(s32 _instid) {
    m_rmesh_id = _instid;
}

void IMIRenderMesh::unbindRes() {
    m_rmesh_id = -1;
}

IMIRMeshResPtr IMIRenderMesh::getResBuffer() {
    if(mApp->getRenderer()) {
        return mApp->getRenderer()->getResBuf(m_rmesh_id);
    }
    return nullptr;
}

void IMIRenderMesh::setIndexDsp(IMIIndexStreamDspPtr _dsp) {
    m_index_dsp = _dsp;
}

void IMIRenderMesh::setVertDsp(IMIVertStreamDspPtr _dsp) {
    m_vert_dsp = _dsp;
}

void IMIRenderMesh::setInstanceDsp(IMIInstStreamDspPtr _dsp) {
    m_instance_dsp = _dsp;
}

bool IMIRenderMesh::useIndex() {
    if(m_index_dsp) {
        return true;
    }
    return false;
}

bool IMIRenderMesh::useInstance() {
    if(m_instance_dsp) {
        return true;
    }
    return false;
}

IMIIndexStreamDspPtr IMIRenderMesh::getIndexDsp() {
    return m_index_dsp;
}

IMIVertStreamDspPtr IMIRenderMesh::getStreamDsp() {
    return m_vert_dsp;
}

IMIInstStreamDspPtr IMIRenderMesh::getInstanceDsp() {
    return m_instance_dsp;
}

IMIRMeshDsp* IMIRenderMesh::getRMeshDsp() {
    return &m_rmesh_dsp;
}

void IMIRenderMesh::setDrawMethod(s32 _method) {
    m_rmesh_dsp.m_draw_method = _method;
}

void IMIRenderMesh::setDrawVertNum(s32 _vertexNum){
    m_rmesh_dsp.m_draw_num = _vertexNum;
}

void IMIRenderMesh::setIndexData(IMIDataSwapPtr _data,s32 _num){
    if(m_index_dsp) {
        //m_index_dsp->setInstData(_data);
        setDrawVertNum(_num);
    }
}

void IMIRenderMesh::setInstanceData(IMIDataSwapPtr _pdata, u32 _instanceCount){
    if(m_instance_dsp) {
        //m_instance_dsp->setInstData(_pdata);
    }
}

void IMIRenderMesh::setVertexData(IMIDataSwapPtr _data){
    if(m_vert_dsp) {
        //m_vert_dsp->setInstData(_pdata);
    }
}

void IMIRenderMesh::setVertexData(IMIDataSwapPtr _data,s32 _streamnum) {
    if(m_vert_dsp) {
        //m_vert_dsp->setVertData(_data, _streamnum);
    }
}
