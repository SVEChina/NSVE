//
// SVRPath.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRPath.h"
#include "../app/SVInst.h"
#include "SVRenderMgr.h"
#include "SVGL/SVRendererGL.h"
#include "SVMetal/SVRendererMetal.h"
#include "SVVulkan/SVRendererVK.h"

using namespace sv;

//
SVRPath::SVRPath(SVInstPtr _app)
:SVGBaseEx(_app){
}

SVRPath::~SVRPath() {
}

void SVRPath::render(SVRendererPtr _renderer) {
}

