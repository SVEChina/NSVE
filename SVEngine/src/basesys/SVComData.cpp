//
// SVComData.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVComData.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../file/SVFileMgr.h"
#include "../base/SVDataSwap.h"
#include "../base/SVDataChunk.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

static u16 m_rect_index[6] = {0,1,2,2,1,3 };
    
static f32 m_screen_rect_v2_t0[] = {
    -1.0f,-1.0f, 0.0f,0.0f,
    1.0f,-1.0f, 1.0f,0.0f,
    -1.0f,1.0f, 0.0f,1.0f,
    1.0f,1.0f, 1.0f,1.0f
};

s32 SVComData::m_standard_imgw_st = 1024;
s32 SVComData::m_standard_imgh_st = 1024;
s32 SVComData::m_standard_imgw_fp = 1024;
s32 SVComData::m_standard_imgh_fp = 1024;
s32 SVComData::m_standard_imgw_as = 1024;
s32 SVComData::m_standard_imgh_as = 1024;

SVComData::SVComData(SVInstPtr _app)
:SVEventProc(_app) {
    m_screenMesh = nullptr;
    m_faceMesh = nullptr;
}

SVComData::~SVComData() {
    destroy();
}

void SVComData::init() {
    
}

void SVComData::destroy() {
    m_screenMesh = nullptr;
    m_faceMesh = nullptr;
}

void SVComData::loadDefault() {
    m_screenMesh = MakeSharedPtr<SVRenderMesh>(mApp);
    //索引描述
    SVIndexStreamDspPtr t_index_dsp = MakeSharedPtr<SVIndexStreamDsp>();
    t_index_dsp->setIndexCnt(6);
    t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_index_dsp->setStreamData(m_rect_index, 6*sizeof(u16));
    m_screenMesh->setIndexDsp(t_index_dsp);
    //顶点描述
    SVVertStreamDspPtr t_vert_dsp= MakeSharedPtr<SVVertStreamDsp>(E_BFM_AOS);
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
    //
    m_faceMesh = SVComData::createFaceMeshSt(mApp,false);
}

SVRenderMeshPtr SVComData::createFaceMeshSt(SVInstPtr _app,bool _simp) {
    if(_simp) {
        return _loadFaceMesh(_app,
                             "facemesh_st_simplify.json",
                             "standerface_st_simplify.json",
                             2);
    }else{
        return _loadFaceMesh(_app,
                             "facemesh_st_normal.json",
                             "standerface_st_normal.json",
                             2);
    }
}

SVRenderMeshPtr SVComData::createFaceMeshFp(SVInstPtr _app,bool _simp) {
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

SVRenderMeshPtr SVComData::createFaceMeshAS(SVInstPtr _app,bool _simp) {
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

SVRenderMeshPtr SVComData::_loadFaceMesh(SVInstPtr _app,
                                         cptr8 _indexfile,
                                         cptr8 _datafile,
                                         s32 _type) {
    SVString indexName = SVString("res/mesh/") + SVString(_indexfile);
    SVString dataName = SVString("res/mesh/") + SVString(_datafile);
    if(!_app->m_file_sys->exist(indexName) ) {
        return nullptr;
    }
    if(!_app->m_file_sys->exist(dataName) ) {
        return nullptr;
    }
    //解析索引
    s32 _tri_cnt = 0;
    s32 _index_cnt = 0;
    SVDataChunk stream_index;
    _app->m_file_sys->loadFileContentStr(&stream_index, indexName.c_str());
    RAPIDJSON_NAMESPACE::Document doc_i;
    doc_i.Parse<0>(stream_index.getPointerChar());
    if (doc_i.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc_i.GetParseError();
        SV_LOG_DEBUG("json %s error:%d \n", indexName.c_str() ,code);
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
    SVIndexStreamDspPtr t_index_dsp = MakeSharedPtr<SVIndexStreamDsp>();
    t_index_dsp->setIndexCnt(_index_cnt);
    t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_index_dsp->setStreamData(t_index, _index_cnt*sizeof(u16));
    delete [] t_index;
    
    /*解析数据*/
    s32 _vert_cnt = 0;
    s32 _design_w = 0;
    s32 _design_h = 0;
    SVDataChunk stream_vert;
    _app->m_file_sys->loadFileContentStr(&stream_vert, dataName.c_str());
    RAPIDJSON_NAMESPACE::Document doc_vert;
    doc_vert.Parse<0>(stream_vert.getPointerChar());
    if (doc_vert.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc_vert.GetParseError();
        SV_LOG_DEBUG("json %s error:%d \n", dataName.c_str() ,code);
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
        SVComData::m_standard_imgw_as = _design_w;
        SVComData::m_standard_imgh_as = _design_h;
    }else if(_type == 1) {
        SVComData::m_standard_imgw_fp = _design_w;
        SVComData::m_standard_imgh_fp = _design_h;
    }else if(_type == 2) {
        SVComData::m_standard_imgw_st = _design_w;
        SVComData::m_standard_imgh_st = _design_h;
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
    SVVertStreamDspPtr t_vert_dsp= MakeSharedPtr<SVVertStreamDsp>(E_BFM_SOA);
    t_vert_dsp->push(E_VF_V2);
    t_vert_dsp->push(E_VF_T0);
    t_vert_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_vert_dsp->setVertCnt(_vert_cnt);
    t_vert_dsp->setSigleStreamData(E_VF_V2, t_data, _vert_cnt*2*sizeof(f32));
    t_vert_dsp->setSigleStreamData(E_VF_T0, t_data_tex, _vert_cnt*2*sizeof(f32));
    delete[] t_data;
    delete[] t_data_tex;
    //
    SVRenderMeshPtr t_r_mesh = MakeSharedPtr<SVRenderMesh>(_app);
    t_r_mesh->setIndexDsp(t_index_dsp);
    t_r_mesh->setVertDsp(t_vert_dsp);
    //设置绘制方法
    t_r_mesh->setDrawMethod(E_DRAW_TRIANGLES);
    t_r_mesh->setDrawVertNum(_index_cnt);
    t_r_mesh->dispatch();
    return t_r_mesh;
}
