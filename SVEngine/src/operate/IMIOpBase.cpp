//
// IMIOpBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpBase.h"
#include "../app/IMIInst.h"

using namespace imi;

IMIOpBase::IMIOpBase(IMIInstPtr _app)
:IMIGBaseEx(_app)
,m_pCB(nullptr){
}

IMIOpBase::~IMIOpBase() {
}

void IMIOpBase::setCallBack(cb_func_op _cb, void* _obj, cptr8 _info){
    m_pCB = _cb;
    m_obj = _obj;
    m_info = _info;
}

void IMIOpBase::process(f32 dt) {
    _process(dt);
    if(m_pCB){
        (*m_pCB)(m_info.c_str(), m_obj);
    }
}

void IMIOpBase::_process(f32 dt){
}


