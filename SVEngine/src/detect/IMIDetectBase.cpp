//
// IMIDetectBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIDetectBase.h"
#include "IMIPerson.h"

using namespace imi;

IMIDetectBase::IMIDetectBase(IMIInstPtr _app)
:IMIListenBase(_app) {
}

IMIDetectBase::~IMIDetectBase() {
}

void IMIDetectBase::update(f32 _dt){
}

void IMIDetectBase::pushData(void *_faceData){
}

s32 IMIDetectBase::transformIndex(s32 index) {
    return 0;
}

BINDREGION IMIDetectBase::getIndexRegion(s32 index) {
    return BD_REGION_CENTER;
}

