//
// SVLoaderGLTFEx.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVLoaderGLTFEx.h"
#include "SVFileMgr.h"
#include "../app/SVInst.h"
#include "../base/SVResDsp.h"

#include "../file/SVParseDef.h"
#include "../file/SVFileMgr.h"

#include "../base/SVDataChunk.h"
#include "../base/SVDataSwap.h"
#include "../base/SVQuat.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtl3D.h"
#include "../mtl/SVMtlGLTF.h"
#include "../mtl/SVSurface.h"

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

#include <map>
#include <vector>

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

//
void SVLoaderGLTFEx::building(SVInstPtr _app,tinygltf::Model* _model) {
    //构建mtl
    for(s32 i=0;i<_model->materials.size();i++) {
        _genMtl(_app,_model,i);
    }
    //构建MESH
    for(s32 i=0;i<_model->meshes.size();i++) {
        _genModel(_app,_model,i);
    }
    //构建skin
    for(s32 i=0;i<_model->skins.size();i++) {
        _genSkin(_app,_model,i);
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
        SVMesh3dPtr t_mesh = _buildMeshPri(_app,_model,t_pri);
        if(t_mesh) {
            t_model->addMesh(t_mesh);
        }
    }
    if (t_modelMgr) {
        t_modelMgr->addModel(t_model);
    }
    return t_model;
}

SVMesh3dPtr SVLoaderGLTFEx::_buildMeshPri(SVInstPtr _app,
                                          tinygltf::Model* _model,
                                          tinygltf::Primitive* _prim) {
    /*
     构建数据
     */
    struct QueneUnit{
        VFTYPE _vtype;
        tinygltf::Accessor* _acc;
        s8* _data;
    };
    //顶点描述
    SVVertStreamDspPtr vert_dsp = MakeSharedPtr<SVVertStreamDsp>(E_BFM_AOS);
    vert_dsp->setBufType(E_BFT_STATIC_DRAW);
    s64 vertNum = 0;
    SVBoundBox vertBox;
    std::vector<QueneUnit> _quene;
    std::map<std::string,int>::iterator it= _prim->attributes.begin();
    while( it!=_prim->attributes.end() ) {
        QueneUnit _unit;
        _unit._acc = &(_model->accessors[it->second]);
        if( strcmp(it->first.c_str(),"POSITION") == 0 ) {
            _unit._vtype = E_VF_V3;
            vertNum = _unit._acc->count;
            //设置box
            if(_unit._acc->minValues.size() == 3
               && _unit._acc->maxValues.size() == 3 ) {
                vertBox.set(FVec3(_unit._acc->minValues[0],
                                  _unit._acc->minValues[1],
                                  _unit._acc->minValues[2]),
                            FVec3(_unit._acc->maxValues[0],
                                  _unit._acc->maxValues[1],
                                  _unit._acc->maxValues[2]));
                //t_mesh->setBox(t_box);
            }
        }else if(strcmp(it->first.c_str(),"NORMAL") == 0 ) {
            _unit._vtype = E_VF_NOR;
        }else if(strcmp(it->first.c_str(),"TANGENT") == 0 ) {
            _unit._vtype = E_VF_TAG;
        }else if(strcmp(it->first.c_str(),"COLOR_0") == 0 ) {
            _unit._vtype = E_VF_C0;
        }else if(strcmp(it->first.c_str(),"TEXCOORD_0") == 0 ) {
            _unit._vtype = E_VF_T0;
        }else if(strcmp(it->first.c_str(),"JOINTS_0") == 0 ) {
            _unit._vtype = E_VF_BONE;
        }else if(strcmp(it->first.c_str(),"WEIGHTS_0") == 0 ) {
            _unit._vtype = E_VF_BONE_W;
        }
        _unit._data = _getAccDataPointer(_model,_unit._acc );
        vert_dsp->push(_unit._vtype);
        _quene.push_back(_unit);
        it++;
    }
    vert_dsp->setVertCnt(vertNum);
    s32 vertSize = vert_dsp->getVertSize();
    //拼接数据,为了优化
    SVDataSwapPtr t_data =  MakeSharedPtr<SVDataSwap>();
    t_data->resize( vertSize*vertNum );
    for(s32 i=0;i<vertNum;i++) {
        for(s32 j=0;j<_quene.size();j++) {
            if(_quene[j]._vtype == E_VF_V3) {
                t_data->appendData(_quene[j]._data, 3*sizeof(f32));
                _quene[j]._data += 3*sizeof(f32);
            }else if(_quene[j]._vtype == E_VF_NOR) {
                t_data->appendData(_quene[j]._data, 3*sizeof(f32));
                _quene[j]._data += 3*sizeof(f32);
            }else if(_quene[j]._vtype == E_VF_TAG) {
                t_data->appendData(_quene[j]._data, 3*sizeof(f32));
                _quene[j]._data += 3*sizeof(f32);
            }else if(_quene[j]._vtype == E_VF_C0) {
//                t_data->appendData(_quene[j]._data, 4*sizeof(s8));
//                _quene[j]._data += 4*sizeof(s8);
            }else if(_quene[j]._vtype == E_VF_T0) {
                t_data->appendData(_quene[j]._data, 2*sizeof(f32));
                _quene[j]._data += 2*sizeof(f32);
            }else if(_quene[j]._vtype == E_VF_BONE) {
                t_data->appendData(_quene[j]._data, 4*sizeof(u16));
                _quene[j]._data += 4*sizeof(u16);
            }else if(_quene[j]._vtype == E_VF_BONE_W) {
                t_data->appendData(_quene[j]._data, 4*sizeof(f32));
                _quene[j]._data += 4*sizeof(f32);
            }
        }
    }
    vert_dsp->setMixStreamData(t_data);
    SVRenderMeshPtr t_rMesh = MakeSharedPtr<SVRenderMesh>(_app);
    t_rMesh->setVertDsp(vert_dsp);
    t_rMesh->setDrawVertNum(vertNum);
    /*
     构建索引
     */
    if(_prim->indices>=0) {
        SVIndexStreamDspPtr t_index_dsp = MakeSharedPtr<SVIndexStreamDsp>();
        t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
        tinygltf::Accessor* _acc_index = &(_model->accessors[_prim->indices]);
        s32 indexNum = _acc_index->count;
        t_index_dsp->setIndexCnt(indexNum);
        s8* t_index_p = _getAccDataPointer(_model,_acc_index);
        if(t_index_p!=nullptr) {
            s32 t_u_size = 0;
            if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_BYTE) {
                t_u_size = sizeof(s8);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
                t_u_size = sizeof(u8);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_SHORT) {
                t_u_size = sizeof(s16);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
                t_u_size = sizeof(u16);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_INT) {
                t_u_size = sizeof(s32);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
                t_u_size = sizeof(u32);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) {
                t_u_size = sizeof(s32);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE) {
                t_u_size = sizeof(s64);
            }
            SVDataSwapPtr t_i_dataswap = MakeSharedPtr<SVDataSwap>();
            t_i_dataswap->resize(indexNum*sizeof(u16));
            u32* tt_i_p = (u32*)t_index_p;
            for(s32 i=0;i<indexNum;i++) {
                u16 t_value = (u16)(*tt_i_p);
                t_i_dataswap->appendData(&t_value, sizeof(u16));
                tt_i_p++;
            }
            t_index_dsp->setStreamData(t_i_dataswap);
            t_i_dataswap = nullptr;
        }
        t_rMesh->setIndexDsp(t_index_dsp);
        t_rMesh->setDrawVertNum(indexNum);
    }
//    t_rMesh->setDrawMethod(_prim->mode);    //定义恰好是一一对应关系
    if(_prim->mode == TINYGLTF_MODE_POINTS) {
        t_rMesh->setDrawMethod(E_DRAW_POINTS);
    }else if(_prim->mode == TINYGLTF_MODE_LINE) {
        t_rMesh->setDrawMethod(E_DRAW_LINES);
    }else if(_prim->mode == TINYGLTF_MODE_LINE_LOOP) {
        t_rMesh->setDrawMethod(E_DRAW_LINE_LOOP);
    }else if(_prim->mode == TINYGLTF_MODE_LINE_STRIP) {
        t_rMesh->setDrawMethod(E_DRAW_LINE_STRIP);
    }else if(_prim->mode == TINYGLTF_MODE_TRIANGLES) {
        t_rMesh->setDrawMethod(E_DRAW_TRIANGLES);
    }else if(_prim->mode == TINYGLTF_MODE_TRIANGLE_STRIP) {
        t_rMesh->setDrawMethod(E_DRAW_TRIANGLE_STRIP);
    }else if(_prim->mode == TINYGLTF_MODE_TRIANGLE_FAN) {
        t_rMesh->setDrawMethod(E_DRAW_TRIANGLE_FAN);
    }
    t_rMesh->dispatch();
    /*
     构建材质
     */
    //SVMtlCorePtr t_mtl = _buildMtl(_app,_model,_prim);
    SVMesh3dPtr t_mesh = MakeSharedPtr<SVMesh3d>(_app);
    t_mesh->setRenderMesh(t_rMesh);
    //t_mesh->setMtl();
    return t_mesh;
}

SVModelPtr SVLoaderGLTFEx::_genSkin(SVInstPtr _app,tinygltf::Model* _model,s32 _index){
    if(_index<0)
        return nullptr;
    tinygltf::Skin* t_skindata = &(_model->skins[_index]);
    return nullptr;
}

//    Material* t_mtl = &(m_gltf.materials[_index]);
//    SVMtlGLTFPtr tMtl = nullptr;
//    if (_vtf & E_VF_BONE) {
//        tMtl = MakeSharedPtr<SVMtlGLTFSkin>(mApp);
//    }else{
//        tMtl = MakeSharedPtr<SVMtlGLTF>(mApp);
//    }

SVModelPtr SVLoaderGLTFEx::_genMtl(SVInstPtr _app,tinygltf::Model* _model,s32 _index){
    if(_index<0)
        return nullptr;
    tinygltf::Material* _material = &(_model->materials[_index]);
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
    tinygltf::ParameterMap::iterator it1 = _material->values.begin();
    while (it1!=_material->values.end()) {
        SVString t_key = it1->first.c_str();
        if( t_key == "baseColorTexture") {
            tinygltf::Parameter* t_param = &(it1->second);
            if(t_param) {
                s32 _texIndex = t_param->TextureIndex();
                if(_texIndex>=0) {
                    tinygltf::Texture* texture = &(_model->textures[_texIndex]);
                    tinygltf::Image* image = &(_model->images[texture->source]);
                    if(image->uri.empty() ) {
                        //无url
                    }else{
                        
                    }
                    //tMtl->m_pBaseColorTex = image->texture;
//                    Sampler* t_sampler = &( m_gltf.samplers[texture->sampler] );
//                    //
//                    if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_NEAREST) {
//
//                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_LINEAR) {
//
//                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST) {
//
//                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST) {
//
//                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR) {
//
//                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR) {
//
//                    }
//                    //
//                    if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_NEAREST) {
//
//                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_LINEAR) {
//
//                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST) {
//
//                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST) {
//
//                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR) {
//
//                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR) {
//
//                    }
//                    //
//                    if( t_sampler->wrapS == SVGLTF_TEXTURE_WRAP_REPEAT ) {
//                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_REPEAT);
//                    }else if( t_sampler->wrapS == SVGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ) {
//                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_CLAMP_TO_EDAGE);
//                    }else if( t_sampler->wrapS == SVGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ) {
//                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_MIRROR);
//                    }
//                    //
//                    if( t_sampler->wrapT == SVGLTF_TEXTURE_WRAP_REPEAT ) {
//                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_REPEAT);
//                    }else if( t_sampler->wrapT == SVGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ) {
//                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_CLAMP_TO_EDAGE);
//                    }else if( t_sampler->wrapT == SVGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ) {
//                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_MIRROR);
//                    }
//                    //
//                    if( t_sampler->wrapR == SVGLTF_TEXTURE_WRAP_REPEAT ) {
//                        //tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_REPEAT);
//                    }else if( t_sampler->wrapR == SVGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ) {
//                        //tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_CLAMP_TO_EDAGE);
//                    }else if( t_sampler->wrapR == SVGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ) {
//                        //tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_MIRROR);
//                    }
                }
            }
        }else if(t_key == "baseColorFactor") {
            tinygltf::Parameter* t_param = &(it1->second);
            if(t_param->number_array.size() == 3) {
                FVec3 _v = FVec3(t_param->number_array[0],
                                 t_param->number_array[1],
                                 t_param->number_array[2]);
                t_surface->setParam("baseColorFactor",_v );
            }
        }else if(t_key == "metallicRoughnessTexture") {
            tinygltf::Parameter* t_param = &(it1->second);
//            s32 textureIndex = t_param->TextureIndex();
//            Texture* texture = &(m_gltf.textures[textureIndex]);
//            Image* image = &(m_gltf.images[texture->source]);
//            tMtl->m_pMetallicRoughnessTex = image->texture;
        }else if(t_key == "metallicFactor") {
            tinygltf::Parameter* t_param = &(it1->second);
            t_surface->setParam("metallicFactor",(f32)(t_param->Factor()) );
        }else if(t_key == "roughnessFactor") {
            tinygltf::Parameter* t_param = &(it1->second);
            t_surface->setParam("roughnessFactor",(f32)(t_param->Factor()) );
        }
        it1++;
    }
    
    //
    tinygltf::ParameterMap::iterator it2 = _material->additionalValues.begin();
    while (it2!=_material->additionalValues.end()) {
        SVString t_key = it2->first.c_str();
        if(t_key == "normalTexture") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                s32 textureIndex = t_param->TextureIndex();
//                Texture* texture = &(m_gltf.textures[textureIndex]);
//                Image* image = &(m_gltf.images[texture->source]);
//                tMtl->m_pNormalTex = image->texture;
//                tMtl->m_normalScale = t_param->ParamValue("scale");
            }
        }else if(t_key == "occlusionTexture") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                s32 textureIndex = t_param->TextureIndex();
//                Texture* texture = &(m_gltf.textures[textureIndex]);
//                Image* image = &(m_gltf.images[texture->source]);
//                tMtl->m_pOcclusionTex = image->texture;
//                tMtl->m_occlusionStrength = t_param->ParamValue("strength");
            }
        }else if(t_key == "emissiveTexture") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
//                s32 textureIndex = t_param->TextureIndex();
//                Texture* texture = &(m_gltf.textures[textureIndex]);
//                Image* image = &(m_gltf.images[texture->source]);
//                tMtl->m_pEmissiveTex = image->texture;
            }
        }else if(t_key == "emissiveFactor") {
            tinygltf::Parameter* t_param = &(it2->second);
//            if(t_param && t_param->number_array.size() ==3) {
//                tMtl->m_emissiveFactor.set(t_param->number_array[0],
//                                           t_param->number_array[1],
//                                           t_param->number_array[2]);
//            }
        }else if(t_key == "alphaMode") {
//            tinygltf::Parameter* t_param = &(it2->second);
//            if(t_param ) {
//                SVString t_str = t_param->string_value;
//            }
        }else if(t_key == "name") {
            //材质名称
//            tinygltf::Parameter* t_param = &(it2->second);
//            if(t_param ) {
//                SVString t_str = t_param->string_value;
//            }
        }
        it2++;
    }
//    //
//    tMtl->refresh();
//    return tMtl;
    return nullptr;
}


s8* SVLoaderGLTFEx::_getAccDataPointer(tinygltf::Model* _model,
                                     tinygltf::Accessor* acc) {
    s32 t_acc_off = acc->byteOffset;
    s32 t_viewID = acc->bufferView;
    tinygltf::BufferView* t_bufview = &(_model->bufferViews[t_viewID]);
    if(t_bufview) {
        s32 t_bufID = t_bufview->buffer;
        s32 t_view_off = t_bufview->byteOffset;
        s32 t_len = t_bufview->byteLength;
        s32 t_view_stride = t_bufview->byteStride;
        tinygltf::Buffer* t_buf = &(_model->buffers[t_bufID]);
        if(t_view_off + t_acc_off>=t_buf->data.size()) {
            return nullptr;
        }
        s8* p = ((s8*)(&(t_buf->data[0]))) + t_view_off + t_acc_off;
        return p;
    }
    return nullptr;
}
