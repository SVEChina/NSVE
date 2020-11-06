//
// IMIRFbo.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRFbo.h"
#include "../app/IMIInst.h"
#include "../work/IMITdCore.h"
#include "IMIRenderer.h"

using namespace imi;

IMIRFbo::IMIRFbo(IMIInstPtr _app)
:IMIRRes(_app)
,m_fbo_dsp(nullptr) {
}

IMIRFbo:: ~IMIRFbo(){
    m_fbo_dsp = nullptr;
}
