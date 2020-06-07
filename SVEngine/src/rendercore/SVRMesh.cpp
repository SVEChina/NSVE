//
// SVRMesh.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMesh.h"

using namespace sv;

SVRMesh::SVRMesh(SVInstPtr _app)
:SVGBaseEx(_app){
    m_create = false;
    m_destroy = false;
}

SVRMesh::~SVRMesh() {
}
