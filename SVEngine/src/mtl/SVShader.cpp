//
// SVShader.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVShader.h"
#include "../rendercore/SVRShader.h"
#include "../app/SVInst.h"

using namespace sv;

SVShader::SVShader(SVInstPtr _app)
:SVGBaseEx(_app)
,m_res_shader(nullptr){
}

SVShader::~SVShader() {
    m_res_shader = nullptr;
}

//渲染内核
void SVShader::bindRes(SVRShaderPtr _res) {
    m_res_shader = _res;
}

void SVShader::unbindRes() {
    m_res_shader = nullptr;
}

SVRShaderPtr SVShader::getResShader() {
    return m_res_shader;
}
