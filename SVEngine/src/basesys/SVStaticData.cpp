//
// SVStaticData.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVStaticData.h"
#include "SVFaceDataMesh.h"
#include "../app/SVInst.h"
#include "../base/SVDataSwap.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

//V3_C_T0 SVStaticData::m_baseRect[6];


static f32 m_data_rect_v3_c_t0[] = {
    -1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
    -1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
    -1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
    -1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f
};

static f32 m_data_rect_v3_t0[] = {
    -1.0f,-1.0f,0.0f,0.0f,
    -1.0f,-1.0f,0.0f,0.0f,
    -1.0f,-1.0f,0.0f,0.0f,
    -1.0f,-1.0f,0.0f,0.0f
};

SVStaticData::SVStaticData(SVInstPtr _app)
:SVGBaseEx(_app) {
    m_screenMesh = nullptr;
    m_screenAdaptMesh = nullptr;
    m_faceDataMesh = nullptr;
}

SVStaticData::~SVStaticData() {
    destroy();
}

void SVStaticData::init() {
    m_screenMesh = MakeSharedPtr<SVRenderMesh>(mApp);
    m_screenMesh->setVertexType(E_VF_V2_C_T0);
    u16 t_index[6] = {0, 1, 2, 2, 1, 3};
    SVDataSwapPtr t_pIndexData = MakeSharedPtr<SVDataSwap>();
    t_pIndexData->writeData(t_index,sizeof(u16)*6);
    m_screenMesh->setIndexData(t_pIndexData,6);
    //
    SVDataSwapPtr t_pMeshData = MakeSharedPtr<SVDataSwap>();
    //渲染数据
//    V2_T0 VerData[4];
//    //
//    VerData[0].t0x = c;
//    VerData[0].t0y = 0.0f;
//    VerData[1].t0x = 1.0f;
//    VerData[1].t0y = 0.0f;
//    VerData[2].t0x = 0.0f;
//    VerData[2].t0y = 1.0f;
//    VerData[3].t0x = 1.0f;
//    VerData[3].t0y = 1.0f;
//    //
//    VerData[0].x = -1.0f;
//    VerData[0].y = -1.0f;
//    VerData[1].x = 1.0f;
//    VerData[1].y = -1.0f;
//    VerData[2].x = -1.0f;
//    VerData[2].y = 1.0f;
//    VerData[3].x = 1.0f;
//    VerData[3].y = 1.0f;
//    t_pMeshData->writeData(&VerData[0],sizeof(V2_T0)*4);
//    //
//    VerData[0].x = -1.0f;
//    VerData[0].y = 0.0f;
//    VerData[1].x = 0.0f;
//    VerData[1].y = 0.0f;
//    VerData[2].x = -1.0f;
//    VerData[2].y = 1.0f;
//    VerData[3].x = 0.0f;
//    VerData[3].y = 1.0f;
//    m_screenMesh->setVertNum(4);
//    m_screenMesh->setVertexData(t_pMeshData);
//    m_screenMesh->createMesh();
//    //
//    m_faceDataMesh = MakeSharedPtr<SVFaceDataMesh>(mApp);
//    m_faceDataMesh->init();
}

SVRenderMeshPtr SVStaticData::generateAdaptScreenMesh(f32 _fromW, f32 _fromH, f32 _toW, f32 _toH){
    f32 _tarW = _toW;
    f32 _tarH = _toH;
    f32 _srcW = _fromW;
    f32 _srcH = _fromH;
    if ((_tarW > _srcW) || (_tarH > _srcH)) {
        return m_screenMesh;
    }
    f32 t_tar_scale = _tarW/_tarH;
    f32 t_src_scale = _srcW/_srcH;
    if (t_tar_scale == t_src_scale) {
        return m_screenMesh;
    }
    SVDataSwapPtr t_pMeshDataAdapt = MakeSharedPtr<SVDataSwap>();
    //渲染数据
    V2_C_T0 VerData[4];
    //颜色
    VerData[0].r = 255;
    VerData[0].g = 255;
    VerData[0].b = 255;
    VerData[0].a = 255;
    VerData[1].r = 255;
    VerData[1].g = 255;
    VerData[1].b = 255;
    VerData[1].a = 255;
    VerData[2].r = 255;
    VerData[2].g = 255;
    VerData[2].b = 255;
    VerData[2].a = 255;
    VerData[3].r = 255;
    VerData[3].g = 255;
    VerData[3].b = 255;
    VerData[3].a = 255;
    //
    if (t_tar_scale < t_src_scale) {
        VerData[0].t0x = ((_srcW - _tarW*(_srcH/_tarH))/_srcW)*0.5f;
        VerData[0].t0y = 0.0f;
        VerData[1].t0x = 1.0f - ((_srcW - _tarW*(_srcH/_tarH))/_srcW)*0.5f;
        VerData[1].t0y = 0.0f;
        VerData[2].t0x = ((_srcW - _tarW*(_srcH/_tarH))/_srcW)*0.5f;
        VerData[2].t0y = 1.0f;
        VerData[3].t0x = 1.0f - ((_srcW - _tarW*(_srcH/_tarH))/_srcW)*0.5f;
        VerData[3].t0y = 1.0f;
    }else{
        VerData[0].t0x = 0.0f;
        VerData[0].t0y = ((_srcH - _tarH*(_srcW/_tarW))/_srcH)*0.5f;
        VerData[1].t0x = 1.0f;
        VerData[1].t0y = ((_srcH -  _tarH*(_srcW/_tarW))/_srcH)*0.5f;;
        VerData[2].t0x = 0.0f;
        VerData[2].t0y = 1.0f - ((_srcH -  _tarH*(_srcW/_tarW))/_srcH)*0.5f;;
        VerData[3].t0x = 1.0f;
        VerData[3].t0y = 1.0f - ((_srcH -  _tarH*(_srcW/_tarW))/_srcH)*0.5f;;
    }
    //
    VerData[0].x = -1.0f;
    VerData[0].y = -1.0f;
    VerData[1].x = 1.0f;
    VerData[1].y = -1.0f;
    VerData[2].x = -1.0f;
    VerData[2].y = 1.0f;
    VerData[3].x = 1.0f;
    VerData[3].y = 1.0f;
    t_pMeshDataAdapt->writeData(&VerData[0],sizeof(V2_C_T0)*4);
    m_screenAdaptMesh->setVertNum(4);
    m_screenAdaptMesh->setVertexData(t_pMeshDataAdapt);
    m_screenAdaptMesh->createMesh();
    return m_screenAdaptMesh;
}

#define IDX(_x_, _y_) ((_y_)*rx + (_x_))
SVRenderMeshPtr SVStaticData::generatePatchMesh(FVec3 &_corner00, FVec3 &_corner10, FVec3 &_corner01, FVec3 &_corner11, s32 _rx, s32 _ry){
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
    
    SVRenderMeshPtr patchMesh =nullptr;// MakeSharedPtr<SVRenderMesh>(mApp);
    patchMesh->setVertexType(E_VF_V3);
    patchMesh->setVertNum(t_vertexCount);
    patchMesh->setVertexData(t_pVertexData);
    patchMesh->setDrawMethod(E_DM_LINES);
    patchMesh->createMesh();
    return patchMesh;
}

void SVStaticData::destroy() {
    m_screenMesh        = nullptr;
    m_screenAdaptMesh = nullptr;
    m_faceDataMesh       = nullptr;
}

SVFaceDataMeshPtr SVStaticData::getFaceDataMesh(){
    return m_faceDataMesh;
}

//void SVStaticData::_initTwoDivisionMesh(){
//    //二分屏
//    //m_screenTwoDivisionMesh  = MakeSharedPtr<SVRenderMesh>(mApp);
//    m_screenTwoDivisionMesh->setVertexType(E_VF_V2_C_T0);
//    m_screenTwoDivisionMesh->setDrawMethod(E_DM_TRIANGLES);
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
//    m_screenTwoDivisionMesh->setVertNum(12);
//    m_screenTwoDivisionMesh->setVertexData(t_pMeshData_TwoVidion);
//    m_screenTwoDivisionMesh->createMesh();
//}

//void SVStaticData::_initFourDivisionMesh(){
//    //四分屏
//    //m_screenFourDivisionMesh  = MakeSharedPtr<SVRenderMesh>(mApp);
//    m_screenFourDivisionMesh->setVertexType(E_VF_V2_C_T0);
//    m_screenFourDivisionMesh->setDrawMethod(E_DM_TRIANGLES);
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
//    m_screenFourDivisionMesh->setVertNum(24);
//    m_screenFourDivisionMesh->setVertexData(t_pMeshData_FourVidion);
//    m_screenFourDivisionMesh->createMesh();
//}
//
//void SVStaticData::_initFourDivisionMesh_X(){
//    //四分屏
//    //m_screenFourXDivisionMesh  = MakeSharedPtr<SVRenderMesh>(mApp);
//    m_screenFourXDivisionMesh->setVertexType(E_VF_V2_C_T0);
//    m_screenFourXDivisionMesh->setDrawMethod(E_DM_TRIANGLES);
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
//    m_screenFourXDivisionMesh->setVertNum(12);
//    m_screenFourXDivisionMesh->setVertexData(t_pMeshData_FourVidion);
//    m_screenFourXDivisionMesh->createMesh();
//}


////单位1的基本矩形
//void SVStaticData::_initBaseRect(){
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
