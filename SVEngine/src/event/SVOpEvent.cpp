//
// SVOpEvent.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVOpEvent.h"
#include "../base/SVDataSwap.h"

using namespace sv;

SVTouchEvent::SVTouchEvent() {
    x = 0;
    y = 0;
}

SVTouchWorldEvent::SVTouchWorldEvent() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

SVPickEvent::SVPickEvent() {
    colorid = 0;
}

SVCameraOrenEvent::SVCameraOrenEvent() {
    yaw = 0;
    pitch = 0;
    roll = 0;
}

SVCameraMatrixEvent::SVCameraMatrixEvent() {
    m_matData = MakeSharedPtr<SVDataSwap>();
}

SVCameraMatrixEvent::~SVCameraMatrixEvent(){
    m_matData = nullptr;
}

SVProjectMatrixEvent::SVProjectMatrixEvent() {
    m_matData = MakeSharedPtr<SVDataSwap>();
}

SVProjectMatrixEvent::~SVProjectMatrixEvent(){
    m_matData = nullptr;
}

SVCameraPosEvent::SVCameraPosEvent() {
    m_px = 0.0f;
    m_py = 0.0f;
    m_pz = 0.0f;
}

SVCameraDirEvent::SVCameraDirEvent() {
    m_dx = 0.0f;
    m_dx = 0.0f;
    m_dx = 0.0f;
}

SVReactEvent::SVReactEvent(){
    m_actAniName = "";
    m_actAniLoop = 0;
}

bool SVReactEvent::isEqual(SVEventPtr _event) {
    bool t_flag = true;
//    SVReactEvent *tempEvent = dynamic_cast<SVReactEvent *>(_event);
//    if (!tempEvent || eventName != tempEvent->eventName)
//        t_flag = false;
    if (eventName != _event->eventName)
        t_flag = false;
    return t_flag;
}
