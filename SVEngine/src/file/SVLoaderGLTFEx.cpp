//
// SVLoaderGLTFEx.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVLoaderGLTFEx.h"
#include "SVFileMgr.h"
#include "../app/SVInst.h"
#include "../file/SVParseDef.h"
#include "../file/SVFileMgr.h"

#include "../base/SVDataChunk.h"
#include "../base/SVDataSwap.h"
#include "../base/SVQuat.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtl3D.h"
#include "../mtl/SVMtlGLTF.h"
#include "../rendercore/SVRenderMesh.h"
#include "../node/SVSkinNode.h"
#include "../node/SVModelNode.h"
#include "../node/SVMorphNode.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVSceneMgr.h"
#include "../core/SVModel.h"
#include "../core/SVMesh3d.h"
#include "../core/SVModel.h"
#include "../core/SVAnimateSkin.h"
#include "../core/SVAnimateMorph.h"
#include "../base/SVMap.h"
#include "../base/SVArray.h"
#include "../base/svstr.h"
#include "../basesys/SVModelMgr.h"
#include "../rendercore/SVRMeshRes.h"

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "../third/gltf/tiny_gltf.h"

using namespace sv;

SVLoaderGLTFEx::SVLoaderGLTFEx(SVInstPtr _app)
:SVGBaseEx(_app) {
}

SVLoaderGLTFEx::~SVLoaderGLTFEx() {
}

bool SVLoaderGLTFEx::loadFromFile(SVInstPtr _app,cptr8 _filename){
    tinygltf::TinyGLTF tiny;
    tinygltf::Model t_model;
    std::string t_err,t_warn;
    SVString tt = _app->m_file_sys->getFileFullName(_filename);
    std::string t_filename = tt.c_str();
    bool t_ret = tiny.LoadASCIIFromFile(&t_model, &t_err, &t_warn, _filename);
    int a = 0;
    return true;
}
