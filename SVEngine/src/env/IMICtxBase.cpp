//
// IMICtxBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMICtxBase.h"

using namespace imi;

IMICtxBase::IMICtxBase(IMIInstPtr _app)
:IMIGBaseEx(_app){
}

IMICtxBase::~IMICtxBase() {
}

bool IMICtxBase::activeContext(IMIRendererPtr _renderer){
    return false;
}

bool IMICtxBase::swap(IMIRendererPtr _renderer){
    return false;
}
