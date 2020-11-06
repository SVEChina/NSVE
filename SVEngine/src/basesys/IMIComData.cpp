//
// IMIComData.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIComData.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../file/IMIFileMgr.h"
#include "../base/IMIDataSwap.h"
#include "../base/IMIDataChunk.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

static u16 m_rect_index[6] = {0,1,2,2,1,3 };
    
static f32 m_screen_rect_v2_t0[] = {
    -1.0f,-1.0f, 0.0f,0.0f,
    1.0f,-1.0f, 1.0f,0.0f,
    -1.0f,1.0f, 0.0f,1.0f,
    1.0f,1.0f, 1.0f,1.0f
};

s32 IMIComData::m_standard_imgw_st = 1024;
s32 IMIComData::m_standard_imgh_st = 1024;
s32 IMIComData::m_standard_imgw_fp = 1024;
s32 IMIComData::m_standard_imgh_fp = 1024;
s32 IMIComData::m_standard_imgw_as = 1024;
s32 IMIComData::m_standard_imgh_as = 1024;

IMIComData::IMIComData(IMIInstPtr _app)
:IMIEventProc(_app) {
    m_screenMesh = nullptr;
    m_faceMesh = nullptr;
}

IMIComData::~IMIComData() {
    destroy();
}

void IMIComData::init() {
    
}

void IMIComData::destroy() {
    m_screenMesh = nullptr;
    m_faceMesh = nullptr;
}

void IMIComData::loadDefault() {
    m_screenMesh = MakeSharedPtr<IMIRenderMesh>(mApp);
    //索引描述
    IMIIndexStreamDspPtr t_index_dsp = MakeSharedPtr<IMIIndexStreamDsp>();
    t_index_dsp->setIndexCnt(6);
    t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_index_dsp->setStreamData(m_rect_index, 6*sizeof(u16));
    m_screenMesh->setIndexDsp(t_index_dsp);
    //顶点描述
    IMIVertStreamDspPtr t_vert_dsp= MakeSharedPtr<IMIVertStreamDsp>(E_BFM_AOS);
    t_vert_dsp->push(E_VF_V2);
    t_vert_dsp->push(E_VF_T0);
    t_vert_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_vert_dsp->setVertCnt(4);
    t_vert_dsp->setMixStreamData(m_screen_rect_v2_t0, 16*sizeof(f32));
    m_screenMesh->setVertDsp(t_vert_dsp);
    //设置绘制方法
    m_screenMesh->setDrawMethod(E_DRAW_TRIANGLES);
    m_screenMesh->setDrawVertNum(6);
    m_screenMesh->dispatch();
}

IMIRenderMeshPtr IMIComData::faceMesh(IMI_E_FACEMESH_TYPE _meshType){
    m_faceMesh = IMIComData::createFaceMeshSt(mApp,_meshType);
    return m_faceMesh;
}

IMIRenderMeshPtr IMIComData::createFaceMeshSt(IMIInstPtr _app, IMI_E_FACEMESH_TYPE _meshType) {
    if(_meshType == IMI_E_FACEMESH_SIMPILITY) {
        return _loadFaceMesh(_app,
                             "mesh_face_simplity.json",
                             "texcoord_face_simplity.json",
                             2);
    }else if(_meshType == IMI_E_FACEMESH_HEAD){
        return _loadFaceMesh(_app,
                             "mesh_face_head.json",
                             "texcoord_face_head.json",
                             2);
    }else if(_meshType == IMI_E_FACEMESH_WHOLE){
        return _loadFaceMesh(_app,
                             "mesh_face.json",
                             "texcoord_face.json",
                             2);
    }else if(_meshType == IMI_E_FACEMESH_EYE){
        return _loadFaceMesh(_app,
                             "mesh_eye.json",
                             "texcoord_eye.json",
                             2);
    }else if(_meshType == IMI_E_FACEMESH_BROW){
        return _loadFaceMesh(_app,
                             "mesh_eyebrow.json",
                             "texcoord_eyebrow.json",
                             2);
    }else if(_meshType == IMI_E_FACEMESH_TUNE){
        return _loadFaceMesh(_app,
                             "mesh_face_tune.json",
                             "texcoord_face_tune.json",
                             2);
    }
    return nullptr;
}

IMIRenderMeshPtr IMIComData::createFaceMeshFp(IMIInstPtr _app,bool _simp) {
    if(_simp) {
        return _loadFaceMesh(_app,
                             "facemesh_fp_simplify.json",
                             "standerface_fp_simplify.json",
                             1);
    }else{
        return _loadFaceMesh(_app,
                             "facemesh_fp.json",
                             "standerface_fp.json",
                             1);
    }
}

IMIRenderMeshPtr IMIComData::createFaceMeshAS(IMIInstPtr _app,bool _simp) {
    if(_simp) {
        return _loadFaceMesh(_app,
                             "facemesh_as_simplify.json",
                             "standerface_as_simplify.json",
                             0);
    }else{
        return _loadFaceMesh(_app,
                             "facemesh_as.json",
                             "standerface_as.json",
                             0);
    }
}

IMIRenderMeshPtr IMIComData::_loadFaceMesh(IMIInstPtr _app,
                                         cptr8 _indexfile,
                                         cptr8 _datafile,
                                         s32 _type) {
    IMIString indexName = IMIString("res/mesh/") + IMIString(_indexfile);
    IMIString dataName = IMIString("res/mesh/") + IMIString(_datafile);
    if(!_app->m_file_sys->exist(indexName) ) {
        return nullptr;
    }
    if(!_app->m_file_sys->exist(dataName) ) {
        return nullptr;
    }
    //解析索引
    s32 _tri_cnt = 0;
    s32 _index_cnt = 0;
    IMIDataChunk stream_index;
    _app->m_file_sys->loadFileContentStr(&stream_index, indexName.c_str());
    RAPIDJSON_NAMESPACE::Document doc_i;
    doc_i.Parse<0>(stream_index.getPointerChar());
    if (doc_i.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc_i.GetParseError();
        IMI_LOG_DEBUG("json %s error:%d \n", indexName.c_str() ,code);
        return nullptr;
    }
    if( doc_i.HasMember("param") ) {
        RAPIDJSON_NAMESPACE::Value &t_param = doc_i["param"];
        if (t_param.IsObject()) {
            if (t_param.HasMember("tricount")) {
                RAPIDJSON_NAMESPACE::Value &t_value = t_param["tricount"];
                _tri_cnt = t_value.GetInt();
            }
            if (t_param.HasMember("vertexcount")) {
                RAPIDJSON_NAMESPACE::Value &t_value = t_param["vertexcount"];
                _index_cnt = t_value.GetInt();
            }
        }
    }
    s16* t_index = new s16[_index_cnt];
    if (doc_i.HasMember("data")) {
        RAPIDJSON_NAMESPACE::Value &t_param = doc_i["data"];
        if (t_param.IsArray()) {
            for (s32 i=0; i<t_param.Size(); i++) {
                RAPIDJSON_NAMESPACE::Value &v = t_param[i];
                if (v.IsInt()) {
                    t_index[i] = s16(v.GetInt());
                }
            }
        }
    }
    IMIIndexStreamDspPtr t_index_dsp = MakeSharedPtr<IMIIndexStreamDsp>();
    t_index_dsp->setIndexCnt(_index_cnt);
    t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_index_dsp->setStreamData(t_index, _index_cnt*sizeof(u16));
    delete [] t_index;
    
    /*解析数据*/
    s32 _vert_cnt = 0;
    s32 _design_w = 0;
    s32 _design_h = 0;
    IMIDataChunk stream_vert;
    _app->m_file_sys->loadFileContentStr(&stream_vert, dataName.c_str());
    RAPIDJSON_NAMESPACE::Document doc_vert;
    doc_vert.Parse<0>(stream_vert.getPointerChar());
    if (doc_vert.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc_vert.GetParseError();
        IMI_LOG_DEBUG("json %s error:%d \n", dataName.c_str() ,code);
        return nullptr;
    }
    if( doc_vert.HasMember("param") ) {
        RAPIDJSON_NAMESPACE::Value &t_param = doc_vert["param"];
        if (t_param.IsObject()) {
            if (t_param.HasMember("facepoints_count")) {
                RAPIDJSON_NAMESPACE::Value &t_value = t_param["facepoints_count"];
                _vert_cnt = t_value.GetInt();
            }
            if (t_param.HasMember("design_img_width")) {
                RAPIDJSON_NAMESPACE::Value &t_value = t_param["design_img_width"];
                _design_w = t_value.GetInt();
            }
            if (t_param.HasMember("design_img_height")) {
                RAPIDJSON_NAMESPACE::Value &t_value = t_param["design_img_height"];
                _design_h = t_value.GetInt();
            }
        }
    }
    //
    if(_type == 0) {
        IMIComData::m_standard_imgw_as = _design_w;
        IMIComData::m_standard_imgh_as = _design_h;
    }else if(_type == 1) {
        IMIComData::m_standard_imgw_fp = _design_w;
        IMIComData::m_standard_imgh_fp = _design_h;
    }else if(_type == 2) {
        IMIComData::m_standard_imgw_st = _design_w;
        IMIComData::m_standard_imgh_st = _design_h;
    }
    //顶点数据
    f32* t_data = new f32[_vert_cnt*2];
    if (doc_vert.HasMember("data")) {
        RAPIDJSON_NAMESPACE::Value &t_param = doc_vert["data"];
        if (t_param.IsArray()) {
            for (s32 i=0; i<t_param.Size(); i++) {
                RAPIDJSON_NAMESPACE::Value &v = t_param[i];
                if (v.IsFloat()) {
                    t_data[i] = v.GetFloat();
                }
            }
        }
    }
    //纹理坐标
    f32* t_data_tex = new f32[_vert_cnt*2];
    for(s32 i=0;i<_vert_cnt*2;i++) {
        if(i%2 == 0) {
            t_data_tex[i] = t_data[i]/_design_w;
        }else{
            t_data_tex[i] = t_data[i]/_design_h;
        }
    }
    //顶点描述
    IMIVertStreamDspPtr t_vert_dsp= MakeSharedPtr<IMIVertStreamDsp>(E_BFM_SOA);
    t_vert_dsp->push(E_VF_V2);
    t_vert_dsp->push(E_VF_T0);
    t_vert_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_vert_dsp->setVertCnt(_vert_cnt);
    t_vert_dsp->setSigleStreamData(E_VF_V2, t_data, _vert_cnt*2*sizeof(f32));
    t_vert_dsp->setSigleStreamData(E_VF_T0, t_data_tex, _vert_cnt*2*sizeof(f32));
    delete[] t_data;
    delete[] t_data_tex;
    //
    IMIRenderMeshPtr t_r_mesh = MakeSharedPtr<IMIRenderMesh>(_app);
    t_r_mesh->setIndexDsp(t_index_dsp);
    t_r_mesh->setVertDsp(t_vert_dsp);
    //设置绘制方法
    t_r_mesh->setDrawMethod(E_DRAW_TRIANGLES);
    t_r_mesh->setDrawVertNum(_index_cnt);
    t_r_mesh->dispatch();
    return t_r_mesh;
}
