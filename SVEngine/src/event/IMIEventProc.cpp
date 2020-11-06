//
// IMIEventProc.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIEventProc.h"
#include "IMIEventMgr.h"
#include "../app/IMIInst.h"

using namespace imi;

IMIEventProc::IMIEventProc(IMIInstPtr _app)
:IMIGBaseEx(_app) {
}

IMIEventProc::~IMIEventProc() {
}

void IMIEventProc::startListen(){
    mApp->getEventMgr()->registProcer(THIS_TO_SHAREPTR(IMIEventProc));
}

void IMIEventProc::stopListen(){
    mApp->getEventMgr()->unregistProcer(THIS_TO_SHAREPTR(IMIEventProc));
}

//返回true 表示消息继续传递 否者 表示消息不在传递
bool IMIEventProc::procEvent(IMIEventPtr _event) {
    return true;
}
