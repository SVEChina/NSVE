//
// IMIOutMission.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOutMissionNor.h"

using namespace imi;

IMIOutMissionNor::IMIOutMissionNor(IMIInstPtr _app,cptr8 _name)
:IMIOutMission(_app,_name)
,m_end(false){
}

IMIOutMissionNor::~IMIOutMissionNor() {
}

void IMIOutMissionNor::output() {
    IMIOutMission::output();
}

void IMIOutMissionNor::setEnd() {
    m_end = true;
}

bool IMIOutMissionNor::isEnd() {
    return m_end;
}
