//
// SVRBufferGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRBufferGL.h"
#include "SVRendererGL.h"
#include "../SVRenderMesh.h"

using namespace sv;

SVRBufferGL::SVRBufferGL(SVInstPtr _app)
:SVRBuffer(_app){
}

SVRBufferGL::~SVRBufferGL() {
}

void SVRBufferGL::create(SVRendererPtr _renderer) {
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    SVRenderMeshPtr t_rendermesh = std::dynamic_pointer_cast<SVRenderMesh>(m_logic_obj);
    if(t_rm && t_rendermesh) {
        m_exist = true;
    }
}

void SVRBufferGL::destroy(SVRendererPtr _renderer) {

}
//
//void SVRBufferGL::create(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh){
//
//}
//
//void SVRBufferGL::render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh){
//
//}
//
//void SVRBufferGL::destroy(SVRendererPtr _renderer,SVRTargetPtr _target) {
//
//}

