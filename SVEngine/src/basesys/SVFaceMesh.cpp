//
// SVFaceMesh.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFaceMesh.h"
#include "../app/SVInst.h"
#include "../base/SVDataChunk.h"
#include "../file/SVFileMgr.h"
#include "../rendercore/SVRenderMesh.h"
#include "../third/rapidjson/document.h"
#include "../third/rapidjson/stringbuffer.h"
#include "../third/rapidjson/writer.h"

using namespace sv;

SVFaceMesh::SVFaceMesh(SVInstPtr _app)
:SVGBaseEx(_app){
}

SVRenderMeshPtr SVFaceMesh::createFaceMeshSt(SVInstPtr _app,bool _simp) {
    if(_simp) {
        return _loadFaceMesh(_app,
                             "facemesh_st_simplify.json",
                             "standerface_st_simplify.json");
    }else{
        return _loadFaceMesh(_app,
                             "facemesh_st.json",
                             "standerface_st.json");
    }
}

SVRenderMeshPtr SVFaceMesh::createFaceMeshFp(SVInstPtr _app,bool _simp) {
    if(_simp) {
        return _loadFaceMesh(_app,
                             "facemesh_fp_simplify.json",
                             "standerface_fp_simplify.json");
    }else{
        return _loadFaceMesh(_app,
                             "facemesh_fp.json",
                             "standerface_fp.json");
    }
}

SVRenderMeshPtr SVFaceMesh::createFaceMeshAS(SVInstPtr _app,bool _simp) {
    if(_simp) {
        return _loadFaceMesh(_app,
                             "facemesh_as_simplify.json",
                             "standerface_as_simplify.json");
    }else{
        return _loadFaceMesh(_app,
                             "facemesh_as.json",
                             "standerface_as.json");
    }
}

SVRenderMeshPtr SVFaceMesh::_loadFaceMesh(SVInstPtr _app,cptr8 _indexfile,cptr8 _datafile) {
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

//bool setSigleStreamData(VFTYPE _stype,void* _data,s32 _len) {
//    if(_bufMode == E_BFM_SOA) {
//        //单一流模式，需要按流分开存储
//        std::map<VFTYPE,SVDataSwapPtr>::iterator it = m_streamData.find(_stype);
//        if( it == m_streamData.end() ) {
//            return false;
//        }
//        if( !m_streamData[_stype] ) {
//            m_streamData[_stype] = MakeSharedPtr<SVDataSwap>();
//        }
//        m_streamData[_stype]->appendData(_data,_len);
//        return true;
//    }
//    return false;
//}

SVFaceMesh::~SVFaceMesh(){
}

//void SVFaceMesh::init(){
////    //加载as标准脸数据
//////    _loadFaceMeshData("facemesh_as");
//////    _loadStanderFaceData("standerface_as");
//////    _loadFaceMeshData("facemesh_as_simplify");
//////    _loadStanderFaceData("standerface_as_simplify");
////    //加载st标准脸数据
//////    _loadFaceMeshData("facemesh_st");
//////    _loadStanderFaceData("standerface_st");
////    _loadFaceMeshData("facemesh_st_simplify");
////    _loadStanderFaceData("standerface_st_simplify");
//////    _loadFaceMeshData("facemesh_st_normal");
////    _loadFaceMeshData("facemesh_st_108");
//////    _loadStanderFaceData("standerface_st_normal");
////    //加载fp标准脸数据
//////    _loadFaceMeshData("facemesh_fp");
//////    _loadStanderFaceData("standerface_fp");
//////    _loadFaceMeshData("facemesh_fp_simplify");
//////    _loadStanderFaceData("standerface_fp_simplify");
//}

//void SVFaceMesh::_loadFaceMeshData(cptr8 _name){
//    SVDataChunk tDataStream;
//    SVString filename = SVString("svres/mesh/") + SVString(_name) + SVString(".json");
//    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, filename.c_str());
//    if (!tflag) {
//        SVString info = SVString("not find ") + filename + SVString(" please check mesh file path!\n");
//       // MA_LOG_INFO(info.c_str());
//        return;
//    }
//    SV_LOG_DEBUG("file facemeshdata %s \n", tDataStream.getPointerChar());
//    RAPIDJSON_NAMESPACE::Document doc;
//    doc.Parse<0>(tDataStream.getPointerChar());
//    if (doc.HasParseError()) {
//        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
//        SV_LOG_DEBUG("rapidjson error code:%d \n", code);
//        return;
//    }
//    FaceMesh *facemesh = new FaceMesh();
//    if (doc.HasMember("param")) {
//        RAPIDJSON_NAMESPACE::Value &t_param = doc["param"];
//        if (t_param.IsObject()) {
//            if (t_param.HasMember("tricount")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["tricount"];
//                facemesh->tricount = t_value.GetInt();
//            }
//            if (t_param.HasMember("vertexcount")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["vertexcount"];
//                facemesh->vertexcount = t_value.GetInt();
//            }
//        }
//    }
//    if (doc.HasMember("data")) {
//        RAPIDJSON_NAMESPACE::Value &t_param = doc["data"];
//        if (t_param.IsArray()) {
//            for (int i=0; i<t_param.Size(); i++) {
//                RAPIDJSON_NAMESPACE::Value &v = t_param[i];
//                if (v.IsInt()) {
//                    facemesh->triangles[i] = v.GetInt();
//                }
//            }
//        }
//    }
//    m_facemeshpool.append(_name,facemesh);
//    SV_LOG_DEBUG("load facemeshdata end\n");
//}

//void SVFaceMesh::_loadStanderFaceData(cptr8 _name){
//    SVDataChunk tDataStream;
//    SV_LOG_DEBUG("load standerfacedata begin\n");
//    SVString filename = SVString("svres/mesh/") + SVString(_name) + SVString(".json");
//    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, filename.c_str());
//    if (!tflag) {
//        SVString info = SVString("not find ") + filename + SVString(" please check shader file path!\n");
//        //MA_LOG_INFO(info.c_str());
//        return;
//    }
//    SV_LOG_DEBUG("file standerfacedata %s \n", tDataStream.getPointerChar());
//    RAPIDJSON_NAMESPACE::Document doc;
//    doc.Parse<0>(tDataStream.getPointerChar());
//    if (doc.HasParseError()) {
//        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
//        SV_LOG_DEBUG("rapidjson error code:%d \n", code);
//        return;
//    }
//    StanderFace *standerface = new StanderFace();
//    if (doc.HasMember("param")) {
//        RAPIDJSON_NAMESPACE::Value &t_param = doc["param"];
//        if (t_param.IsObject()) {
//            if (t_param.HasMember("facepoints_count")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["facepoints_count"];
//                standerface->facepoints_count = t_value.GetInt();
//            }
//            if (t_param.HasMember("face_top")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["face_top"];
//                standerface->face_top = t_value.GetInt();
//            }
//            if (t_param.HasMember("face_left")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["face_left"];
//                standerface->face_left = t_value.GetInt();
//            }
//            if (t_param.HasMember("face_bottom")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["face_bottom"];
//                standerface->face_bottom = t_value.GetInt();
//            }
//            if (t_param.HasMember("face_right")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["face_right"];
//                standerface->face_right = t_value.GetInt();
//            }
//            if (t_param.HasMember("face_yaw")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["face_yaw"];
//                standerface->face_yaw = t_value.GetFloat();
//            }
//            if (t_param.HasMember("face_roll")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["face_roll"];
//                standerface->face_roll = t_value.GetFloat();
//            }
//            if (t_param.HasMember("face_pitch")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["face_pitch"];
//                standerface->face_pitch = t_value.GetFloat();
//            }
//            if (t_param.HasMember("design_img_width")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["design_img_width"];
//                standerface->design_img_width = t_value.GetInt();
//            }
//            if (t_param.HasMember("design_img_height")) {
//                RAPIDJSON_NAMESPACE::Value &t_value = t_param["design_img_height"];
//                standerface->design_img_height = t_value.GetInt();
//            }
//        }
//    }
//    if (doc.HasMember("data")) {
//        RAPIDJSON_NAMESPACE::Value &t_param = doc["data"];
//        if (t_param.IsArray()) {
//            for (int i=0; i<t_param.Size(); i++) {
//                RAPIDJSON_NAMESPACE::Value &v = t_param[i];
//                if (v.IsFloat()) {
//                    standerface->points[i] = v.GetFloat();
//                }else if (v.IsInt()){
//                    standerface->points[i] = v.GetInt()*1.0;
//                }
//            }
//        }
//    }
//    m_standerfacepool.append(_name,standerface);
//    SV_LOG_DEBUG("load standerfacedata end\n");
//}
