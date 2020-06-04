//
// SVRPath.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRPath.h"
#include "../app/SVInst.h"

using namespace sv;

//普通的path
SVRPathNor::SVRPathNor(SVInstPtr _app)
:SVRPath(_app){
    
}

SVRPathNor::~SVRPathNor() {
    
}

void SVRPathNor::init() {
    //设定两个流，固体和透明
    
}

//前向渲染
void SVRPathNor::render(f32 _dt) {
    SV_LOG_INFO("render path");
    //1 gpu例子
    
    //2 pre-z
    
    //3 逐实体渲染
    
    //4 后处理
}



//
SVRPathDef::SVRPathDef(SVInstPtr _app)
:SVRPath(_app){
    
}

SVRPathDef::~SVRPathDef() {
    
}

void SVRPathDef::init() {
    
}

void SVRPathDef::render(f32 _dt) {
    //1 gpu例子
    
    //2 pre-z
    
    //3 逐实体渲染
    
    //4 后处理
}
