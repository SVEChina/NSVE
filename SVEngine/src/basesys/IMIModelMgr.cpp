//
// IMIModelMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIModelMgr.h"
#include "../core/IMIModel.h"
#include "../work/IMITdCore.h"
//

using namespace imi;

IMIModelMgr::IMIModelMgr(IMIInstPtr _app)
:IMISysBase(_app){
    m_lock = MakeSharedPtr<IMILock>();
}

IMIModelMgr::~IMIModelMgr() {
    m_lock = nullptr;
}

void IMIModelMgr::init(){
    
}

void IMIModelMgr::update(f32 _dt){
    _recycleUnuseModel();
}

void IMIModelMgr::destroy(){
    m_modelPool.destroy();
}

void IMIModelMgr::addModel(IMIModelPtr _model){
    if (_model) {
        if (!_hasModel(_model)) {
            m_lock->lock();
            m_modelPool.append(_model);
            m_lock->unlock();
        }
    }
}

IMIModelPtr IMIModelMgr::getModel(IMIString _name){
    IMIModelPtr model = nullptr;
    m_lock->lock();
    for (s32 i = 0; i<m_modelPool.size(); i++) {
        IMIModelPtr t_model = m_modelPool[i];
        if (strcmp(t_model->getName(), _name.c_str()) == 0) {
            model = t_model;
            break;
        }
    }
    m_lock->unlock();
    return model;
}

bool IMIModelMgr::_hasModel(IMIModelPtr _model){
    bool t_res = false;
    m_lock->lock();
    for (s32 i = 0; i<m_modelPool.size(); i++) {
        IMIModelPtr t_model = m_modelPool[i];
        if (t_model == _model) {
            t_res = true;
        }
    }
    m_lock->unlock();
    return t_res;
}

void IMIModelMgr::_recycleUnuseModel(){
    m_lock->lock();
    for(s32 i=0;i<m_modelPool.size();) {
        if(m_modelPool[i].use_count() == 1) {
            m_modelPool.remove(i);
        }else{
            i++;
        }
    }
    m_modelPool.reserveForce(m_modelPool.size());
    m_lock->unlock();
}
