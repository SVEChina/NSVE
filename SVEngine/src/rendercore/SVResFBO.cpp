//
// SVResFBO.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVResFBO.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVRenderer.h"

SVResFBO::SVResFBO(SVInst* _app)
:SVRObjBase(_app){
    m_uid = mApp->m_IDPool.applyUID();
}

SVResFBO:: ~SVResFBO(){
    mApp->m_IDPool.returnUID(m_uid);
}

void SVResFBO::create(render::SVRendererPtr _renderer){
    
}

void SVResFBO::destroy(render::SVRendererPtr _renderer){
    
}

