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
,m_exist(false){
}

SVRRes::~SVRRes(){
}
