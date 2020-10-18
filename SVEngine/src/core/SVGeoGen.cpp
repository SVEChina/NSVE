//
// SVGeoGen.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVGeoGen.h"
#include "../app/SVDispatch.h"
#include "../base/SVCoreMath.h"
#include "../base/SVDataSwap.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderCmd.h"
#include "../app/SVInst.h"

using namespace sv;

//三角形
SVRenderMeshPtr SVGeoGen::genTri(SVInstPtr _app,
                                     f32 _len,
                                     SVBoundBox& _aabb) {
    return _getPolygonDiy(_app,3, 0.0f, _len,_aabb);
}

//方形
SVRenderMeshPtr SVGeoGen::genRect(SVInstPtr _app,f32 _w,f32 _h,SVBoundBox& _aabb) {
    _aabb.clear();
    //索引
    u16 t_index_data[] = { 0,1,2,2,1,3 };
    f32 t_coord_size = 1.0f;
    //数据
    V3_T0 t_verts[4];
    t_verts[0].x = -0.5f * _w;
    t_verts[0].y = -0.5f * _h;
    t_verts[0].z = 0.0f;
    t_verts[0].t0x = 0.0f * t_coord_size;
    t_verts[0].t0y = 0.0f * t_coord_size;

    t_verts[1].x = 0.5f * _w;
    t_verts[1].y = -0.5f * _h;
    t_verts[1].z = 0.0f;
    t_verts[1].t0x = 1.0f * t_coord_size;
    t_verts[1].t0y = 0.0f * t_coord_size;

    t_verts[2].x = -0.5f * _w;
    t_verts[2].y = 0.5f * _h;
    t_verts[2].z = 0.0f;
    t_verts[2].t0x = 0.0f * t_coord_size;
    t_verts[2].t0y = 1.0f * t_coord_size;

    t_verts[3].x = 0.5f * _w;
    t_verts[3].y = 0.5f * _h;
    t_verts[3].z = 0.0f;
    t_verts[3].t0x = 1.0f * t_coord_size;
    t_verts[3].t0y = 1.0f * t_coord_size;
    //
    for(s32 i=0;i<4;i++) {
        _aabb.expand(FVec3(t_verts[i].x,t_verts[i].y,t_verts[i].z));
    }
    //
    SVRenderMeshPtr t_mesh = MakeSharedPtr<SVRenderMesh>(_app);
    SVIndexStreamDspPtr t_index_dsp = MakeSharedPtr<SVIndexStreamDsp>();
    t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_index_dsp->setIndexCnt(6);
    t_index_dsp->setStreamData(t_index_data, 6*sizeof(u16));
    t_mesh->setIndexDsp(t_index_dsp);
    SVVertStreamDspPtr t_vert_dsp = MakeSharedPtr<SVVertStreamDsp>(E_BFM_AOS);
    t_vert_dsp->push(E_VF_V3);
    t_vert_dsp->push(E_VF_T0);
    t_vert_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_vert_dsp->setVertCnt(4);
    t_vert_dsp->setMixStreamData(t_verts, 4*sizeof(V3_T0));
    t_mesh->setVertDsp(t_vert_dsp);
    t_mesh->dispatch();
    return t_mesh;
}

SVRenderMeshPtr SVGeoGen::genRectARCHO(SVInstPtr _app,f32 _w,f32 _h,EUIARCHO _archo,SVBoundBox& _aabb) {
//    s16 t_index_data[] = { 0,1,2,2,1,3 };
//    V3_T0 t_verts[4];
//    //
//    SVRenderMeshPtr t_mesh = MakeSharedPtr<SVRenderMesh>(_app);
//    SVBufferDspPtr t_index_dsp= MakeSharedPtr<SVBufferDsp>(E_BFM_AOS);
//    SVRenderMesh::buildSVBufferDsp(E_BFT_STATIC_DRAW,6,6*sizeof(u16),t_index_data,t_index_dsp);
//    t_mesh->setIndexDsp(t_index_dsp);
//    //
//    SVBufferDspPtr t_vert_dsp= MakeSharedPtr<SVBufferDsp>(E_BFM_AOS);
//    SVRenderMesh::buildSVBufferDsp(E_BFT_STATIC_DRAW,4,6*sizeof(u16),t_verts,t_vert_dsp);
//    t_mesh->setVertDsp(t_vert_dsp);
//
//    //这个必须有渲染器才可以执行
//    return t_mesh;
//    //
//    f32 t_off_x = 0.0f;
//    f32 t_off_y = 0.0f;
//    if(_archo == E_ARCHO_LT) {
//        t_off_x = 0.5f*_w;
//        t_off_y = -0.5f*_h;
//    }else if(_archo == E_ARCHO_CT) {
//        t_off_x = 0.0f;
//        t_off_y = -0.5f*_h;
//    }else if(_archo == E_ARCHO_RT) {
//        t_off_x = -0.5f*_w;
//        t_off_y = -0.5f*_h;
//    }else if(_archo == E_ARCHO_LC) {
//        t_off_x = 0.5f*_w ;
//        t_off_y = 0.0f;
//    }else if(_archo == E_ARCHO_CC) {
//        t_off_x = 0.0f;
//        t_off_y = 0.0f;
//    }else if(_archo == E_ARCHO_RC) {
//        t_off_x = -0.5f*_w;
//        t_off_y = 0.0f;
//    }else if(_archo == E_ARCHO_LB) {
//        t_off_x = 0.5f*_w;
//        t_off_y = 0.5f*_h;
//    }else if(_archo == E_ARCHO_CB) {
//        t_off_x = 0.0f;
//        t_off_y = 0.5f*_h;
//    }else if(_archo == E_ARCHO_RB) {
//        t_off_x = -0.5f*_w;
//        t_off_y = 0.5f*_h;
//    }
//    //
//    _aabb.clear();
//    //
//    V2_T0 verts[4];
//    verts[0].x = -0.5f * _w + t_off_x;
//    verts[0].y = -0.5f * _h + t_off_y;
//    verts[0].t0x = 0.0f;
//    verts[0].t0y = 0.0f;
//
//    verts[1].x = 0.5f * _w + t_off_x;
//    verts[1].y = -0.5f * _h + t_off_y;
//    verts[1].t0x = 1.0f;
//    verts[1].t0y = 0.0f;
//
//    verts[2].x = -0.5f * _w + t_off_x;
//    verts[2].y = 0.5f * _h + t_off_y;
//    verts[2].t0x = 0.0f;
//    verts[2].t0y = 1.0f;
//
//    verts[3].x = 0.5f * _w + t_off_x;
//    verts[3].y = 0.5f * _h + t_off_y;
//    verts[3].t0x = 1.0f;
//    verts[3].t0y = 1.0f;
//    //设置包围盒
//    for(s32 i=0;i<4;i++){
//        if (i == 0) {
//            _aabb.clear();
//            _aabb.expand(FVec3(verts[i].x, verts[i].y, 0.0f));
//        }else{
//            _aabb.expand(FVec3(verts[i].x, verts[i].y, 0.0f));
//        }
//    }
//    //
//    SVRenderMeshPtr t_mesh = _app->getRenderMgr()->createMeshRObj();
//    SVDataSwapPtr t_data = MakeSharedPtr<SVDataSwap>();
//    t_data->writeData(&verts[0], sizeof(V2_T0) * 4);
//    t_mesh->setDrawVertNum(4);
//    t_mesh->setVertexData(t_data);
//    t_mesh->setVertexType(E_VF_V2_T0);
//    t_mesh->setDrawMethod(E_DRAW_TRIANGLE_STRIP);
//    t_mesh->createMesh();
//    return t_mesh;
    return nullptr;
}

//菱形
SVRenderMeshPtr SVGeoGen::genLing(SVInstPtr _app,
                                      f32 _len,
                                      SVBoundBox& _aabb) {
    return _getPolygonDiy(_app,4, 0.0f, _len,_aabb);
}

//五边
SVRenderMeshPtr SVGeoGen::genFiveEdage(SVInstPtr _app,
                                           f32 _len,
                                           SVBoundBox& _aabb) {
    return _getPolygonDiy(_app,5, 0.0f, _len,_aabb);
}

//六边
SVRenderMeshPtr SVGeoGen::genSixEdage(SVInstPtr _app,
                                          f32 _len,
                                          SVBoundBox& _aabb) {
    return _getPolygonDiy(_app,6, 15.0f, _len,_aabb);
}

//圆形
SVRenderMeshPtr SVGeoGen::genCircle(SVInstPtr _app,
                                        f32 _len,
                                        SVBoundBox& _aabb) {
    return _getPolygonDiy(_app,36, 0.0f, _len,_aabb);
}

SVRenderMeshPtr SVGeoGen::_getPolygonDiy(SVInstPtr _app,
                                             s32 _edagenum,
                                             f32 _startangle,
                                             f32 _len,
                                             SVBoundBox& _aabb) {
//    if (_edagenum <= 2)
//        return nullptr;
//    //
//    _aabb.clear();
//    //
//    f32 t_single_angle = 360.0f / _edagenum;    //单片角度
//    //
//    V2_T0 *verts = new V2_T0[_edagenum + 2];
//    //中心点和最后一个边点
//    verts[0].x = 0.0f;
//    verts[0].y = 0.0f;
//    verts[0].t0x = 0.5f;
//    verts[0].t0y = 0.5f;
//    verts[_edagenum + 1].x = cos(sv::degToRad(_startangle)) * 0.5f * _len;
//    verts[_edagenum + 1].y = sin(sv::degToRad(_startangle)) * 0.5f * _len;
//    verts[_edagenum + 1].t0x = cos(sv::degToRad(_startangle)) * 0.5f + 0.5f;
//    verts[_edagenum + 1].t0y = 0.5f - sin(sv::degToRad(_startangle)) * 0.5f;
//    //边点
//    for (s32 i = 0; i < _edagenum; i++) {
//        verts[i + 1].x = cos(sv::degToRad(_startangle)) * 0.5f * _len;
//        verts[i + 1].y = sin(sv::degToRad(_startangle)) * 0.5f * _len;
//        verts[i + 1].t0x = cos(sv::degToRad(_startangle)) * 0.5f + 0.5f;
//        verts[i + 1].t0y = 0.5f - sin(sv::degToRad(_startangle)) * 0.5f;
//        _startangle += t_single_angle;
//    }
//    //设置包围盒
//    for(s32 i=0;i<_edagenum + 2;i++){
//        _aabb.expand(FVec3(verts[i].x, verts[i].y, 0.0f));
//    }
//    //
//    SVRenderMeshPtr t_mesh = _app->getRenderMgr()->createMeshRObj();
//    SVDataSwapPtr t_data = MakeSharedPtr<SVDataSwap>();
//    t_data->writeData(verts, sizeof(V2_T0) * (_edagenum + 2));
//    t_mesh->setDrawVertNum(_edagenum + 2);
//    t_mesh->setVertexData(t_data);
//    t_mesh->setVertexType(E_VF_V2_T0);
//    t_mesh->setDrawMethod(E_DRAW_TRIANGLE_FAN);
//    t_mesh->createMesh();
//    delete[] verts;
//    //
//    return t_mesh;
    return nullptr;
}

//AABB盒
SVRenderMeshPtr SVGeoGen::genAABB(SVInstPtr _app,SVBoundBox& _aabb){
    //6*8 = 48个索引点
    u16 m_index[36];
    //4*8 = 32个点
    V3_N_T0 m_verts[24];
    //6个面
    for(s32 i=0;i<6;i++) {
        s32 base_v = i*4;
        FVec3 _min = _aabb.getMin();
        FVec3 _max = _aabb.getMax();
        FVec3 _nor;
        if(i == 0) {
            //max-z
            m_verts[base_v].x = _min.x;
            m_verts[base_v].y = _min.y;
            m_verts[base_v].z = _max.z;
            m_verts[base_v + 1].x = _max.x;
            m_verts[base_v + 1].y = _min.y;
            m_verts[base_v + 1].z = _max.z;
            m_verts[base_v + 2].x = _min.x;
            m_verts[base_v + 2].y = _max.y;
            m_verts[base_v + 2].z = _max.z;
            m_verts[base_v + 3].x = _max.x;
            m_verts[base_v + 3].y = _max.y;
            m_verts[base_v + 3].z = _max.z;
        }else if(i == 1) {
            //min-z
            m_verts[base_v].x = _max.x;
            m_verts[base_v].y = _min.y;
            m_verts[base_v].z = _min.z;
            m_verts[base_v + 1].x = _min.x;
            m_verts[base_v + 1].y = _min.y;
            m_verts[base_v + 1].z = _min.z;
            m_verts[base_v + 2].x = _max.x;
            m_verts[base_v + 2].y = _max.y;
            m_verts[base_v + 2].z = _min.z;
            m_verts[base_v + 3].x = _min.x;
            m_verts[base_v + 3].y = _max.y;
            m_verts[base_v + 3].z = _min.z;
        }else if(i == 2) {
            //max-x
            m_verts[base_v].x = _max.x;
            m_verts[base_v].y = _min.y;
            m_verts[base_v].z = _max.z;
            m_verts[base_v + 1].x = _max.x;
            m_verts[base_v + 1].y = _min.y;
            m_verts[base_v + 1].z = _min.z;
            m_verts[base_v + 2].x = _max.x;
            m_verts[base_v + 2].y = _max.y;
            m_verts[base_v + 2].z = _max.z;
            m_verts[base_v + 3].x = _max.x;
            m_verts[base_v + 3].y = _max.y;
            m_verts[base_v + 3].z = _min.z;
        }else if(i == 3) {
            //min-x
            m_verts[base_v].x = _min.x;
            m_verts[base_v].y = _min.y;
            m_verts[base_v].z = _min.z;
            m_verts[base_v + 1].x = _min.x;
            m_verts[base_v + 1].y = _min.y;
            m_verts[base_v + 1].z = _max.z;
            m_verts[base_v + 2].x = _min.x;
            m_verts[base_v + 2].y = _max.y;
            m_verts[base_v + 2].z = _min.z;
            m_verts[base_v + 3].x = _min.x;
            m_verts[base_v + 3].y = _max.y;
            m_verts[base_v + 3].z = _max.z;
        }else if(i == 4) {
            //max-y
            m_verts[base_v].x = _min.x;
            m_verts[base_v].y = _max.y;
            m_verts[base_v].z = _max.z;
            m_verts[base_v + 1].x = _max.x;
            m_verts[base_v + 1].y = _max.y;
            m_verts[base_v + 1].z = _max.z;
            m_verts[base_v + 2].x = _min.x;
            m_verts[base_v + 2].y = _max.y;
            m_verts[base_v + 2].z = _min.z;
            m_verts[base_v + 3].x = _max.x;
            m_verts[base_v + 3].y = _max.y;
            m_verts[base_v + 3].z = _min.z;
        }else if(i == 5) {
            //min-y
            m_verts[base_v].x = _min.x;
            m_verts[base_v].y = _min.y;
            m_verts[base_v].z = _min.z;
            m_verts[base_v + 1].x = _max.x;
            m_verts[base_v + 1].y = _min.y;
            m_verts[base_v + 1].z = _min.z;
            m_verts[base_v + 2].x = _min.x;
            m_verts[base_v + 2].y = _min.y;
            m_verts[base_v + 2].z = _max.z;
            m_verts[base_v + 3].x = _max.x;
            m_verts[base_v + 3].y = _min.y;
            m_verts[base_v + 3].z = _max.z;
        }
        m_verts[base_v].nx = _nor.x;
        m_verts[base_v].ny = _nor.y;
        m_verts[base_v].nz = _nor.z;
        m_verts[base_v].t0x = 0.0f;
        m_verts[base_v].t0y = 0.0f;
        //
        m_verts[base_v + 1].nx = _nor.x;
        m_verts[base_v + 1].ny = _nor.y;
        m_verts[base_v + 1].nz = _nor.z;
        m_verts[base_v + 1].t0x = 1.0f;
        m_verts[base_v + 1].t0y = 0.0f;
        //
        m_verts[base_v + 2].nx = _nor.x;
        m_verts[base_v + 2].ny = _nor.y;
        m_verts[base_v + 2].nz = _nor.z;
        m_verts[base_v + 2].t0x = 0.0f;
        m_verts[base_v + 2].t0y = 1.0f;
        //
        m_verts[base_v + 3].nx = _nor.x;
        m_verts[base_v + 3].ny = _nor.y;
        m_verts[base_v + 3].nz = _nor.z;
        m_verts[base_v + 3].t0x = 1.0f;
        m_verts[base_v + 3].t0y = 1.0f;
        //index
        s32 base_i = i*6;
        m_index[base_i] = base_v;
        m_index[base_i+1] = base_v + 1;
        m_index[base_i+2] = base_v + 2;
        m_index[base_i+3] = base_v + 2;
        m_index[base_i+4] = base_v + 1;
        m_index[base_i+5] = base_v + 3;
    }
    //
    SVRenderMeshPtr t_mesh = MakeSharedPtr<SVRenderMesh>(_app);
    //设置索引描述
    SVIndexStreamDspPtr t_index_dsp = MakeSharedPtr<SVIndexStreamDsp>();
    t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_index_dsp->setIndexCnt(36);
    t_index_dsp->setStreamData(m_index, 36*sizeof(u16));
    t_mesh->setIndexDsp(t_index_dsp);
    //设置顶点描述
    SVVertStreamDspPtr t_vert_dsp = MakeSharedPtr<SVVertStreamDsp>(E_BFM_AOS);
    t_vert_dsp->push(E_VF_V3);
    t_vert_dsp->push(E_VF_NOR);
    t_vert_dsp->push(E_VF_T0);
    t_vert_dsp->setBufType(E_BFT_STATIC_DRAW);
    t_vert_dsp->setVertCnt(24);
    t_vert_dsp->setMixStreamData(m_verts, 24*sizeof(V3_N_T0));
    t_mesh->setVertDsp(t_vert_dsp);
    //这个必须有渲染器才可以执行
    t_mesh->dispatch();
    return t_mesh;
}

SVRenderMeshPtr SVGeoGen::createRectMesh(SVInstPtr _app,f32 _w ,f32 _h , s32 _wPointCount , s32 _hPointCont){
//    s32 iWidthPoint = _wPointCount , iHeightPoint = _hPointCont;
//    s32 iDataCount = iWidthPoint * iHeightPoint;
//
//    s32 iWidthRect  = iWidthPoint - 1;
//    s32 iHeightRect = iHeightPoint - 1;
//    f32 fWidthDelta = 2.0 * _w / iWidthRect;
//    f32 fHeightDelta = 2.0 * _h / iHeightRect;
//    f32 fScreenData[iDataCount * 2];
//    s32 iDataIndex = 0;
//    memset(fScreenData , 0 , sizeof(f32) * iDataCount * 2);
//
//    for (s32 i = 0 ; i < iHeightPoint ; ++i){
//        for (s32 j = 0 ; j < iWidthPoint ; ++j ){
//            fScreenData[iDataIndex] = fWidthDelta * j - _w;
//            fScreenData[iDataIndex+1] = fHeightDelta * i - _h;
//            iDataIndex += 2;
//        }
//    }
//    s32 iRectCount  = iWidthRect * iHeightRect;
//    s32 iIndexCount = iRectCount * 2 * 3;
//    u16 dataIndex[iIndexCount];
//    s32 iIndexIndex = 0;
//    for (s32 i = 0 ; i < iHeightRect ; ++i){
//        for (s32 j = 0; j < iWidthRect ; ++j){
//            dataIndex[iIndexIndex]     = i * iWidthPoint + j;
//            dataIndex[iIndexIndex + 1] = i * iWidthPoint + j + 1;
//            dataIndex[iIndexIndex + 2] = (i + 1) * iWidthPoint + j;
//            dataIndex[iIndexIndex + 3] = (i + 1) * iWidthPoint + j;
//            dataIndex[iIndexIndex + 4] = i * iWidthPoint + j + 1;
//            dataIndex[iIndexIndex + 5] = (i + 1) * iWidthPoint + j + 1;
//            iIndexIndex += 6;
//        }
//    }
//    SVRenderMeshPtr  pRenderMesh =  _app->getRenderMgr()->createMeshRObj();
//    SVDataSwapPtr t_index = MakeSharedPtr<SVDataSwap>();
//    t_index->writeData(dataIndex, iIndexCount * sizeof(u16));
//    pRenderMesh->setIndexData(t_index, iIndexCount);
//    //渲染数据
//    V2_C_T0 pVer[iDataCount];
//
//    for (s32 i = 0; i < iDataCount ; ++i){
//        pVer[i].x = fScreenData[i * 2];
//        pVer[i].y = fScreenData[i * 2 + 1];
//        pVer[i].t0x = fScreenData[i * 2] * 0.5 + 0.5;
//        pVer[i].t0y = fScreenData[i * 2 + 1] * 0.5 + 0.5;
//        pVer[i].r = 255;
//        pVer[i].g = 255;
//        pVer[i].b = 255;
//        pVer[i].a = 255;
//    }
//    pRenderMesh->setVertexType(E_VF_V2_C_T0);
//    SVDataSwapPtr t_data = MakeSharedPtr<SVDataSwap>();
//    t_data->writeData(pVer, sizeof(V2_C_T0) * iDataCount);
//    pRenderMesh->setDrawVertNum(iDataCount);
//    pRenderMesh->setVertexData(t_data);
//    pRenderMesh->createMesh();
//    return pRenderMesh;
    return nullptr;
}

//_axis = 0 代表x轴
//_axis = 1 代表y轴
//_axis = 2 代表z轴

SVRenderMeshPtr SVGeoGen::createNetGrid(SVInstPtr _app,s32 _size,s32 _axis) {
//    SVRenderMeshPtr pRenderMesh =  _app->getRenderMgr()->createMeshRObj();
//    //渲染数据
//    V3_T0 pVer[4];
//    if(_axis ==0 ) {
//        pVer[0].x = _size*-1.0f;
//        pVer[0].z = _size;
//        pVer[1].x = _size*-1.0f;
//        pVer[1].z = _size*-1.0f;
//        pVer[2].x = _size;
//        pVer[2].z = _size;
//        pVer[3].x = _size;
//        pVer[3].z = _size*-1.0f;
//        pVer[0].y = 0;
//        pVer[1].y = 0;
//        pVer[2].y = 0;
//        pVer[3].y = 0;
//    }else if(_axis == 1) {
//        pVer[0].x = _size*-1.0f;
//        pVer[0].y = _size;
//        pVer[1].x = _size*-1.0f;
//        pVer[1].y = _size*-1.0f;
//        pVer[2].x = _size;
//        pVer[2].y = _size;
//        pVer[3].x = _size;
//        pVer[3].y = _size*-1.0f;
//        pVer[0].z = 0;
//        pVer[1].z = 0;
//        pVer[2].z = 0;
//        pVer[3].z = 0;
//    }else if(_axis == 2){
//        pVer[0].y = _size*-1.0f;
//        pVer[0].z = _size;
//        pVer[1].y = _size*-1.0f;
//        pVer[1].z = _size*-1.0f;
//        pVer[2].y = _size;
//        pVer[2].z = _size;
//        pVer[3].y = _size;
//        pVer[3].z = _size*-1.0f;
//        pVer[0].x = 0;
//        pVer[1].x = 0;
//        pVer[2].x = 0;
//        pVer[3].x = 0;
//    }
////    pVer[0].t0x = 0.0f;
////    pVer[0].t0y = 0.0f;
////    pVer[1].t0x = 0.0f;
////    pVer[1].t0y = 2.0f;
////    pVer[2].t0x = 2.0f;
////    pVer[2].t0y = 0.0f;
////    pVer[3].t0x = 2.0f;
////    pVer[3].t0y = 2.0f;
//    pVer[0].t0x = 0.0f;
//    pVer[0].t0y = 0.0f;
//    pVer[1].t0x = 0.0f;
//    pVer[1].t0y = _size/32.0f;
//    pVer[2].t0x = _size/32.0f;
//    pVer[2].t0y = 0.0f;
//    pVer[3].t0x = _size/32.0f;
//    pVer[3].t0y = _size/32.0f;
//    //
//    pRenderMesh->setVertexType(E_VF_V3_T0);
//    SVDataSwapPtr t_data = MakeSharedPtr<SVDataSwap>();
//    t_data->writeData(pVer, sizeof(V3_T0) * 4);
//    pRenderMesh->setDrawVertNum(4);
//    pRenderMesh->setVertexData(t_data);
//    pRenderMesh->setDrawMethod(E_DRAW_TRIANGLE_STRIP);
//    pRenderMesh->createMesh();
//    return pRenderMesh;
    return nullptr;
}
