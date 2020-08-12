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
,m_target_num(1)
,m_use_depth(false)
,m_use_stencil(false){
}

SVRFbo:: ~SVRFbo(){
}
