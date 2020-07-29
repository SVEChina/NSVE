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

void SVRenderMesh::buildBufferDsp(VFTYPE _vertype,BUFFERTYPE _buftype,s32 _vertCnt,s32 _bufsize,void* _data,BufferDsp* _dsp) {
    if(_dsp) {
        _dsp->_bufVertDsp = _vertype;
        _dsp->_bufType = _buftype;
        _dsp->_vertCnt = _vertCnt;
        _dsp->_bufSize = _bufsize;
        _dsp->_bufData = nullptr;
        if(_data) {
            _dsp->_bufData = MakeSharedPtr<SVDataSwap>();
            _dsp->_bufData->appendData(_data, _bufsize);
        }
    }
}

SVRenderMesh::SVRenderMesh(SVInstPtr _app)
:SVGBaseEx(_app){
    m_res_buffer = nullptr;
    m_use_index = false;
    m_use_instance = false;
}

SVRenderMesh::~SVRenderMesh() {
    m_res_buffer = nullptr;
    m_use_index = false;
    m_use_instance = false;
}

void SVRenderMesh::bindRes(SVRBufferPtr _res) {
    m_res_buffer = _res;
}

void SVRenderMesh::unbindRes() {
    m_res_buffer = nullptr;
}

SVRBufferPtr SVRenderMesh::getResBuffer() {
    return m_res_buffer;
}

//
void SVRenderMesh::setIndexDsp(BufferDsp& _dsp) {
    m_use_index = true;
    m_index_dsp = _dsp;
}

//
void SVRenderMesh::setVertDsp(BufferDsp& _dsp) {
    m_vert_dsp = _dsp;
}

//
void SVRenderMesh::setInstanceDsp(BufferDsp& _dsp) {
    m_use_instance = true;
    m_instance_dsp = _dsp;
}

bool SVRenderMesh::useIndex() {
    return m_use_index;
}

BufferDsp* SVRenderMesh::getIndexDsp() {
    return &m_index_dsp;
}

s32 SVRenderMesh::getStreamNum() {
    return 0;
}

BufferDsp* SVRenderMesh::getStreamDsp() {
    return &m_vert_dsp;
}

bool SVRenderMesh::useInstance() {
    return m_use_instance;
}

BufferDsp* SVRenderMesh::getInstanceDsp() {
    return &m_instance_dsp;
}

//
void SVRenderMesh::create(SVRendererPtr _renderer){
}

void SVRenderMesh::destroy(SVRendererPtr _renderer) {
}

void SVRenderMesh::render(SVRendererPtr _renderer) {
    if(m_res_buffer) {
        m_res_buffer->process(_renderer);
    }
}

void SVRenderMesh::setDrawMethod(DRAWMETHOD drawtype) {
}

void SVRenderMesh::setVertNum(s32 _vertexNum){
}

void SVRenderMesh::setIndexData(SVDataSwapPtr _data,s32 _num){
}

void SVRenderMesh::setVertexData(SVDataSwapPtr _data,s32 _channel,VFTYPE type){
}

void SVRenderMesh::setInstanceData(SVDataSwapPtr _pdata, u32 _instanceCount){
}


