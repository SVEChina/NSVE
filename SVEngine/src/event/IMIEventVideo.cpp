//
// IMIEventVideo.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIEventVideo.h"

using namespace imi;

IMIEventVideoCtrl::IMIEventVideoCtrl() {
    eventType = EVN_T_VIDEO_CTRL;
    ctrlmode = VIDEO_CTRL_NONE;
}

IMIEventVideoStatus::IMIEventVideoStatus() {
    eventType = EVN_T_VIDEO_STATE;
    state = VIDEO_STATE_NONE;
}

//
IMIEventMixBegin::IMIEventMixBegin() {
    eventType = EVN_T_SAVE_BEGIN;
}

//
IMIEventMixEnd::IMIEventMixEnd() {
    eventType = EVN_T_SAVE_END;
}
