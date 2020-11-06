//
// IMIOutMission.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOutMission.h"

using namespace imi;

IMIOutMission::IMIOutMission(IMIInstPtr _app,cptr8 _name)
:IMIEventProc(_app)
,m_name(_name)
,m_pOutStreamStateCB(nullptr){
}

IMIOutMission::~IMIOutMission() {
    m_pOutStreamStateCB = nullptr;
}

cptr8 IMIOutMission::getMissionName() {
    return m_name.c_str();
}

void IMIOutMission::output(){
    if(m_pOutStreamStateCB) {
        (*m_pOutStreamStateCB)(E_MS_RUN);
    }
}

void IMIOutMission::sendEnd() {
    if(m_pOutStreamStateCB) {
        (*m_pOutStreamStateCB)(E_MS_END);
    }
}

bool IMIOutMission::isEnd() {
    return true;
}
