//
// SVComData.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVComData.h"
#include "SVFaceMesh.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../event/SVEvent.h"
#include "../base/SVDataSwap.h"
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

SVComData::SVComData(SVInstPtr _app)
:SVEventProc(_app) {
    m_screenMesh = nullptr;
}

SVComData::~SVComData() {
    destroy();
}

void SVComData::init() {
}

void SVComData::destroy() {
    m_screenMesh = nullptr;
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
    m_faceMesh = SVFaceMesh::createFaceMeshSt(mApp,true);
}

//SVFaceMeshPtr SVComData::faceMesh(s32 _type) {
//    //根据不同算法，获取不同算法的标准脸
//    if(_type == 1) {
//        m_faceMesh = MakeSharedPtr<SVRenderMesh>(mApp);
//        //索引描述
//        SVIndexStreamDspPtr t_index_dsp = MakeSharedPtr<SVIndexStreamDsp>();
//        t_index_dsp->setIndexCnt(6);
//        t_index_dsp->setBufType(E_BFT_STATIC_DRAW);
//        t_index_dsp->setStreamData(m_rect_index, 6*sizeof(u16));
//        m_screenMesh->setIndexDsp(t_index_dsp);
//        //顶点描述
//        SVVertStreamDspPtr t_vert_dsp= MakeSharedPtr<SVVertStreamDsp>(E_BFM_SOA);
//        t_vert_dsp->push(E_VF_V2);
//        t_vert_dsp->push(E_VF_T0);
//        t_vert_dsp->setBufType(E_BFT_STATIC_DRAW);
//        t_vert_dsp->setVertCnt(4);
//        t_vert_dsp->setMixStreamData(m_screen_rect_v2_t0, 16*sizeof(f32));
//        m_faceMesh->setVertDsp(t_vert_dsp);
//        //设置绘制方法
//        m_faceMesh->setDrawMethod(E_DRAW_TRIANGLES);
//        m_faceMesh->setDrawVertNum(6);
//        m_faceMesh->dispatch();
//    } else {
//        
//    }
//    return nullptr;
//}

#define IDX(_x_, _y_) ((_y_)*rx + (_x_))
SVRenderMeshPtr SVComData::generatePatchMesh(FVec3 &_corner00, FVec3 &_corner10, FVec3 &_corner01, FVec3 &_corner11, s32 _rx, s32 _ry){
    if (_rx < 2 || _ry < 2) {
        return nullptr;
    }
    const s32 rx = _rx;
    const s32 ry = _ry;
    //渲染数据
    //顶点数据
    V3 t_verData[rx*ry];
    for (s32 iy = 0; iy<ry; iy++) {
        FVec3 y0 = FVec3_zero;
        FVec3 y1 = FVec3_zero;
        const f32 t_y = iy / (f32)(ry - 1);
        lerp(y0, _corner00, _corner01, t_y);
        lerp(y1, _corner10, _corner11, t_y);
        for (s32 ix = 0; ix<rx; ix++) {
            const f32 t_x = ix / (f32)(rx - 1);
            s32 idx = IDX(ix, iy);
            FVec3 x0 = FVec3_zero;
            lerp(x0, y0, y1, t_x);
            t_verData[idx].x = x0.x;
            t_verData[idx].y = x0.y;
            t_verData[idx].z = x0.z;
        }
    }
    //网格数据
    s32 t_indexCount = (rx - 1)*(ry - 1)*6;
    u16 indexes[t_indexCount];
    s32 index = 0;
    for (s32 iy = 0; iy < ry; iy++) {
        for (s32 ix = 0; ix < rx; ix++) {
            const bool mdx = (ix + 1) < rx;
            const bool mdy = (iy + 1) < ry;
            if (mdx && mdy) {
                if ((ix + iy) & 1) {
                    indexes[index++] = IDX(ix, iy);
                    indexes[index++] = IDX(ix + 1, iy);
                    indexes[index++] = IDX(ix + 1, iy + 1);
                    
                    indexes[index++] = IDX(ix, iy);
                    indexes[index++] = IDX(ix + 1, iy + 1);
                    indexes[index++] = IDX(ix, iy + 1);
                }else {
                    indexes[index++] = IDX(ix, iy + 1);
                    indexes[index++] = IDX(ix, iy);
                    indexes[index++] = IDX(ix + 1, iy);
                    
                    indexes[index++] = IDX(ix, iy + 1);
                    indexes[index++] = IDX(ix + 1, iy);
                    indexes[index++] = IDX(ix + 1, iy + 1);
                }
            }
        }
    }
    //混合顶点数据
    V3 vertexData[t_indexCount];
    for (s32 i = 0; i<t_indexCount; i++) {
        s32 t_index = indexes[i];
        vertexData[i] = t_verData[t_index];
    }
    const s32 t_vertexCount = t_indexCount;
    SVDataSwapPtr t_pVertexData = MakeSharedPtr<SVDataSwap>();
    t_pVertexData->writeData(&vertexData[0], sizeof(V3)*t_vertexCount);
    
    SVRenderMeshPtr patchMesh = nullptr;// MakeSharedPtr<SVRenderMesh>(mApp);
//    patchMesh->setVertexType(E_VF_V3);
//    patchMesh->setDrawVertNum(t_vertexCount);
//    patchMesh->setVertexData(t_pVertexData);
//    patchMesh->setDrawMethod(E_DRAW_LINES);
//    patchMesh->createMesh();
    return patchMesh;
}

//void SVComData::_initTwoDivisionMesh(){
//    //二分屏
//    //m_screenTwoDivisionMesh  = MakeSharedPtr<SVRenderMesh>(mApp);
//    m_screenTwoDivisionMesh->setVertexType(E_VF_V2_C_T0);
//    m_screenTwoDivisionMesh->setDrawMethod(E_DRAW_TRIANGLES);
//
//    SVDataSwapPtr t_pMeshData_TwoVidion = MakeSharedPtr<SVDataSwap>();
//    //渲染数据
//    V2_C_T0 VerData[12];
//    //颜色
//    for (s32 i=0; i<12; i++) {
//        VerData[i].r = 255;
//        VerData[i].g = 255;
//        VerData[i].b = 255;
//        VerData[i].a = 255;
//    }
//    //纹理
//    for (s32 i = 0; i<2; i++) {
//        VerData[i*6].t0x = 0.0f;
//        VerData[i*6].t0y = 0.0f;
//        VerData[i*6+1].t0x = 1.0f;
//        VerData[i*6+1].t0y = 0.0f;
//        VerData[i*6+2].t0x = 0.0f;
//        VerData[i*6+2].t0y = 1.0f;
//        VerData[i*6+3].t0x = 0.0f;
//        VerData[i*6+3].t0y = 1.0f;
//        VerData[i*6+4].t0x = 1.0f;
//        VerData[i*6+4].t0y = 0.0f;
//        VerData[i*6+5].t0x = 1.0f;
//        VerData[i*6+5].t0y = 1.0f;
//    }
//    //(0,1) (1,1)
//    //(-1,0)(1,0)
//    // ---------
//    //(-1,0) (1,0)
//    //(-1,-1)(1,-1)
//    VerData[0].x = -1.0f;
//    VerData[0].y = -1.0f;
//    VerData[1].x = 1.0f;
//    VerData[1].y = -1.0f;
//    VerData[2].x = -1.0f;
//    VerData[2].y = 0.0f;
//    VerData[3].x = -1.0f;
//    VerData[3].y = 0.0f;
//    VerData[4].x = 1.0f;
//    VerData[4].y = -1.0f;
//    VerData[5].x = 1.0f;
//    VerData[5].y = 0.0f;
//    VerData[6].x = -1.0f;
//    VerData[6].y = 0.0f;
//    VerData[7].x = 1.0f;
//    VerData[7].y = 0.0f;
//    VerData[8].x = -1.0f;
//    VerData[8].y = 1.0f;
//    VerData[9].x = -1.0f;
//    VerData[9].y = 1.0f;
//    VerData[10].x = 1.0f;
//    VerData[10].y = 0.0f;
//    VerData[11].x = 1.0f;
//    VerData[11].y = 1.0f;
//    t_pMeshData_TwoVidion->writeData(&VerData[0],sizeof(V2_C_T0)*12);
//    m_screenTwoDivisionMesh->setDrawVertNum(12);
//    m_screenTwoDivisionMesh->setVertexData(t_pMeshData_TwoVidion);
//    m_screenTwoDivisionMesh->createMesh();
//}

//void SVComData::_initFourDivisionMesh(){
//    //四分屏
//    //m_screenFourDivisionMesh  = MakeSharedPtr<SVRenderMesh>(mApp);
//    m_screenFourDivisionMesh->setVertexType(E_VF_V2_C_T0);
//    m_screenFourDivisionMesh->setDrawMethod(E_DRAW_TRIANGLES);
//    SVDataSwapPtr t_pMeshData_FourVidion = MakeSharedPtr<SVDataSwap>();
//    //渲染数据
//    V2_C_T0 VerData[24];
//    //颜色
//    for (s32 i = 0; i<24; i++) {
//        VerData[i].r = 255;
//        VerData[i].g = 255;
//        VerData[i].b = 255;
//        VerData[i].a = 255;
//    }
//    //纹理
//    for (s32 i = 0; i<4; i++) {
//        VerData[i*6].t0x = 0.0f;
//        VerData[i*6].t0y = 0.0f;
//        VerData[i*6+1].t0x = 1.0f;
//        VerData[i*6+1].t0y = 0.0f;
//        VerData[i*6+2].t0x = 0.0f;
//        VerData[i*6+2].t0y = 1.0f;
//        VerData[i*6+3].t0x = 0.0f;
//        VerData[i*6+3].t0y = 1.0f;
//        VerData[i*6+4].t0x = 1.0f;
//        VerData[i*6+4].t0y = 0.0f;
//        VerData[i*6+5].t0x = 1.0f;
//        VerData[i*6+5].t0y = 1.0f;
//    }
//    //(-1,1)(0,1)   | (0,1) (1,1)
//    //(-1,0)(0,0)   | (0,0) (1,0)
//    // ---------    | -----------
//    //(-1,0) (0,0)  | (0,0) (1,0)
//    //(-1,-1)(0,-1) | (0,-1)(1,-1)
//    //顶点
//    VerData[0].x = -1.0f;
//    VerData[0].y = -1.0f;
//    VerData[1].x = 0.0f;
//    VerData[1].y = -1.0f;
//    VerData[2].x = -1.0f;
//    VerData[2].y = 0.0f;
//    VerData[3].x = -1.0f;
//    VerData[3].y = 0.0f;
//    VerData[4].x = 0.0f;
//    VerData[4].y = -1.0f;
//    VerData[5].x = 0.0f;
//    VerData[5].y = 0.0f;
//
//    VerData[6].x = 0.0f;
//    VerData[6].y = -1.0f;
//    VerData[7].x = 1.0f;
//    VerData[7].y = -1.0f;
//    VerData[8].x = 0.0f;
//    VerData[8].y = 0.0f;
//    VerData[9].x = 0.0f;
//    VerData[9].y = 0.0f;
//    VerData[10].x = 1.0f;
//    VerData[10].y = -1.0f;
//    VerData[11].x = 1.0f;
//    VerData[11].y = 0.0f;
//
//    VerData[12].x = -1.0f;
//    VerData[12].y = 0.0f;
//    VerData[13].x = 0.0f;
//    VerData[13].y = 0.0f;
//    VerData[14].x = -1.0f;
//    VerData[14].y = 1.0f;
//    VerData[15].x = -1.0f;
//    VerData[15].y = 1.0f;
//    VerData[16].x = 0.0f;
//    VerData[16].y = 0.0f;
//    VerData[17].x = 0.0f;
//    VerData[17].y = 1.0f;
//
//    VerData[18].x = 0.0f;
//    VerData[18].y = 0.0f;
//    VerData[19].x = 1.0f;
//    VerData[19].y = 0.0f;
//    VerData[20].x = 0.0f;
//    VerData[20].y = 1.0f;
//    VerData[21].x = 0.0f;
//    VerData[21].y = 1.0f;
//    VerData[22].x = 1.0f;
//    VerData[22].y = 0.0f;
//    VerData[23].x = 1.0f;
//    VerData[23].y = 1.0f;
//
//    t_pMeshData_FourVidion->writeData(&VerData[0],sizeof(V2_C_T0)*24);
//
//    m_screenFourDivisionMesh->setDrawVertNum(24);
//    m_screenFourDivisionMesh->setVertexData(t_pMeshData_FourVidion);
//    m_screenFourDivisionMesh->createMesh();
//}
//
//void SVComData::_initFourDivisionMesh_X(){
//    //四分屏
//    //m_screenFourXDivisionMesh  = MakeSharedPtr<SVRenderMesh>(mApp);
//    m_screenFourXDivisionMesh->setVertexType(E_VF_V2_C_T0);
//    m_screenFourXDivisionMesh->setDrawMethod(E_DRAW_TRIANGLES);
//    SVDataSwapPtr t_pMeshData_FourVidion = MakeSharedPtr<SVDataSwap>();
//    //渲染数据
//    V2_C_T0 VerData[12];
//    //颜色
//    for (s32 i = 0; i<12; i++) {
//        VerData[i].r = 255;
//        VerData[i].g = 255;
//        VerData[i].b = 255;
//        VerData[i].a = 255;
//    }
//    //纹理
//    for (s32 i = 0; i<4; i++) {
//        VerData[i*3].t0x = 0.0f;
//        VerData[i*3].t0y = 0.0f;
//        VerData[i*3+1].t0x = 1.0f;
//        VerData[i*3+1].t0y = 0.0f;
//        VerData[i*3+2].t0x = 0.5f;
//        VerData[i*3+2].t0y = 0.5f;
//    }
//    //          \                                /
//    //           \                              /
//    //            \                            /
//    //             \                          /
//    //              \                        /
//    //               \                      /
//    //                \                    /
//    //                 \   (-1,1)(1,1)    /
//    //                  \     (0,0)      /
//    //                   \              /
//    //                    \            /
//    //                     \          /
//    //                      \        /
//    //                       \      /
//    //                        \    /
//    //                         \  /
//    //         (0,0)            \/           (0,0)
//    //     (-1,1)(-1,-1)        /\        (1,-1)(1,1)
//    //                         /  \
//    //                        /    \
//    //                       /      \
//    //                      /        \
//    //                     /          \
//    //                    /            \
//    //                   /              \
//    //                  /      (0,0)     \
//    //                 /   (-1,-1)(1,-1)  \
//    //                /                    \
//    //               /                      \
//    //              /                        \
//    //             /                          \
//    //            /                            \
//    //           /                              \
//    //
//    //
//    //
//    //顶点
//    VerData[0].x = -1.0f;
//    VerData[0].y = -1.0f;
//    VerData[1].x = 1.0f;
//    VerData[1].y = -1.0f;
//    VerData[2].x = 0.0f;
//    VerData[2].y = 0.0f;
//
//    VerData[3].x = 1.0f;
//    VerData[3].y = -1.0f;
//    VerData[4].x = 1.0f;
//    VerData[4].y = 1.0f;
//    VerData[5].x = 0.0f;
//    VerData[5].y = 0.0f;
//
//    VerData[6].x = 1.0f;
//    VerData[6].y = 1.0f;
//    VerData[7].x = -1.0f;
//    VerData[7].y = 1.0f;
//    VerData[8].x = 0.0f;
//    VerData[8].y = 0.0f;
//
//    VerData[9].x = -1.0f;
//    VerData[9].y = 1.0f;
//    VerData[10].x = -1.0f;
//    VerData[10].y = -1.0f;
//    VerData[11].x = 0.0f;
//    VerData[11].y = 0.0f;
//    t_pMeshData_FourVidion->writeData(&VerData[0],sizeof(V2_C_T0)*12);
//
//    m_screenFourXDivisionMesh->setDrawVertNum(12);
//    m_screenFourXDivisionMesh->setVertexData(t_pMeshData_FourVidion);
//    m_screenFourXDivisionMesh->createMesh();
//}


////单位1的基本矩形
//void SVComData::_initBaseRect(){
//    //0 1 2 2 1 3
//    m_baseRect[0].x = -0.5f;
//    m_baseRect[0].y = -0.5f;
//    m_baseRect[0].z = 0.0f;
//    m_baseRect[0].t0x = 0.0f;
//    m_baseRect[0].t0y = 0.0f;
//    m_baseRect[0].r = 255;
//    m_baseRect[0].g = 255;
//    m_baseRect[0].b = 255;
//    m_baseRect[0].a = 255;
//    
//    m_baseRect[1].x = 0.5f;
//    m_baseRect[1].y = -0.5f;
//    m_baseRect[1].z = 0.0f;
//    m_baseRect[1].t0x = 1.0f;
//    m_baseRect[1].t0y = 0.0f;
//    m_baseRect[1].r = 255;
//    m_baseRect[1].g = 255;
//    m_baseRect[1].b = 255;
//    m_baseRect[1].a = 255;
//    
//    m_baseRect[2].x = -0.5f;
//    m_baseRect[2].y = 0.5f;
//    m_baseRect[2].z = 0.0f;
//    m_baseRect[2].t0x = 0.0f;
//    m_baseRect[2].t0y = 1.0f;
//    m_baseRect[2].r = 255;
//    m_baseRect[2].g = 255;
//    m_baseRect[2].b = 255;
//    m_baseRect[2].a = 255;
//    
//    m_baseRect[3].x = -0.5f;
//    m_baseRect[3].y = 0.5f;
//    m_baseRect[3].z = 0.0f;
//    m_baseRect[3].t0x = 0.0f;
//    m_baseRect[3].t0y = 1.0f;
//    m_baseRect[3].r = 255;
//    m_baseRect[3].g = 255;
//    m_baseRect[3].b = 255;
//    m_baseRect[3].a = 255;
//    
//    m_baseRect[4].x = 0.5f;
//    m_baseRect[4].y = -0.5f;
//    m_baseRect[4].z = 0.0f;
//    m_baseRect[4].t0x = 1.0f;
//    m_baseRect[4].t0y = 0.0f;
//    m_baseRect[4].r = 255;
//    m_baseRect[4].g = 255;
//    m_baseRect[4].b = 255;
//    m_baseRect[4].a = 255;
//    
//    m_baseRect[5].x = 0.5f;
//    m_baseRect[5].y = 0.5f;
//    m_baseRect[5].z = 0.0f;
//    m_baseRect[5].t0x = 1.0f;
//    m_baseRect[5].t0y = 1.0f;
//    m_baseRect[5].r = 255;
//    m_baseRect[5].g = 255;
//    m_baseRect[5].b = 255;
//    m_baseRect[5].a = 255;
//}
