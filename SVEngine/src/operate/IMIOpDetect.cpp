//
// IMIOpDetect.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpDetect.h"
#include "../app/IMIInst.h"
#include "../detect/IMIDetectMgr.h"

using namespace imi;

//
IMIOpOpenDetect::IMIOpOpenDetect(IMIInstPtr _app, s32 detecttype)
:IMIOpBase(_app) {
    m_detectType = (DETECTTYPE)detecttype;
}

void IMIOpOpenDetect::_process(float dt) {
    mApp->getDetectMgr()->init(m_detectType);
}

//
IMIOpCloseDetect::IMIOpCloseDetect(IMIInstPtr _app)
:IMIOpBase(_app) {
}

void IMIOpCloseDetect::_process(float dt) {
    mApp->getDetectMgr()->init(DETECT_T_NULL);
}
