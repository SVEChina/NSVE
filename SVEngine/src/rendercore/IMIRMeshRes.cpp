//
// IMIRMeshRes.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRMeshRes.h"
#include "../app/IMIInst.h"
#include "../work/IMITdCore.h"
#include "IMIRenderer.h"
#include "IMIRenderMesh.h"

using namespace imi;

IMIRMeshRes::IMIRMeshRes(IMIInstPtr _app)
:IMIRRes(_app){
    m_data_lock = MakeSharedPtr<IMILockSpin>();
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_dsp = nullptr;
}

IMIRMeshRes::~IMIRMeshRes(){
    m_data_lock = nullptr;
    m_index_dsp = nullptr;
    m_vert_dsp = nullptr;
    m_instance_dsp = nullptr;
    m_rmesh_dsp = nullptr;
}

void IMIRMeshRes::load(IMIRendererPtr _renderer,
                      IMIIndexStreamDspPtr _indexdsp,
                      IMIVertStreamDspPtr _streamdsp,
                      IMIInstStreamDspPtr _instdsp,
                      IMIRMeshDsp* _IMIRMeshDsp) {
    m_index_dsp = _indexdsp;
    m_vert_dsp = _streamdsp;
    m_instance_dsp = _instdsp;
    m_rmesh_dsp = _IMIRMeshDsp;
}

void IMIRMeshRes::unload() {
}

s32 IMIRMeshRes::process(IMIRendererPtr _renderer) {
    return -1;
}

void IMIRMeshRes::draw(IMIRendererPtr _renderer) {
    return ;
}

//
void IMIRMeshRes::setInstData(IMIDataSwapPtr _data) {
    m_data_lock->lock();
    if(m_instance_dsp) {
        m_instance_dsp->setStreamData(_data);
    }
    m_data_lock->unlock();
}

//
void IMIRMeshRes::setIndexData(IMIDataSwapPtr _data) {
    m_data_lock->lock();
    if(m_index_dsp) {
        m_index_dsp->setStreamData(_data);
    }
    m_data_lock->unlock();
}

//
void IMIRMeshRes::setVertData(IMIDataSwapPtr _data,s32 _chn) {
    m_data_lock->lock();
    if(m_vert_dsp) {
        //m_vert_dsp->setStreamData(<#VFTYPE _stype#>, <#IMIDataSwapPtr _data#>)
    }
    m_data_lock->unlock();
}
