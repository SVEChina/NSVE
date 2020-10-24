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
    bool t_ret = tiny.LoadASCIIFromFile(&t_model, &t_err, &t_warn, t_filename);
    if(t_ret) {
        //用各种模型接入
        building(_app,&t_model);
    }
    return t_ret;
}

//class Model {
// public:
//  Model() {}
//
//  Model(const Model &) = default;
//  Model &operator=(const Model &) = default;
//
//  ~Model() {}
//
//  bool operator==(const Model &) const;
//
//  std::vector<Accessor> accessors;
//  std::vector<Animation> animations;
//  std::vector<Buffer> buffers;
//  std::vector<BufferView> bufferViews;
//  std::vector<Material> materials;
//  std::vector<Mesh> meshes;
//  std::vector<Node> nodes;
//  std::vector<Texture> textures;
//  std::vector<Image> images;
//  std::vector<Skin> skins;
//  std::vector<Sampler> samplers;
//  std::vector<Camera> cameras;
//  std::vector<Scene> scenes;
//  std::vector<Light> lights;
//  ExtensionMap extensions;
//
//  int defaultScene;
//  std::vector<std::string> extensionsUsed;
//  std::vector<std::string> extensionsRequired;
//
//  Asset asset;
//
//  Value extras;
//};

//
void SVLoaderGLTFEx::building(SVInstPtr _app,tinygltf::Model* _model) {
    //构建MESH
    for(s32 i=0;i<_model->meshes.size();i++) {
        _genModel(_app,_model,i);
    }
    //构建skin
    for(s32 i=0;i<_model->skins.size();i++) {
        _genSkin(_app,_model,i);
    }
    //构建mtl
    for(s32 i=0;i<_model->materials.size();i++) {
        _genMtl(_app,_model,i);
    }
    
//    //构建节点
//    for(s32 i=0;i<_model->scenes.size();i++) {
//        tinygltf::Scene* t_scene = &(_model->scenes[i]);
//        for(s32 j=0;j<t_scene->nodes.size();j++) {
//            s32 t_node_id = t_scene->nodes[j];
//            //genNode(_app,_model,t_node_id);
//        }
//    }
}

void SVLoaderGLTFEx::genNode(SVInstPtr _app,tinygltf::Model* _model,s32 _nodeid) {
    tinygltf::Node* t_node = &(_model->nodes[_nodeid]);
    if(t_node->skin>=0) {
        //有骨骼动画
        int i=0;
//        SVNodePtr t_svNode = _buildSkinNode(t_node);
//        if(t_svNode) {
//            t_sc->addNode(t_svNode);
//            m_nodeArray.append(t_svNode);
//        }
    }
    if(t_node->mesh>=0) {
        int i=0;
        //无骨骼动画 纯mesh
//                SVNodePtr t_svNode = _build3DNode(t_node);
//                if(t_svNode) {
//                    m_nodeArray.append(t_svNode);
//                }
    }
    if(t_node->camera>=0) {
//                SVNodePtr t_svNode = _buildCameraNode(t_node);
//                if(t_svNode) {
//                    //t_sc->addNode(t_svNode);
//                    m_nodeArray.append(t_svNode);
//                }
    }
    for(s32 i=0;i<t_node->children.size();i++) {
        genNode(_app,_model,t_node->children[i]);
    }
}

SVModelPtr SVLoaderGLTFEx::_genModel(SVInstPtr _app,tinygltf::Model* _model,s32 _index){
    if(_index<0)
        return nullptr;
    tinygltf::Mesh* t_meshdata = &(_model->meshes[_index]);
    SVString t_modelName = t_meshdata->name.c_str();
    SVModelMgrPtr t_modelMgr = _app->getModelMgr();
    if (t_modelMgr) {
        SVModelPtr t_model = t_modelMgr->getModel(t_modelName);
        if (t_model) {
            return t_model;
        }
    }
    SVModelPtr t_model = MakeSharedPtr<SVModel>(_app);
    t_model->setName(t_modelName.c_str());
    //非权重方式
    for(s32 i=0;i<t_meshdata->primitives.size();i++) {
        tinygltf::Primitive* t_pri = &(t_meshdata->primitives[i]);
//        SVMesh3dPtr t_mesh = _buildMeshPri(t_pri);
//        if(t_mesh) {
//            t_model->addMesh(t_mesh);
//        }
    }
    if (t_modelMgr) {
        t_modelMgr->addModel(t_model);
    }
    return t_model;
}

SVModelPtr SVLoaderGLTFEx::_genSkin(SVInstPtr _app,tinygltf::Model* _model,s32 _index){
    if(_index<0)
        return nullptr;
    tinygltf::Skin* t_skindata = &(_model->skins[_index]);
    return nullptr;
}

SVModelPtr SVLoaderGLTFEx::_genMtl(SVInstPtr _app,tinygltf::Model* _model,s32 _index){
    if(_index<0)
        return nullptr;
    tinygltf::Material* t_mtldata = &(_model->materials[_index]);
    return nullptr;
}
