//
// IMIProcess.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIProcess.h"

using namespace imi;

IMIProcess::IMIProcess(IMIInstPtr _app)
:IMIEventProc(_app) {
    m_subProcType = "IMIProcess";

}

IMIProcess::~IMIProcess() {
}
