//
// SVLoaderGLTFEx.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVLoaderGLTFEx.h"
#include "SVFileMgr.h"
#include "../app/SVInst.h"
#include "../base/SVDataChunk.h"
#include "../base/SVDataSwap.h"
#include "../base/SVQuat.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtl3D.h"
#include "../mtl/SVMtlGLTF.h"
#include "../file/SVParseDef.h"
#include "../file/SVFileMgr.h"
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

SVLoaderGLTF::SVLoaderGLTF(SVInstPtr _app)
:SVGBaseEx(_app) {
}

SVLoaderGLTF::~SVLoaderGLTF() {
}

bool SVLoaderGLTF::loadFromFile(cptr8 _filename){
//    SVDataChunk tDataStream;
//    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, _filename);
//    if (!tflag)
//        return false;
//    SV_LOG_INFO("SVLoaderGLTF :load glTF JSON sucess\n");
//    SV_LOG_INFO("SVLoaderGLTF :filedata %s\n", tDataStream.getPointerChar() );
//    if (!tDataStream.getPointerChar() ) {
//        SV_LOG_ERROR("SVLoaderGLTF :data stream is null");
//        return false;
//    }
//    RAPIDJSON_NAMESPACE::Document doc;
//    doc.Parse(tDataStream.getPointerChar());
//    if (doc.HasParseError()) {
//        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
//        SV_LOG_ERROR("SVLoaderGLTF :rapidjson error code:%d \n", code);
//        return false;
//    }
//    if (!doc.HasMember("scenes"))
//        return false;
//    if (!doc["scenes"].IsArray())
//        return false;
//    if (!doc.HasMember("nodes"))
//        return false;
//    if (!doc["nodes"].IsArray())
//        return false;
//    if (!doc.HasMember("accessors"))
//        return false;
//    if (!doc["accessors"].IsArray())
//        return false;
//    if (!doc.HasMember("buffers"))
//        return false;
//    if (!doc["buffers"].IsArray())
//        return false;
//    if (!doc.HasMember("bufferViews"))
//        return false;
//    if (!doc["bufferViews"].IsArray())
//        return false;
//    //
//    m_gltf.buffers.clear();
//    m_gltf.bufferViews.clear();
//    m_gltf.accessors.clear();
//    m_gltf.meshes.clear();
//    m_gltf.cameras.clear();
//    m_gltf.nodes.clear();
//    m_gltf.extensionsUsed.clear();
//    m_gltf.extensionsRequired.clear();
//    m_gltf.defaultScene = -1;
//    /*1. Parse Asset*/
//    if (doc.HasMember("asset") && doc["asset"].IsObject()) {
//        RAPIDJSON_NAMESPACE::Value &item = doc["asset"];
//        _parseAsset(&(m_gltf.asset), item);
//    }
//    /*2. Parse extensionUsed*/
//    if (doc.HasMember("extensionsUsed") && doc["extensionsUsed"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_extensionsUseds = doc["extensionsUsed"];
//        for (s32 i = 0; i < t_extensionsUseds.Size(); ++i) {
//            RAPIDJSON_NAMESPACE::Value &t_extensionsUsedItem = t_extensionsUseds[i];
//            m_gltf.extensionsUsed.append(t_extensionsUsedItem.GetString());
//        }
//    }
//    if (doc.HasMember("extensionsRequired") && doc["extensionsRequired"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_extensionsRequireds = doc["extensionsRequired"];
//        for (s32 i = 0; i < t_extensionsRequireds.Size(); ++i) {
//            RAPIDJSON_NAMESPACE::Value &t_extensionsRequiredItem = t_extensionsRequireds[i];
//            m_gltf.extensionsRequired.append(t_extensionsRequiredItem.GetString());
//        }
//    }
//    /*3. Parse Buffer*/
//    if (doc.HasMember("buffers") && doc["buffers"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_buffers = doc["buffers"];
//        for (s32 i = 0; i<t_buffers.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_bufferItem = t_buffers[i];
//            if (t_bufferItem.IsObject()) {
//                Buffer buffer;
//                if (!_parseBuffer(&buffer, t_bufferItem, _filename)) {
//                    return nullptr;
//                }
//                m_gltf.buffers.append(buffer);
//            }else{
//                SV_LOG_ERROR("SVLoaderGLTF Error: 'buffers' does not contain an JSON object.");
//                return nullptr;
//            }
//        }
//    }
//    /*4. Parse BufferView*/
//    if (doc.HasMember("bufferViews") && doc["bufferViews"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_bufferViews = doc["bufferViews"];
//        for (s32 i = 0; i<t_bufferViews.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_bufferViewItem = t_bufferViews[i];
//            if (!t_bufferViewItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error: 'bufferViews' does not contain an JSON object.");
//                return nullptr;
//            }
//            BufferView bufferView;
//            if (!_parseBufferView(&bufferView, t_bufferViewItem)) {
//                return nullptr;
//            }
//            m_gltf.bufferViews.append(bufferView);
//        }
//    }
//    /*5. Parse Accessor*/
//    if (doc.HasMember("accessors") && doc["accessors"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_accessors = doc["accessors"];
//        for (s32 i=0; i<t_accessors.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_accessorItem = t_accessors[i];
//            if (!t_accessorItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error: `accessors' does not contain an JSON object.");
//                return nullptr;
//            }
//            Accessor accessor;
//            if (!_parseAccessor(&accessor, t_accessorItem)) {
//                return nullptr;
//            }
//            m_gltf.accessors.append(accessor);
//        }
//    }
//    /*6. Parse Mesh*/
//    if (doc.HasMember("meshes") && doc["meshes"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_meshes = doc["meshes"];
//        for (s32 i=0; i<t_meshes.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_meshItem = t_meshes[i];
//            if (!t_meshItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error:`meshes' does not contain an JSON object.");
//                return nullptr;
//            }
//            Mesh mesh;
//            if (!_parseMesh(&mesh, t_meshItem)) {
//                return nullptr;
//            }
//            m_gltf.meshes.append(mesh);
//        }
//    }
//    /*7. Parse Node*/
//    if (doc.HasMember("nodes") && doc["nodes"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_nodes = doc["nodes"];
//        for (s32 i=0; i<t_nodes.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_nodeItem = t_nodes[i];
//            if (!t_nodeItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error:`nodes' does not contain an JSON object.");
//                return nullptr;
//            }
//            Node node;
//            if (!_parseNode(&node, t_nodeItem)) {
//                return nullptr;
//            }
//            m_gltf.nodes.append(node);
//        }
//    }
//    /*8. Parse scenes.*/
//    if (doc.HasMember("scenes") && doc["scenes"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_scenes = doc["scenes"];
//        for (s32 i =0; i<t_scenes.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_sceneItem = t_scenes[i];
//            if (!t_sceneItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error :`scenes' does not contain an JSON object.");
//                return nullptr;
//            }
//            SVArray<s32> nodesIds;
//            if (t_sceneItem.HasMember("nodes") && t_sceneItem["nodes"].IsArray()) {
//                RAPIDJSON_NAMESPACE::Value &t_nodes = t_sceneItem["nodes"];
//                for (s32 j = 0; j<t_nodes.Size(); j++) {
//                    nodesIds.append(t_nodes[j].GetInt());
//                }
//            }
//
//            Scene scene;
//            if (t_sceneItem.HasMember("name") && t_sceneItem["name"].IsString()) {
//                scene.name = t_sceneItem["name"].GetString();
//            }
//            scene.nodes = nodesIds;
//            m_gltf.scenes.append(scene);
//        }
//    }
//    /*9. Parse default scenes.*/
//    if (doc.HasMember("scene") && doc["scene"].IsNumber()) {
//        RAPIDJSON_NAMESPACE::Value &t_scene = doc["scene"];
//        const s32 defaultScene = t_scene.GetInt();
//        m_gltf.defaultScene = defaultScene;
//    }
//    /*10. Parse Material*/
//    if (doc.HasMember("materials") && doc["materials"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_materials = doc["materials"];
//        for (s32 i =0; i<t_materials.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_material = t_materials[i];
//            if (!t_material.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error :'materials' does not contain an JSON object.");
//                return nullptr;
//            }
//            Material material;
//            if (t_material.HasMember("name") && t_material["name"].IsString()) {
//                material.name = t_material["name"].GetString();
//            }
//            if (!_parseMaterial(&material, t_material)) {
//                return nullptr;
//            }
//            m_gltf.materials.append(material);
//        }
//    }
//    /*11. Parse Image*/
//    if (doc.HasMember("images") && doc["images"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_images = doc["images"];
//        for (s32 i =0; i<t_images.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_image = t_images[i];
//            if (!t_image.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error :'images' does not contain an JSON object.");
//                return nullptr;
//            }
//            Image image;
//            if (!_parseImage(&image, t_image, _filename)) {
//                return nullptr;
//            }
//            if (image.bufferView != -1) {
//                // Load image from the buffer view.
//
//                // not supporte now!!!!!
//                SV_LOG_ERROR("SVLoaderGLTF Error :read image from buffer does not supporte now.");
//                return nullptr;
//            }
//            m_gltf.images.append(image);
//        }
//    }
//    /*12. Parse Texture*/
//    if (doc.HasMember("textures") && doc["textures"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_textures = doc["textures"];
//        for (s32 i=0; i<t_textures.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_textureItem = t_textures[i];
//            if (!t_textureItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error :'textures' does not contain an JSON object.");
//                return nullptr;
//            }
//            Texture texture;
//            if (!_parseTexture(&texture, t_textureItem, _filename)) {
//                return nullptr;
//            }
//            m_gltf.textures.append(texture);
//        }
//    }
//    /*13. Parse Animation*/
//    if (doc.HasMember("animations") && doc["animations"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_animations = doc["animations"];
//        for (s32 i=0; i<t_animations.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_animationItem = t_animations[i];
//            if (!t_animationItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error :'animations' does not contain an JSON object.");
//                return nullptr;
//            }
//            Animation animation;
//            if (!_parseAnimation(&animation, t_animationItem)) {
//                return nullptr;
//            }
//            m_gltf.animations.append(animation);
//        }
//    }
//    /*14. Parse Skin*/
//    if (doc.HasMember("skins") && doc["skins"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_skins = doc["skins"];
//        for (s32 i=0; i<t_skins.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_skinItem = t_skins[i];
//            if (!t_skinItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error :'skins' does not contain an JSON object.");
//                return nullptr;
//            }
//            Skin skin;
//            skin.skeleton = i;
//            if (!_parseSkin(&skin, t_skinItem)) {
//                return nullptr;
//            }
//            m_gltf.skins.append(skin);
//        }
//    }
//    /*15. Parse Sampler*/
//    if (doc.HasMember("samplers") && doc["samplers"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &t_samplers = doc["samplers"];
//        for (s32 i=0; i<t_samplers.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &t_samplerItem = t_samplers[i];
//            if (!t_samplerItem.IsObject()) {
//                SV_LOG_ERROR("SVLoaderGLTF Error :'samplers' does not contain an JSON object.");
//                return nullptr;
//            }
//            Sampler sampler;
//            if (!_parseSampler(&sampler, t_samplerItem)) {
//                return nullptr;
//            }
//            m_gltf.samplers.append(sampler);
//        }
//    }
    return true;
}
