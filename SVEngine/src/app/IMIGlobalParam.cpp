//
// IMIGlobalParam.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIGlobalParam.h"

using namespace imi;

IMIGlobalParam::IMIGlobalParam(){
    sv_width = 720;
    sv_height = 1280;
    setSeed(0);
}

IMIGlobalParam::~IMIGlobalParam() {
    clear();
}

void IMIGlobalParam::clear() {
    sv_width = 720;
    sv_height = 1280;
}

void IMIGlobalParam::setSeed(u32 seed) {
    //AtomicLock atomic(&lock);
    m_random.setSeed(seed);
}

u32 IMIGlobalParam::getSeed() const {
    return m_random.getSeed();
}

u32 IMIGlobalParam::getRandom() {
    //AtomicLock atomic(&lock);
    return m_random.get();
}

s32 IMIGlobalParam::getRandomInt(s32 from,s32 to) {
    //AtomicLock atomic(&lock);
    return m_random.getInt(from,to);
}

f32 IMIGlobalParam::getRandomFloat(f32 from,f32 to) {
    //AtomicLock atomic(&lock);
    return m_random.getFloat(from,to);
}

double IMIGlobalParam::getRandomDouble(double from,double to) {
    //AtomicLock atomic(&lock);
    return m_random.getDouble(from,to);
}
