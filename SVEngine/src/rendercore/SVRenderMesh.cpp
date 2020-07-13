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

bool SVRenderMesh::useIndex() {
    return m_use_index;
}

BufferDsp* SVRenderMesh::getIndexDsp() {
    return &m_index_dsp;
}

s32 SVRenderMesh::getStreamNum() {
    return 0;
}

BufferDsp* SVRenderMesh::getStreamDsp(s32 _index) {
    if(_index<m_vert_dsp.size())
        return &m_vert_dsp[_index];
    return nullptr;
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
}

void SVRenderMesh::createMesh(){
}

void SVRenderMesh::render(SVRendererPtr _renderer) {
}
