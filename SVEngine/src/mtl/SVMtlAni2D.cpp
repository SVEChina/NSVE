//
// SVMtlAni2D.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMtlAni2D.h"
#include "../mtl/SVTexture.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVGL/SVRTexGL.h"

using namespace sv;

SVMtlAni2D::SVMtlAni2D(SVInstPtr _app)
:SVMtlCore(_app,"normal2dani_c") {
}

SVMtlAni2D::SVMtlAni2D(SVMtlAni2D *_mtl)
:SVMtlCore(_mtl){
}

SVMtlAni2D::~SVMtlAni2D() {
    
}

SVMtlCorePtr SVMtlAni2D::clone() {
    return PointerSharedPtr<SVMtlAni2D>(new SVMtlAni2D(this));
}

void SVMtlAni2D::reset() {
    SVMtlCore::reset();
}

void SVMtlAni2D::_submitUniform(SVRendererPtr _render) {
    SVMtlCore::_submitUniform(_render);
}

void SVMtlAni2D::setBlendMode(SVMTLBLENDMODE _blendMode){
}
