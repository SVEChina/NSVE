//
// SVRRes.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRRes.h"
#include "../app/SVInst.h"
#include "../base/SVDataSwap.h"

using namespace sv;

SVRRes::SVRRes(SVInstPtr _app)
:SVGBaseEx(_app)
,m_logic_obj(nullptr)
,m_exist(false){
}

SVRRes::~SVRRes(){
    m_logic_obj = nullptr;
}

void SVRRes::create(SVRendererPtr _renderer){
}

void SVRRes::destroy(SVRendererPtr _renderer){
}
