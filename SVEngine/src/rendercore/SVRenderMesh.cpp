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

using namespace sv;

void SVRenderMesh::buildBufferDsp(BUFFERTYPE _buftype,s32 _vertCnt,BufferDspPtr _dsp) {
    if(_dsp) {
        _dsp->_bufType = _buftype;
        _dsp->_vertCnt = _vertCnt;
        _dsp->_bufSize = _vertCnt * BufferDsp::getVertSize(_dsp->getVertType());
    }
}

SVRenderMesh::SVRenderMesh(SVInstPtr _app)
:SVGBaseEx(_app){
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_res_buffer = nullptr;
    m_use_index = false;
    m_use_instance = false;
}

SVRenderMesh::~SVRenderMesh() {
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_res_buffer = nullptr;
    m_use_index = false;
    m_use_instance = false;
}

void SVRenderMesh::bindRes(SVRMeshResPtr _res) {
    m_res_buffer = _res;
}

void SVRenderMesh::unbindRes() {
    m_res_buffer = nullptr;
}

SVRMeshResPtr SVRenderMesh::getResBuffer() {
    return m_res_buffer;
}

//
void SVRenderMesh::setIndexDsp(BufferDspPtr _dsp) {
    m_use_index = true;
    m_index_dsp = _dsp;
}

//
void SVRenderMesh::setVertDsp(BufferDspPtr _dsp) {
    m_vert_dsp = _dsp;
}

//
void SVRenderMesh::setInstanceDsp(BufferDspPtr _dsp) {
    m_use_instance = true;
    m_instance_dsp = _dsp;
}

bool SVRenderMesh::useIndex() {
    return m_use_index;
}

BufferDspPtr SVRenderMesh::getIndexDsp() {
    return m_index_dsp;
}

s32 SVRenderMesh::getStreamNum() {
    return 0;
}

BufferDspPtr SVRenderMesh::getStreamDsp() {
    return m_vert_dsp;
}

bool SVRenderMesh::useInstance() {
    return m_use_instance;
}

BufferDspPtr SVRenderMesh::getInstanceDsp() {
    return m_instance_dsp;
}

void SVRenderMesh::setDrawMethod(s32 _method) {
    m_draw_method = _method;
}

void SVRenderMesh::setVertNum(s32 _vertexNum){
}

void SVRenderMesh::setIndexData(SVDataSwapPtr _data,s32 _num){
//    if(m_use_index) {
//    }
}

void SVRenderMesh::setInstanceData(SVDataSwapPtr _pdata, u32 _instanceCount){
    if(m_use_instance) {
        //
        
    }
}

void SVRenderMesh::setVertexData(SVDataSwapPtr _data){
    //更改混合流数据
    
}

void SVRenderMesh::setVertexData(SVDataSwapPtr _data,s32 _streamtype) {
    //更改目标流数据
    
}

