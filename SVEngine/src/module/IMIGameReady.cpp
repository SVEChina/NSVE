//
// IMIGameReady.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIGameReady.h"

using namespace imi;

IMIGameReady::IMIGameReady(IMIInstPtr _app)
:IMIGamePart(_app) {
}

IMIGameReady::~IMIGameReady() {
}

void IMIGameReady::init() {
}

void IMIGameReady::destroy() {
}

void IMIGameReady::update(f32 _dt) {
    
}

bool IMIGameReady::isEnd(){
    return true;
}
