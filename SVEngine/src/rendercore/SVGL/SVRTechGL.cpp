//
// SVRTechGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTechGL.h"
#include "SVRendererGL.h"

using namespace sv;

SVRTechGL::SVRTechGL(SVInstPtr _app)
:SVRTech(_app){
}

SVRTechGL::~SVRTechGL() {
}

void SVRTechGL::render(SVRendererPtr _renderer) {
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    //shader 绑定
    
    //状态切换
    
    //
    
}
