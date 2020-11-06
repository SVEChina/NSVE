//
// IMISysBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMISysBase.h"

using namespace imi;

IMISysBase::IMISysBase(IMIInstPtr _app)
:IMIEventProc(_app) {
    m_subsysType = 0;
}

IMISysBase::~IMISysBase() {
}

