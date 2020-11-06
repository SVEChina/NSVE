//
// IMIModuleBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIModuleBase.h"

using namespace imi;

IMIModuleBase::IMIModuleBase(IMIInstPtr _app)
:IMIEventProc(_app)
,m_isOpen(false){
    m_module_name = "";
}

IMIModuleBase::~IMIModuleBase() {
}

void IMIModuleBase::init() {
}

void IMIModuleBase::destroy() {
}

void IMIModuleBase::update(f32 _dt) {
}

void IMIModuleBase::open() {
    m_isOpen = true;
}

void IMIModuleBase::close() {
    m_isOpen = false;
}

bool IMIModuleBase::isOpen(){
    return m_isOpen;
}

void IMIModuleBase::setOpCallBack(cb_func_op _cb, void *_obj){
    m_cb = _cb;
    m_obj = _obj;
}
