//
// SVRFbo.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRFbo.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVRenderer.h"

using namespace sv;

SVRFbo::SVRFbo(SVInstPtr _app)
:SVRRes(_app)
,m_width(1)
,m_height(1)
,m_target_num(1){
}

SVRFbo:: ~SVRFbo(){
}
