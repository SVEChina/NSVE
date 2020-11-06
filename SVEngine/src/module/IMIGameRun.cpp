//
// IMIGameRun.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIGameRun.h"

using namespace imi;

IMIGameRun::IMIGameRun(IMIInstPtr _app)
:IMIGamePart(_app) {
}

IMIGameRun::~IMIGameRun() {
}

void IMIGameRun::init() {
}

void IMIGameRun::destroy() {
}

void IMIGameRun::update(f32 _dt) {
    
}

bool IMIGameRun::isEnd(){
    return true;
}
