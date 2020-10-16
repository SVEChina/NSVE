//
// SVRMeshRes.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMeshRes.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVRenderer.h"
#include "SVRenderMesh.h"

using namespace sv;

SVRMeshRes::SVRMeshRes(SVInstPtr _app)
:SVRRes(_app){
    m_data_lock = MakeSharedPtr<SVLockSpin>();
//    m_draw_method = E_DRAW_TRIANGLES;
//    m_draw_num = 0;
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_dsp = nullptr;
}

SVRMeshRes::~SVRMeshRes(){
    m_data_lock = nullptr;
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_dsp = nullptr;
}

void SVRMeshRes::create(SVRendererPtr _renderer,
                        SVBufferDspPtr _indexdsp,
                        SVBufferDspPtr _streamdsp,
                        SVBufferDspPtr _instdsp,
                        SVRMeshDsp* _SVRMeshDsp) {
    m_index_dsp = _indexdsp;
    m_vert_dsp = _streamdsp;
    m_instance_dsp = _instdsp;
    m_rmesh_dsp = _SVRMeshDsp;
}

void SVRMeshRes::destroy(SVRendererPtr _renderer) {
}

s32 SVRMeshRes::process(SVRendererPtr _renderer) {
    return -1;
}

void SVRMeshRes::draw(SVRendererPtr _renderer) {
    return ;
}

//
void SVRMeshRes::setInstData(SVDataSwapPtr _data) {
    m_data_lock->lock();
    m_inst = _data;
    m_data_lock->unlock();
}

//
void SVRMeshRes::setIndexData(SVDataSwapPtr _data) {
    m_data_lock->lock();
    m_index = _data;
    m_data_lock->unlock();
}

//
void SVRMeshRes::setVertData(SVDataSwapPtr _data,s32 _chn) {
    m_data_lock->lock();
    InVertDataUp t_up;
    t_up._chn = _chn;
    t_up._data = _data;
    m_verts.push_back(t_up);
    m_data_lock->unlock();
}
