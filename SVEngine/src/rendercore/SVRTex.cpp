//
// SVRTex.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTex.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVRenderer.h"

using namespace sv;

SVRTex::SVRTex(SVInstPtr _app)
:SVRRes(_app){
    m_texLock = MakeSharedPtr<SVLockSpin>();
}

SVRTex:: ~SVRTex(){
    m_texLock = nullptr;
}

void SVRTex::create(SVRendererPtr _renderer){
}

void SVRTex::destroy(SVRendererPtr _renderer){
}

void SVRTex::setTexData(SVDataSwapPtr _data){
}

void SVRTex::commit(){
}
