//
// SVGlobalParam.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVGlobalParam.h"

using namespace sv;

SVGlobalParam::SVGlobalParam(){
    sv_width = 720;
    sv_height = 1280;
    setSeed(0);
}

SVGlobalParam::~SVGlobalParam() {
    clear();
}

void SVGlobalParam::clear() {
    sv_width = 720;
    sv_height = 1280;
}

void SVGlobalParam::setSeed(u32 seed) {
    //AtomicLock atomic(&lock);
    m_random.setSeed(seed);
}

u32 SVGlobalParam::getSeed() const {
    return m_random.getSeed();
}

u32 SVGlobalParam::getRandom() {
    //AtomicLock atomic(&lock);
    return m_random.get();
}

s32 SVGlobalParam::getRandomInt(s32 from,s32 to) {
    //AtomicLock atomic(&lock);
    return m_random.getInt(from,to);
}

f32 SVGlobalParam::getRandomFloat(f32 from,f32 to) {
    //AtomicLock atomic(&lock);
    return m_random.getFloat(from,to);
}

double SVGlobalParam::getRandomDouble(double from,double to) {
    //AtomicLock atomic(&lock);
    return m_random.getDouble(from,to);
}
