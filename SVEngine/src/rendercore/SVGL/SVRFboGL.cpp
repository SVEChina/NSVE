//
// SVRTarget.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRFboGL.h"
#include "SVRendererGL.h"
#include "../SVRTarget.h"

using namespace sv;

//
SVRFboGL::SVRFboGL(SVInstPtr _app)
: SVRFbo(_app) {
}

SVRFboGL::~SVRFboGL() {
}

void SVRFboGL::create(SVRendererPtr _renderer) {
    SVRFbo::create(_renderer);
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    SVRTargetPtr t_target = std::dynamic_pointer_cast<SVRTarget>(m_logic_obj);
    if(t_rm && t_target) {
        SVTargetDsp* t_dsp = t_target->getTargetDsp();
    }
}

void SVRFboGL::destroy(SVRendererPtr _renderer) {
    
    //
    SVRFbo::destroy(_renderer);
}

