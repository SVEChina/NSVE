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

using namespace sv;

SVRMeshRes::SVRMeshRes(SVInstPtr _app)
:SVRRes(_app){
    m_data_lock = MakeSharedPtr<SVLockSpin>();
    m_draw_method = E_DRAW_TRIANGLES;
    m_draw_num = 0;
}

SVRMeshRes::~SVRMeshRes(){
    m_data_lock = nullptr;
}

void SVRMeshRes::create(SVRendererPtr _renderer) {
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
void SVRMeshRes::setDrawMethod(s32 _dm) {
    m_draw_method = _dm;
}

//
void SVRMeshRes::setDrawNum(s32 _num) {
    m_draw_num = _num;
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
