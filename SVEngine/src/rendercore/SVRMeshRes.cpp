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

void SVRMeshRes::load(SVRendererPtr _renderer,
                      SVIndexStreamDspPtr _indexdsp,
                      SVVertStreamDspPtr _streamdsp,
                      SVInstStreamDspPtr _instdsp,
                      SVRMeshDsp* _SVRMeshDsp) {
    m_index_dsp = _indexdsp;
    m_vert_dsp = _streamdsp;
    m_instance_dsp = _instdsp;
    m_rmesh_dsp = _SVRMeshDsp;
}

void SVRMeshRes::unload() {
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
    if(m_instance_dsp) {
        m_instance_dsp->setStreamData(_data);
    }
    m_data_lock->unlock();
}

//
void SVRMeshRes::setIndexData(SVDataSwapPtr _data) {
    m_data_lock->lock();
    if(m_index_dsp) {
        m_index_dsp->setStreamData(_data);
    }
    m_data_lock->unlock();
}

//
void SVRMeshRes::setVertData(SVDataSwapPtr _data,s32 _chn) {
    m_data_lock->lock();
    if(m_vert_dsp) {
        //m_vert_dsp->setStreamData(<#VFTYPE _stype#>, <#SVDataSwapPtr _data#>)
    }
    m_data_lock->unlock();
}
