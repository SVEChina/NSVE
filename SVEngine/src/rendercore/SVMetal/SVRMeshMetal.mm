//
// SVRMeshMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMeshMetal.h"

using namespace sv;

SVRMeshMetal::SVRMeshMetal(SVInstPtr _app)
:SVRMesh(_app){
}

SVRMeshMetal::~SVRMeshMetal() {
}

void SVRMeshMetal::create(SVRendererPtr _renderer) {
    
}

void SVRMeshMetal::render(SVRendererPtr _renderer) {
    
}

//MTLVertexDescriptor _unityVertexDescriptor = [[MTLVertexDescriptor alloc] init];
//    
//    // Positions.
//    _unityVertexDescriptor.attributes[0].format = MTLVertexFormatFloat2;
//    _unityVertexDescriptor.attributes[0].offset = 0;
//    _unityVertexDescriptor.attributes[0].bufferIndex = 0;
//    
//    // Texture coordinates.
//    _unityVertexDescriptor.attributes[1].format = MTLVertexFormatFloat2;
//    _unityVertexDescriptor.attributes[1].offset = 0;
//    _unityVertexDescriptor.attributes[1].bufferIndex = 0;
//
//    // Position Buffer Layout
//    _unityVertexDescriptor.layouts[0].stride = 8;
//    _unityVertexDescriptor.layouts[0].stepRate = 1;
//    _unityVertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
//    
//    _unityVertexDescriptor.layouts[1].stride = 8;
//    _unityVertexDescriptor.layouts[1].stepRate = 1;
//    _unityVertexDescriptor.layouts[1].stepFunction = MTLVertexStepFunctionPerVe

