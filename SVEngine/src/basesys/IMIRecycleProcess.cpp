//
// IMIRecycleProcess.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRecycleProcess.h"
#include "../app/IMIInst.h"
#include "../event/IMIEventMgr.h"
#include "../event/IMIEvent.h"

using namespace imi;

IMIRecycleProcess::IMIRecycleProcess(IMIInstPtr _app)
:IMIProcess(_app) {
}

IMIRecycleProcess::~IMIRecycleProcess() {
}

void IMIRecycleProcess::update(f32 _dt){
    
}

bool IMIRecycleProcess::procEvent(IMIEventPtr _event){
    IMIvtRecyclePtr t_event = DYN_TO_SHAREPTR(IMIvtRecycle,_event);
    if(t_event && t_event->m_obj){
        t_event->m_obj = nullptr;
        return false;
    }
    return true;
}
