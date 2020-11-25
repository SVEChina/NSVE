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
#include "../base/SVMap.h"
#include "../base/SVArray.h"
#include "../base/svstr.h"

#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtl3D.h"
#include "../mtl/SVMtlGLTF.h"
#include "../mtl/SVSurface.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVMtlLib.h"

#include "../node/SVSkinNode.h"
#include "../node/SVModelNode.h"
#include "../node/SVMorphNode.h"

#include "../basesys/SVScene.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVModelMgr.h"

#include "../core/SVModel.h"
#include "../core/SVMesh3d.h"
#include "../core/SVAnimateSkin.h"
#include "../core/SVAnimateMorph.h"

#include "../rendercore/SVRMeshRes.h"
#include "../rendercore/SVRenderMesh.h"

#include "../node/SVSkinNode.h"

#include <map>
#include <vector>

using namespace sv;

SVLoaderGLTFEx::SVLoaderGLTFEx(SVInstPtr _app)
:SVGBaseEx(_app) {
}

SVLoaderGLTFEx::~SVLoaderGLTFEx() {
}

SVSkinNodePtr SVLoaderGLTFEx::loadFromFile(SVInstPtr _app, cptr8 _filename) {
    tinygltf::TinyGLTF tiny;
    tinygltf::Model t_model;
    std::string t_err,t_warn;
    SVString tt = _app->m_file_sys->getFileFullName(_filename);
    std::string t_filename = tt.c_str();
    bool t_ret = tiny.LoadASCIIFromFile(&t_model, &t_err, &t_warn, t_filename);
    if(t_ret) {
        //用各种模型接入
        SVString t_path = _app->m_file_sys->getPath(tt.c_str());
        return building(_app,&t_model,t_path.c_str());
    }
    return nullptr;
}

//
SVSkinNodePtr SVLoaderGLTFEx::building(SVInstPtr _app,
                              tinygltf::Model* _model,
                              cptr8 _path) {
    SVSkinNodePtr _nodePtr = MakeSharedPtr<SVSkinNode>(_app);
    //构建skin
    std::vector<SVSkeletonPtr> t_skeArray;
    for(s32 i=0;i<_model->skins.size();i++) {
        SVSkeletonPtr t_ske = _genSkin(_app,_model,i,_path);
        t_ske->refresh();
        t_skeArray.push_back(t_ske);
    }
    
    //构建动画
     for(s32 i=0;i<_model->animations.size();i++) {
         SVAnimateSkinPtr t_ani = _genAnimate(_app,_model,i,_path);
         t_ani->setSkes(t_skeArray);
         std::string _name = "default"+std::to_string(i);
         _nodePtr->addAni(_name.c_str(), t_ani);
     }
    
    //构建mtl
    std::vector<SVMtlCorePtr> _mtlPool;
    std::vector<SVSurfacePtr> _surfacePool;
    _mtlPool.resize(_model->materials.size());
    _surfacePool.resize(_model->materials.size());
    for(s32 i=0;i<_model->materials.size();i++) {
        _mtlPool[i] = _genMtl(_app, _model, i, _path);
        _surfacePool[i] = _genSurface(_app, _model, i,  _path);
    }
    _nodePtr->setMaterial(_mtlPool);
    _nodePtr->setSurface(_surfacePool);
    
    //构建MESH
    std::vector<SVModelPtr> t_modelsPtr{};
    t_modelsPtr.resize(_model->meshes.size());
    for(s32 i=0;i<_model->meshes.size();i++) {
        //
         t_modelsPtr[i] = _genModel(_app, _model, i, _path);
        //整理mesh对应的mtl
        int meshNum = t_modelsPtr[i]->getMeshNum();
        for (s32 j = 0; j < meshNum; j++) {
            SVMesh3dPtr meshPtr = t_modelsPtr[i]->getMesh(j);
            
            tinygltf::Primitive &primitive = _model->meshes[j].primitives[j];
            meshPtr->setMtl(_mtlPool[primitive.material]);
            meshPtr->setSurface(_surfacePool[primitive.material]);
        }
        
        //Model绑定skin
        s32 _skinIndex = getSkinIndexForMeshId(_app, _model, i);
        t_modelsPtr[i]->bindSke(t_skeArray[_skinIndex]);
        
    }
    _nodePtr->setModel(t_modelsPtr);
    
    //构建节点
    for(s32 i=0;i<_model->scenes.size();i++) {
        tinygltf::Scene* t_scene = &(_model->scenes[i]);
        for(s32 j=0;j<t_scene->nodes.size();j++) {
            s32 t_node_id = t_scene->nodes[j];
//            genNode(_app,_model,t_node_id);
        }
    }
    return _nodePtr;
}

s32 SVLoaderGLTFEx::getSkinIndexForMeshId(SVInstPtr _app, tinygltf::Model* _model, s32 _meshId) {
    for(s32 i=0; i<_model->nodes.size(); i++) {
        if (_model->nodes[i].mesh == _meshId) {
            return _model->nodes[i].skin;
        }
    }
    return 0;
}

void SVLoaderGLTFEx::genNode(SVInstPtr _app,
                             tinygltf::Model* _model,
                             s32 _nodeid,
                             cptr8 _path) {
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
        genNode(_app,_model,t_node->children[i],_path);
    }
}

SVModelPtr SVLoaderGLTFEx::_genModel(SVInstPtr _app,
                                     tinygltf::Model* _model,
                                     s32 _index,
                                     cptr8 _path){
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
        SVMesh3dPtr t_mesh = _genMeshPri(_app,_model,t_pri,_path);
        if(t_mesh) {
            t_model->addMesh(t_mesh);
        }
    }
    if (t_modelMgr) {
        t_modelMgr->addModel(t_model);
    }
    return t_model;
}

//
s32 SVLoaderGLTFEx::_getAccLen(tinygltf::Accessor* acc) {
    s32 t_len = 0;
    s32 t_size1 = 0;
    if(acc->componentType == TINYGLTF_COMPONENT_TYPE_BYTE) {
        t_size1 = sizeof(s8);
    }else if(acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
        t_size1 = sizeof(u8);
    }else if(acc->componentType == TINYGLTF_COMPONENT_TYPE_SHORT) {
        t_size1 = sizeof(s16);
    }else if(acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
        t_size1 = sizeof(u16);
    }else if(acc->componentType == TINYGLTF_COMPONENT_TYPE_INT) {
        t_size1 = sizeof(s32);
    }else if(acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
        t_size1 = sizeof(u32);
    }else if(acc->componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) {
        t_size1 = sizeof(s32);
    }else if(acc->componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE) {
        t_size1 = sizeof(s64);
    }
    //
    s32 t_size2 = 0;
    if(acc->type == TINYGLTF_TYPE_VEC2) {
        t_size2 = 2;
    }else if(acc->type == TINYGLTF_TYPE_VEC3) {
        t_size2 = 3;
    }else if(acc->type == TINYGLTF_TYPE_VEC4) {
        t_size2 = 4;
    }else if(acc->type == TINYGLTF_TYPE_MAT2) {
        t_size2 = 4;
    }else if(acc->type == TINYGLTF_TYPE_MAT3) {
        t_size2 = 9;
    }else if(acc->type == TINYGLTF_TYPE_MAT4) {
        t_size2 = 16;
    }else if(acc->type == TINYGLTF_TYPE_SCALAR) {
        t_size2 = 1;
    }else if(acc->type == TINYGLTF_TYPE_VECTOR) {
        t_size2 = 4;
    }else if(acc->type == TINYGLTF_TYPE_MATRIX) {
        t_size2 = 16;
    }
    t_len = t_size1*acc->count*t_size2;
    return t_len;
}

SVMesh3dPtr SVLoaderGLTFEx::_genMeshPri(SVInstPtr _app,
                                        tinygltf::Model* _model,
                                        tinygltf::Primitive* _prim,
                                        cptr8 _path) {
    /*
     构建数据
     */
    struct QueneUnit{
        VFTYPE _vtype;
        tinygltf::Accessor* _acc;
        s8* _data;
    };
    //顶点描述
    SVVertStreamDspPtr vert_dsp = MakeSharedPtr<SVVertStreamDsp>(E_BFM_SOA);
    vert_dsp->setBufType(E_BFT_STATIC_DRAW);
    s64 vertNum = 0;
    SVBoundBox vertBox;
    std::vector<QueneUnit> _quene;
    //
    std::map<std::string,int>::iterator it= _prim->attributes.begin();
    while( it!=_prim->attributes.end() ) {
        QueneUnit _unit;
        _unit._acc = &(_model->accessors[it->second]);
        _unit._data = _getAccDataPointer(_model,_unit._acc,_path);
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
            vert_dsp->setVertCnt(vertNum);
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
        vert_dsp->push(_unit._vtype);
        s32 t_len = _getAccLen(_unit._acc);
        vert_dsp->setSigleStreamData(_unit._vtype,_unit._data,t_len);
        _quene.push_back(_unit);
        it++;
    }

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
        s8* t_index_p = _getAccDataPointer(_model,_acc_index,_path);
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
                SVDataSwapPtr t_i_dataswap = MakeSharedPtr<SVDataSwap>();
                t_i_dataswap->resize(indexNum*sizeof(u16));
                s32* tt_i_p = (s32*)t_index_p;
                for(s32 i=0;i<indexNum;i++) {
                    u16 t_value = (u16)(*tt_i_p);
                    t_i_dataswap->appendData(&t_value, sizeof(u16));
                    tt_i_p++;
                }
                t_index_dsp->setStreamData(t_i_dataswap);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_INT) {
                t_u_size = sizeof(s32);
                t_index_dsp->setDataType(32);
                SVDataSwapPtr t_i_dataswap = MakeSharedPtr<SVDataSwap>();
                t_i_dataswap->resize(indexNum*sizeof(s32));
                t_i_dataswap->writeData(t_index_p, indexNum*sizeof(u32));
                t_index_dsp->setStreamData(t_i_dataswap);
                t_i_dataswap = nullptr;
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
                t_u_size = sizeof(u32);
                t_index_dsp->setDataType(32);
                SVDataSwapPtr t_i_dataswap = MakeSharedPtr<SVDataSwap>();
                t_i_dataswap->resize(indexNum*sizeof(u32));
                u32* tt_i_p = (u32*)t_index_p;
                t_i_dataswap->writeData(t_index_p, indexNum*sizeof(u32));
                t_index_dsp->setStreamData(t_i_dataswap);
                t_i_dataswap = nullptr;
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) {
                t_u_size = sizeof(s32);
            }else if(_acc_index->componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE) {
                t_u_size = sizeof(s64);
            }
        }
        t_rMesh->setIndexDsp(t_index_dsp);
        t_rMesh->setDrawVertNum(indexNum);
    }
    t_rMesh->setDrawMethod(_prim->mode);    //定义恰好是一一对应关系
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
    return t_mesh;
}

SVSkeletonPtr SVLoaderGLTFEx::_genSkin(SVInstPtr _app,
                                    tinygltf::Model* _model,
                                    s32 _index,
                                    cptr8 _path){
    if(_index<0)
        return nullptr;
    
    tinygltf::Skin* t_skindata = &(_model->skins[_index]);
    SVSkeletonPtr t_ske = MakeSharedPtr<SVSkeleton>();
    s32 t_node_index = t_skindata->skeleton;
    //创建根骨骼,并构建骨架
    t_ske->m_root = _genBone(_app, _model, t_skindata, t_node_index,  nullptr, t_ske);
    //初始化骨架基本数据
    tinygltf::Accessor* t_acc = &(_model->accessors[t_skindata->inverseBindMatrices]);
    s8* t_imb_p = _getAccDataPointer(_model,t_acc,_path);
    f32* t_imb_p_f = (f32*)t_imb_p;
    for(s32 i=0;i<t_skindata->joints.size();i++) {
        s32 t_nodeid = t_skindata->joints[i];
        SVBonePtr t_bone = t_ske->getBoneByNodeID(t_nodeid);//获取对应的骨骼
        if(t_bone) {
            t_bone->m_id = i;
            f32* t_imb_p_f_aim = t_imb_p_f+i*16;
            t_bone->m_invertBindMat.set(t_imb_p_f_aim);
        }
    }
    return t_ske;
}

SVBonePtr SVLoaderGLTFEx::_genBone(SVInstPtr _app,
                                   tinygltf::Model* _model,
                                     tinygltf::Skin* _skinData,
                                     s32 _nodeIndex,
                                     SVBonePtr _parent,
                                     SVSkeletonPtr _ske) {
    if(_nodeIndex<0)
        return nullptr;
    //填充数据
    tinygltf::Node* t_node = &(_model->nodes[_nodeIndex]);
    if(!t_node){
        return nullptr;
    }
    SVBonePtr t_bone = MakeSharedPtr<SVBone>();
    for(s32 i=0;i<_skinData->joints.size();i++) {
        if( _skinData->joints[i] == _nodeIndex) {
            t_bone->m_id = i;
            break;
        }
    }
    t_bone->m_nodeid = _nodeIndex;
    t_bone->m_pParent = _parent;
    t_bone->m_name = t_node->name.c_str(); // 骨头名称
    if(t_node->translation.size() == 3) {
        t_bone->m_tran.x = t_node->translation[0];
        t_bone->m_tran.y = t_node->translation[1];
        t_bone->m_tran.z = t_node->translation[2];
    }
    if(t_node->scale.size() == 3) {
        t_bone->m_scale.x = t_node->scale[0];
        t_bone->m_scale.y = t_node->scale[1];
        t_bone->m_scale.z = t_node->scale[2];
    }
    if(t_node->rotation.size() == 4) {
        t_bone->m_rot.x = t_node->rotation[0];
        t_bone->m_rot.y = t_node->rotation[1];
        t_bone->m_rot.z = t_node->rotation[2];
        t_bone->m_rot.w = t_node->rotation[3];
    }
    if(t_node->mesh>=0) {
        int a = 0;
    }
    if(_parent == nullptr) {
        //root
        _ske->m_name = _skinData->name.c_str();
        _ske->m_root = t_bone;
    }else{
        //child
        _parent->m_children.push_back(t_bone);
    }
    _ske->addBone(t_bone);
    //构建子骨骼
    for(s32 i=0;i<t_node->children.size();i++) {
        s32 t_nodeIndex = t_node->children[i];
        _genBone(_app,_model,_skinData,t_nodeIndex,t_bone,_ske);
    }
    return t_bone;
}

static sv_inline s32 _getInterpolationMode(SVString _interpolation){
    if (_interpolation == "LINEAR") {
        return 0;
    }else if(_interpolation == "STEP"){
        return 1;
    }else if(_interpolation == "CUBICSPLINE"){
        return 2;
    }
    return 3;
}

SVAnimateSkinPtr SVLoaderGLTFEx::_genAnimate(SVInstPtr _app, tinygltf::Model* _model, s32 _aniIndex, cptr8 _path){
    if(_aniIndex<0) {
        return nullptr;
    }
    tinygltf::Animation* _data = &(_model->animations[_aniIndex]);
    SVAnimateSkinPtr t_ani = MakeSharedPtr<SVAnimateSkin>(_app, _data->name.c_str());
    //构建轨道
    for(s32 i=0;i<_data->channels.size();i++) {
        tinygltf::AnimationChannel* t_chn = &(_data->channels[i]);
        if (t_chn->sampler < 0) {
            continue;
        }
        SVChannelPtr chn_obj = MakeSharedPtr<SVChannel>();
        chn_obj->m_target_node = t_chn->target_node;
        chn_obj->m_target_path = t_chn->target_path.c_str();
        //输入和输出是一对
        //构建通道和KEY
        tinygltf::AnimationSampler* t_samp = &(_data->samplers[t_chn->sampler]);
        tinygltf::Accessor* t_acc_in = &(_model->accessors[t_samp->input]);
        tinygltf::Accessor* t_acc_out = &(_model->accessors[t_samp->output]);
        if(t_acc_in->count!=t_acc_out->count){
            continue;
        }
        chn_obj->m_maxTime = t_acc_in->maxValues[0];
        chn_obj->m_minTime = t_acc_in->minValues[0];
        chn_obj->m_intertype_trans = _getInterpolationMode(t_samp->interpolation.c_str());
        s8* t_p_in = _getAccDataPointer(_model,t_acc_in,_path);
        s8* t_p_out = _getAccDataPointer(_model,t_acc_out,_path);
        if( t_chn->target_path == "translation") {
            //构建trans
            f32* t_p_tim = (f32*)t_p_in;
            f32* t_p_pos = (f32*)t_p_out;
            for(s32 i=0;i<t_acc_in->count;i++) {
                SVASKeyPosPtr t_askey = MakeSharedPtr<SVASKeyPos>();
                t_askey->m_time = *t_p_tim;
                t_p_tim++;
                t_askey->m_pos.x = *t_p_pos;
                t_p_pos++;
                t_askey->m_pos.y = *t_p_pos;
                t_p_pos++;
                t_askey->m_pos.z = *t_p_pos;
                t_p_pos++;
                chn_obj->m_keyPool.append(t_askey);
            }
        }else if( t_chn->target_path == "rotation") {
            f32* t_p_tim = (f32*)t_p_in;
            f32* t_p_rot = (f32*)t_p_out;
            for(s32 i=0;i<t_acc_in->count;i++) {
                SVASKeyRotPtr t_askey = MakeSharedPtr<SVASKeyRot>();
                t_askey->m_time = *t_p_tim;
                t_p_tim++;
                t_askey->m_rot.x = *t_p_rot;
                t_p_rot++;
                t_askey->m_rot.y = *t_p_rot;
                t_p_rot++;
                t_askey->m_rot.z = *t_p_rot;
                t_p_rot++;
                t_askey->m_rot.w = *t_p_rot;
                t_p_rot++;
                chn_obj->m_keyPool.append(t_askey);
            }
        }else if( t_chn->target_path == "scale") {
            //构建scale
            f32* t_p_tim = (f32*)t_p_in;
            f32* t_p_scale = (f32*)t_p_out;
            for(s32 i=0;i<t_acc_in->count;i++) {
                SVASKeyScalePtr t_askey = MakeSharedPtr<SVASKeyScale>();
                t_askey->m_time = *t_p_tim;
                t_p_tim++;
                t_askey->m_scale.x = *t_p_scale;
                t_p_scale++;
                t_askey->m_scale.y = *t_p_scale;
                t_p_scale++;
                t_askey->m_scale.z = *t_p_scale;
                t_p_scale++;
                chn_obj->m_keyPool.append(t_askey);
            }
        }else if( t_chn->target_path == "weights") {
            //构建weight
            s32 a = 0;
        }
        
        //加入到通道中
        t_ani->addChannel(chn_obj);
    }
    return t_ani;
}


SVMtlCorePtr SVLoaderGLTFEx::_genMtl(SVInstPtr _app, tinygltf::Model* _model, s32 _index, cptr8 _path) {
    tinygltf::Material* _mat = &(_model->materials[_index]);
    SVMtlCorePtr _mtlPtr = _app->getMtlLib()->getMtl("test1");
    tinygltf::ParameterMap &_additionalValues = _mat->additionalValues;
    
    //
    _mtlPtr->setDepthEnable(true);
    _mtlPtr->setDepthMethod(SV_LEQUAL);
    _mtlPtr->setStencilEnable(true);
    
    //
    auto doubleSided = _additionalValues.find("doubleSided");
    if (doubleSided != _additionalValues.end()) {
        if (doubleSided->second.bool_value) {
            _mtlPtr->setCullEnable(false);
        } else {
            _mtlPtr->setCullEnable(true);
            _mtlPtr->setCullFace(SV_CCW, SV_BACK);
        }
    }
    //
    _mtlPtr->setBlendEnable(false);
    _mtlPtr->setBlendSeparateEnable(false);
    auto alphaMode = _additionalValues.find("alphaMode");
    if (alphaMode != _additionalValues.end()) {
        if (strcmp(alphaMode->second.string_value.c_str(), "BLEND") == 0) {
            _mtlPtr->setBlendSeparateEnable(true);
            _mtlPtr->setBlendSeparateState(
               SV_SRC_ALPHA,
               SV_ONE_MINUS_SRC_ALPHA,
               SV_ONE,
               SV_ONE_MINUS_SRC_ALPHA,
               SV_FUNC_ADD
           );
        }
    }

    
    
    
    
    return _mtlPtr;
}

SVSurfacePtr SVLoaderGLTFEx::_genSurface(SVInstPtr _app, tinygltf::Model* _model, s32 _index, cptr8 _path) {
    tinygltf::Material* _material = &(_model->materials[_index]);
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
    /*
     value
     */
    tinygltf::ParameterMap::iterator it1 = _material->values.begin();
    while (it1!=_material->values.end()) {
        SVString t_key = it1->first.c_str();
        if( t_key == "baseColorTexture") {
            tinygltf::Parameter* t_param = &(it1->second);
            if(t_param) {
                s32 _texIndex = t_param->TextureIndex();
                SVTexturePtr t_tex = _genTexture(_app,_model,_texIndex,_path);
                if(t_tex) {
                    t_surface->setTexture("aTexture0", t_tex);
//                    t_surface->setTexture(t_key, t_tex);
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
            s32 _texIndex = t_param->TextureIndex();
            SVTexturePtr t_tex = _genTexture(_app,_model,_texIndex,_path);
            if(t_tex) {
                t_surface->setTexture(t_key, t_tex);
            }
        }else if(t_key == "metallicFactor") {
            tinygltf::Parameter* t_param = &(it1->second);
            t_surface->setParam("metallicFactor",(f32)(t_param->Factor()) );
        }else if(t_key == "roughnessFactor") {
            tinygltf::Parameter* t_param = &(it1->second);
            t_surface->setParam("roughnessFactor",(f32)(t_param->Factor()) );
        }
        it1++;
    }
    
    /*
     additional
     */
    tinygltf::ParameterMap::iterator it2 = _material->additionalValues.begin();
    while (it2!=_material->additionalValues.end()) {
        SVString t_key = it2->first.c_str();
        if(t_key == "normalTexture") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                s32 _texIndex = t_param->TextureIndex();
                SVTexturePtr t_tex = _genTexture(_app,_model,_texIndex,_path);
                if(t_tex) {
                    t_surface->setTexture(t_key, t_tex);
                }
            }
        }else if(t_key == "occlusionTexture") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                s32 _texIndex = t_param->TextureIndex();
                SVTexturePtr t_tex = _genTexture(_app,_model,_texIndex,_path);
                if(t_tex) {
                    t_surface->setTexture(t_key, t_tex);
                }
//                Texture* texture = &(m_gltf.textures[textureIndex]);
//                Image* image = &(m_gltf.images[texture->source]);
//                tMtl->m_pOcclusionTex = image->texture;
//                tMtl->m_occlusionStrength = t_param->ParamValue("strength");
            }
        }else if(t_key == "emissiveTexture") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                s32 _texIndex = t_param->TextureIndex();
                SVTexturePtr t_tex = _genTexture(_app,_model,_texIndex,_path);
                if(t_tex) {
                    t_surface->setTexture(t_key, t_tex);
                }
            }
        }else if(t_key == "emissiveFactor") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param && t_param->number_array.size() ==3) {
                FVec3 _value = FVec3(t_param->number_array[0],
                                     t_param->number_array[1],
                                     t_param->number_array[2]);
                t_surface->setParam("emissiveFactor",_value);
            }
        }else if(t_key == "alphaMode") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                
            }
//            tinygltf::Parameter* t_param = &(it2->second);
//            if(t_param ) {
//                SVString t_str = t_param->string_value;
//            }
        }else if(t_key == "name") {
            //材质名称
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                
            }
//            tinygltf::Parameter* t_param = &(it2->second);
//            if(t_param ) {
//                SVString t_str = t_param->string_value;
//            }
        }else if(t_key == "doubleSided") {
            tinygltf::Parameter* t_param = &(it2->second);
            if(t_param) {
                
            }
        }
        it2++;
    }
    /*
     extensions
     */
    //std::map<std::string, Value> ExtensionMap;
    tinygltf::ExtensionMap::iterator it3 = _material->extensions.begin();
    while ( it3!=_material->extensions.end() ) {
        std::string ttt = it3->first;
        tinygltf::Value t_value = it3->second;
        if(it3->second.IsBool() ) {
            //it3->second
        }else if(it3->second.IsInt() ) {
            
        }else if(it3->second.IsNumber() ) {
            
        }else if(it3->second.IsString() ) {
            
        }else if(it3->second.IsBinary() ) {
            
        }else if(it3->second.IsArray() ) {
            
        }else if(it3->second.IsObject() ) {
            
        }
        it3++;
    }
    //ExtensionMap extensions;
    return t_surface;
}

SVTexturePtr SVLoaderGLTFEx::_genTexture(SVInstPtr _app,
                                         tinygltf::Model* _model,
                                         s32 _index,
                                         cptr8 _path) {
    SVTexturePtr t_tex = nullptr;
    tinygltf::Texture* texture = &(_model->textures[_index]);
    tinygltf::Image* image = &(_model->images[texture->source]);
    if(image->uri.empty()) {
        t_tex = nullptr;
    }else{
        SVString t_full = _path;
        t_full = t_full + image->uri.c_str();
        t_tex = _app->getTexMgr()->getTexture(t_full.c_str());
    }
    return t_tex;
}


s8* SVLoaderGLTFEx::_getAccDataPointer(tinygltf::Model* _model,
                                       tinygltf::Accessor* acc,
                                       cptr8 _path) {
//    s32 t_acc_off = acc->byteOffset;
//    s32 t_viewID = acc->bufferView;
    tinygltf::BufferView* t_bufview = &(_model->bufferViews[acc->bufferView]);
    if(t_bufview) {
//        tinygltf::Buffer* t_buf = &(_model->buffers[t_bufview->buffer]);
        return (s8*)(_model->buffers[t_bufview->buffer].data.data() + (t_bufview->byteOffset + acc->byteOffset));
        
//        s32 t_bufID = t_bufview->buffer;
//        s32 t_view_off = t_bufview->byteOffset;
//        s32 t_len = t_bufview->byteLength;
//        s32 t_view_stride = t_bufview->byteStride;
//        tinygltf::Buffer* t_buf = &(_model->buffers[t_bufID]);
//        if(t_view_off + t_acc_off>=t_buf->data.size()) {
//            return nullptr;
//        }
//        s8* p = ((s8*)(&(t_buf->data[0]))) + t_view_off + t_acc_off;
//        return p;
    }
    return nullptr;
}

//if(_texIndex>=0) {
////                    tinygltf::Texture* texture = &(_model->textures[_texIndex]);
////                    if(t_param) {
////                        s32 textureIndex = t_param->TextureIndex();
////                    }
//                    //tMtl->m_pBaseColorTex = image->texture;
////                    Sampler* t_sampler = &( m_gltf.samplers[texture->sampler] );
////                    //
////                    if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_NEAREST) {
////
////                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_LINEAR) {
////
////                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST) {
////
////                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST) {
////
////                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR) {
////
////                    }else if( t_sampler->minFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR) {
////
////                    }
////                    //
////                    if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_NEAREST) {
////
////                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_LINEAR) {
////
////                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST) {
////
////                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST) {
////
////                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR) {
////
////                    }else if( t_sampler->magFilter == SVGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR) {
////
////                    }
////                    //
////                    if( t_sampler->wrapS == SVGLTF_TEXTURE_WRAP_REPEAT ) {
////                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_REPEAT);
////                    }else if( t_sampler->wrapS == SVGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ) {
////                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_CLAMP_TO_EDAGE);
////                    }else if( t_sampler->wrapS == SVGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ) {
////                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_MIRROR);
////                    }
////                    //
////                    if( t_sampler->wrapT == SVGLTF_TEXTURE_WRAP_REPEAT ) {
////                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_REPEAT);
////                    }else if( t_sampler->wrapT == SVGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ) {
////                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_CLAMP_TO_EDAGE);
////                    }else if( t_sampler->wrapT == SVGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ) {
////                        tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_MIRROR);
////                    }
////                    //
////                    if( t_sampler->wrapR == SVGLTF_TEXTURE_WRAP_REPEAT ) {
////                        //tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_REPEAT);
////                    }else if( t_sampler->wrapR == SVGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ) {
////                        //tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_CLAMP_TO_EDAGE);
////                    }else if( t_sampler->wrapR == SVGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ) {
////                        //tMtl->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_MIRROR);
////                    }
//                }
