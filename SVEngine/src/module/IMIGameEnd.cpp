//
// IMIGameEnd.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIGameEnd.h"

using namespace imi;

IMIGameEnd::IMIGameEnd(IMIInstPtr _app)
:IMIGamePart(_app) {
}

IMIGameEnd::~IMIGameEnd() {
}

void IMIGameEnd::init() {
}

void IMIGameEnd::destroy() {
}

void IMIGameEnd::update(f32 _dt) {
}

bool IMIGameEnd::isEnd(){
    return true;
}
