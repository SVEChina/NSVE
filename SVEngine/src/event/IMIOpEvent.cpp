//
// IMIOpEvent.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpEvent.h"
#include "../base/IMIDataSwap.h"

using namespace imi;

IMITouchEvent::IMITouchEvent() {
    x = 0;
    y = 0;
}

IMITouchWorldEvent::IMITouchWorldEvent() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

IMIPickEvent::IMIPickEvent() {
    colorid = 0;
}

IMICameraOrenEvent::IMICameraOrenEvent() {
    yaw = 0;
    pitch = 0;
    roll = 0;
}

IMICameraMatrixEvent::IMICameraMatrixEvent() {
    m_matData = MakeSharedPtr<IMIDataSwap>();
}

IMICameraMatrixEvent::~IMICameraMatrixEvent(){
    m_matData = nullptr;
}

IMIProjectMatrixEvent::IMIProjectMatrixEvent() {
    m_matData = MakeSharedPtr<IMIDataSwap>();
}

IMIProjectMatrixEvent::~IMIProjectMatrixEvent(){
    m_matData = nullptr;
}

IMICameraPosEvent::IMICameraPosEvent() {
    m_px = 0.0f;
    m_py = 0.0f;
    m_pz = 0.0f;
}

IMICameraDirEvent::IMICameraDirEvent() {
    m_dx = 0.0f;
    m_dx = 0.0f;
    m_dx = 0.0f;
}

IMIReactEvent::IMIReactEvent(){
    m_actAniName = "";
    m_actAniLoop = 0;
}

bool IMIReactEvent::isEqual(IMIEventPtr _event) {
    bool t_flag = true;
//    IMIReactEvent *tempEvent = dynamic_cast<IMIReactEvent *>(_event);
//    if (!tempEvent || eventName != tempEvent->eventName)
//        t_flag = false;
    if (eventName != _event->eventName)
        t_flag = false;
    return t_flag;
}
