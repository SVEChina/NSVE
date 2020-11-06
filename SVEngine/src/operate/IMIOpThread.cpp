//
// IMIOpThread.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpThread.h"
#include "../app/IMIInst.h"
#include "../work/IMIThread.h"
#include "../work/IMIThreadPool.h"

using namespace imi;

//
IMIOpAppMode::IMIOpAppMode(IMIInstPtr _app,IMI_STATE _mode)
: IMIOpBase(_app) {
    m_EngMode = _mode;
}

IMIOpAppMode::~IMIOpAppMode() {
}

void IMIOpAppMode::_process(f32 dt) {
//    if(mApp){
//        IMI_LOG_INFO("IMIOpAppMode set sv mode %d \n",m_EngMode);
//        mApp->setIMIMode(m_EngMode);
//    }
}
