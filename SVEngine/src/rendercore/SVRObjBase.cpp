//
// SVRObjBase.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRObjBase.h"
#include "../app/SVInst.h"
#include "../base/SVDataSwap.h"

using namespace sv;

SVRObjBase::SVRObjBase(SVInstPtr _app)
:SVGBaseEx(_app)
,m_pData(nullptr){
}

SVRObjBase::~SVRObjBase(){
    m_pData = nullptr;
}

void SVRObjBase::create(SVRendererPtr _renderer){
    
}

void SVRObjBase::destroy(SVRendererPtr _renderer){
    
}

void SVRObjBase::setData(SVDataSwapPtr _pdata){
    m_pData = _pdata;
}

//处理
void SVRObjBase::process(){
}
