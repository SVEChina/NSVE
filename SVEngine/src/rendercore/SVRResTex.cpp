//
// SVRResTex.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRResTex.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVRenderer.h"

using namespace sv;

SVRResTex::SVRResTex(SVInstPtr _app)
:SVRRes(_app){
    m_texLock = MakeSharedPtr<SVLock>();
}

SVRResTex:: ~SVRResTex(){
    m_texLock = nullptr;
}

void SVRResTex::create(SVRendererPtr _renderer){
    
}

void SVRResTex::destroy(SVRendererPtr _renderer){
    
}

void SVRResTex::setTexData(void *_data, s32 _len){
    
}

void SVRResTex::commit(){
    
}
