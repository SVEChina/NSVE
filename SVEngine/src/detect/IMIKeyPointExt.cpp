//
// IMIKeyPointExt.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIKeyPointExt.h"
#include "../core/IMIMathHelper.h"
#include "../base/IMICoreMath.h"

using namespace imi;

void IMIKeyPointExt::faceDataForEyes(f32 *faceLandMark, f32 *eyesPts, s32 &eyesPtsCount){
    s32 t_eyePtIndex = 0;
    //脸部竖直方向
    FVec2 vertical_dir_up = (FVec2(faceLandMark[2*43], faceLandMark[2*43+1]) - FVec2(faceLandMark[2*45], faceLandMark[2*45+1])).normalize();
    FVec2 vertical_dir_down = -vertical_dir_up;
    //脸部横向方向
    FVec2 horizontal_dir_left = (FVec2(faceLandMark[2*104], faceLandMark[2*104+1]) - FVec2(faceLandMark[2*105], faceLandMark[2*105+1])).normalize();
    FVec2 horizontal_dir_right = -horizontal_dir_left;
    FVec2 t_pt_104(faceLandMark[2*104], faceLandMark[2*104+1]);
    FVec2 t_pt_105(faceLandMark[2*105], faceLandMark[2*105+1]);
    f32 t_eyeDis = (t_pt_104 - t_pt_105).length();
    //左眼处理
    s32 t_lefteye_pointsIndex[8] = {52, 53, 72, 54, 55, 56, 73, 57};
    V2 t_lefteye_point[8];
    for (s32 i = 0; i<8; i++) {
        s32 t_index = t_lefteye_pointsIndex[i];
        t_lefteye_point[i].x = faceLandMark[2*t_index];
        t_lefteye_point[i].y = faceLandMark[2*t_index+1];
    }
    V2 t_lefteye_curvePoint[60];
    s32 t_lefteye_curvePointNum = 0   ;
    IMIMathHelper::createCurve(t_lefteye_point, 8, 2,t_lefteye_curvePoint, t_lefteye_curvePointNum, true);
    FVec2 t_pt_72(faceLandMark[2*72], faceLandMark[2*72+1]);
    FVec2 t_pt_n_72 = t_pt_72+vertical_dir_up*t_eyeDis*0.15;
    for (s32 i = 0; i<t_lefteye_curvePointNum; i++) {
        V2 pt = t_lefteye_curvePoint[i];
        eyesPts[2*t_eyePtIndex] = pt.x;
        eyesPts[2*t_eyePtIndex+1] = pt.y;
        t_eyePtIndex++;
        FVec2 t_pt = FVec2(pt.x, pt.y);
        if (i>t_lefteye_curvePointNum/2) {
            FVec2 t_n_pt = t_pt+vertical_dir_down*t_eyeDis*0.15;
            eyesPts[2*t_eyePtIndex] = t_n_pt.x;
            eyesPts[2*t_eyePtIndex+1] = t_n_pt.y;
            t_eyePtIndex++;
        }else{
//            FVec2 t_n_pt = t_pt - t_pt_n_72;
//            t_n_pt.y = 0.006*pow(t_n_pt.x, 2.0);
//            t_n_pt =  t_n_pt+t_pt_n_72;
//            eyesPts[2*t_eyePtIndex] = t_n_pt.x;
//            eyesPts[2*t_eyePtIndex+1] = t_n_pt.y;
//            t_eyePtIndex++;
        }
    }
    
    for (s32 i = 0; i<6; i++) {
        f32 t_delta_len_h = i*t_eyeDis*0.048;
        FVec2 t_n_pt = t_pt_n_72 + horizontal_dir_left*t_delta_len_h;
        eyesPts[2*t_eyePtIndex] = t_n_pt.x;
        eyesPts[2*t_eyePtIndex+1] = t_n_pt.y;
        t_eyePtIndex++;
    }
    for (s32 i = 0; i<6; i++) {
        f32 t_delta_len = i*t_eyeDis*0.048;
        FVec2 t_n_pt = (t_pt_n_72 + horizontal_dir_right*t_delta_len);
        eyesPts[2*t_eyePtIndex] = t_n_pt.x;
        eyesPts[2*t_eyePtIndex+1] = t_n_pt.y;
        t_eyePtIndex++;
    }
    
    //右眼处理
    V2 t_righteye_point[8];
    s32 t_righteye_pointsIndex[8] = {58, 59, 75, 60, 61, 62, 76, 63};
    for (s32 i = 0; i<8; i++) {
        s32 t_index = t_righteye_pointsIndex[i];
        t_righteye_point[i].x = faceLandMark[2*t_index];
        t_righteye_point[i].y = faceLandMark[2*t_index+1];
    }
    V2 t_righteye_curvePoint[60];
    s32 t_righteye_curvePointNum = 0;
    IMIMathHelper::createCurve(t_righteye_point, 8, 2,t_righteye_curvePoint, t_righteye_curvePointNum, true);
    for (s32 i = 0; i<t_righteye_curvePointNum; i++) {
        V2 pt = t_righteye_curvePoint[i];
        eyesPts[2*t_eyePtIndex] = pt.x;
        eyesPts[2*t_eyePtIndex+1] = pt.y;
        t_eyePtIndex++;
        FVec2 t_pt(pt.x, pt.y);
        FVec2 t_vertical_dir = vertical_dir_up;
        if (i>t_righteye_curvePointNum/2) {
            FVec2 t_n_pt = t_pt+vertical_dir_down*t_eyeDis*0.15;
            eyesPts[2*t_eyePtIndex] = t_n_pt.x;
            eyesPts[2*t_eyePtIndex+1] = t_n_pt.y;
            t_eyePtIndex++;
        }
    }
    FVec2 t_pt_75(faceLandMark[2*75], faceLandMark[2*75+1]);
    FVec2 t_pt_n_75 = t_pt_75+vertical_dir_up*t_eyeDis*0.15;
    for (s32 i = 0; i<6; i++) {
        f32 t_delta_len_h = i*t_eyeDis*0.048;
        FVec2 t_n_pt = t_pt_n_75 + horizontal_dir_left*t_delta_len_h;
        eyesPts[2*t_eyePtIndex] = t_n_pt.x;
        eyesPts[2*t_eyePtIndex+1] = t_n_pt.y;
        t_eyePtIndex++;
    }
    for (s32 i = 0; i<6; i++) {
        f32 t_delta_len = i*t_eyeDis*0.048;
        FVec2 t_n_pt = (t_pt_n_75 + horizontal_dir_right*t_delta_len);
        eyesPts[2*t_eyePtIndex] = t_n_pt.x;
        eyesPts[2*t_eyePtIndex+1] = t_n_pt.y;
        t_eyePtIndex++;
    }
    //四周的点
    V2 t_lefteye_center_pt;
    t_lefteye_center_pt.x = faceLandMark[2*104];
    t_lefteye_center_pt.y = faceLandMark[2*104+1];
    V2 t_lefteye_left1_pt;
    _generateDirPt(t_lefteye_center_pt, horizontal_dir_left, t_lefteye_left1_pt, t_eyeDis*0.42);
    eyesPts[2*t_eyePtIndex] = t_lefteye_left1_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_lefteye_left1_pt.y;
    t_eyePtIndex++;
    V2 t_lefteye_left2_pt;
    _generateDirPt(t_lefteye_left1_pt, vertical_dir_up, t_lefteye_left2_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_lefteye_left2_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_lefteye_left2_pt.y;
    t_eyePtIndex++;
    V2 t_lefteye_left3_pt;
    _generateDirPt(t_lefteye_left1_pt, vertical_dir_down, t_lefteye_left3_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_lefteye_left3_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_lefteye_left3_pt.y;
    t_eyePtIndex++;
    V2 t_lefteye_left4_pt;
    _generateDirPt(t_lefteye_center_pt, horizontal_dir_right, t_lefteye_left4_pt, t_eyeDis*0.42);
    eyesPts[2*t_eyePtIndex] = t_lefteye_left4_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_lefteye_left4_pt.y;
    t_eyePtIndex++;
    V2 t_lefteye_left5_pt;
    _generateDirPt(t_lefteye_left4_pt, vertical_dir_up, t_lefteye_left5_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_lefteye_left5_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_lefteye_left5_pt.y;
    t_eyePtIndex++;
    V2 t_lefteye_left6_pt;
    _generateDirPt(t_lefteye_left4_pt, vertical_dir_down, t_lefteye_left6_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_lefteye_left6_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_lefteye_left6_pt.y;
    t_eyePtIndex++;
    //
    V2 t_righteye_center_pt;
    t_righteye_center_pt.x = faceLandMark[2*105];
    t_righteye_center_pt.y = faceLandMark[2*105+1];
    V2 t_righteye_left1_pt;
    _generateDirPt(t_righteye_center_pt, horizontal_dir_left, t_righteye_left1_pt, t_eyeDis*0.42);
    eyesPts[2*t_eyePtIndex] = t_righteye_left1_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_righteye_left1_pt.y;
    t_eyePtIndex++;
    V2 t_righteye_left2_pt;
    _generateDirPt(t_righteye_left1_pt, vertical_dir_up, t_righteye_left2_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_righteye_left2_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_righteye_left2_pt.y;
    t_eyePtIndex++;
    V2 t_righteye_left3_pt;
    _generateDirPt(t_righteye_left1_pt, vertical_dir_down, t_righteye_left3_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_righteye_left3_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_righteye_left3_pt.y;
    t_eyePtIndex++;
    V2 t_righteye_left4_pt;
    _generateDirPt(t_righteye_center_pt, horizontal_dir_right, t_righteye_left4_pt, t_eyeDis*0.42);
    eyesPts[2*t_eyePtIndex] = t_righteye_left4_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_righteye_left4_pt.y;
    t_eyePtIndex++;
    V2 t_righteye_left5_pt;
    _generateDirPt(t_righteye_left4_pt, vertical_dir_up, t_righteye_left5_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_righteye_left5_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_righteye_left5_pt.y;
    t_eyePtIndex++;
    V2 t_righteye_left6_pt;
    _generateDirPt(t_righteye_left4_pt, vertical_dir_down, t_righteye_left6_pt, t_eyeDis*0.24);
    eyesPts[2*t_eyePtIndex] = t_righteye_left6_pt.x;
    eyesPts[2*t_eyePtIndex+1] = t_righteye_left6_pt.y;
    t_eyePtIndex++;
    eyesPtsCount = t_eyePtIndex;
}

void IMIKeyPointExt::faceDataForEyeBrow(f32 *faceLandMark, f32 *eyebrowPts, s32 &eyebrowPtsCount){
    s32 t_eyePtIndex = 0;
    //脸部竖直方向
    FVec2 vertical_dir_up = (FVec2(faceLandMark[2*43], faceLandMark[2*43+1]) - FVec2(faceLandMark[2*45], faceLandMark[2*45+1])).normalize();
    FVec2 vertical_dir_down = -vertical_dir_up;
    //脸部横向方向
    FVec2 horizontal_dir_left = (FVec2(faceLandMark[2*104], faceLandMark[2*104+1]) - FVec2(faceLandMark[2*105], faceLandMark[2*105+1])).normalize();
    FVec2 horizontal_dir_right = -horizontal_dir_left;
    //左眉毛
    f32 t_lefteyebrow_height = (FVec2(faceLandMark[2*35], faceLandMark[2*35+1]) - FVec2(faceLandMark[2*65], faceLandMark[2*65+1])).length();
    s32 t_lefteyebrow_pointsIndex[9] = {33, 34, 35, 36, 37, 67, 66, 65, 64};
    V2 t_lefteyebrow_point[9];
    for (s32 i = 0; i<9; i++) {
        s32 t_index = t_lefteyebrow_pointsIndex[i];
        t_lefteyebrow_point[i].x = faceLandMark[2*t_index];
        t_lefteyebrow_point[i].y = faceLandMark[2*t_index+1];
    }
    V2 t_lefteyebrow_curvePoint[60];
    s32 t_lefteyebrow_curvePointNum = 0   ;
    IMIMathHelper::createCurve(t_lefteyebrow_point, 9, 1,t_lefteyebrow_curvePoint, t_lefteyebrow_curvePointNum, true);
    for (s32 i = 0; i<t_lefteyebrow_curvePointNum; i++) {
       V2 pt = t_lefteyebrow_curvePoint[i];
       eyebrowPts[2*t_eyePtIndex] = pt.x;
       eyebrowPts[2*t_eyePtIndex+1] = pt.y;
       t_eyePtIndex++;
       V2 t_tar;
        if (i<t_lefteyebrow_curvePointNum/2) {
            _generateDirPt(pt, vertical_dir_up, t_tar, t_lefteyebrow_height*0.8);
            eyebrowPts[2*t_eyePtIndex] = t_tar.x;
            eyebrowPts[2*t_eyePtIndex+1] = t_tar.y;
            t_eyePtIndex++;
        }else if (i>t_lefteyebrow_curvePointNum/2){
            _generateDirPt(pt, vertical_dir_down, t_tar, t_lefteyebrow_height*0.8);
            eyebrowPts[2*t_eyePtIndex] = t_tar.x;
            eyebrowPts[2*t_eyePtIndex+1] = t_tar.y;
            t_eyePtIndex++;
        }
    }
    //四周的点
    V2 t_lefteyebrow_33_pt;
    t_lefteyebrow_33_pt.x = faceLandMark[2*33];
    t_lefteyebrow_33_pt.y = faceLandMark[2*33+1];
    V2 t_lefteyebrow_37_pt;
    t_lefteyebrow_37_pt.x = faceLandMark[2*37];
    t_lefteyebrow_37_pt.y = faceLandMark[2*37+1];
    V2 t_lefteyebrow_67_pt;
    t_lefteyebrow_67_pt.x = faceLandMark[2*67];
    t_lefteyebrow_67_pt.y = faceLandMark[2*67+1];
    V2 t_lefteyebrow_left1_pt;
    _generateDirPt(t_lefteyebrow_33_pt, horizontal_dir_left, t_lefteyebrow_left1_pt, t_lefteyebrow_height*1.1);
    eyebrowPts[2*t_eyePtIndex] = t_lefteyebrow_left1_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_lefteyebrow_left1_pt.y;
    t_eyePtIndex++;
    V2 t_lefteyebrow_left2_pt;
    _generateDirPt(t_lefteyebrow_left1_pt, vertical_dir_up, t_lefteyebrow_left2_pt, t_lefteyebrow_height*0.8);
    eyebrowPts[2*t_eyePtIndex] = t_lefteyebrow_left2_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_lefteyebrow_left2_pt.y;
    t_eyePtIndex++;
    V2 t_lefteyebrow_left3_pt;
    _generateDirPt(t_lefteyebrow_left1_pt, vertical_dir_down, t_lefteyebrow_left3_pt, t_lefteyebrow_height*0.8);
    eyebrowPts[2*t_eyePtIndex] = t_lefteyebrow_left3_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_lefteyebrow_left3_pt.y;
    t_eyePtIndex++;
    V2 t_lefteyebrow_left4_pt;
    _generateDirPt(t_lefteyebrow_37_pt, horizontal_dir_right, t_lefteyebrow_left4_pt, t_lefteyebrow_height*1.1);
    eyebrowPts[2*t_eyePtIndex] = t_lefteyebrow_left4_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_lefteyebrow_left4_pt.y;
    t_eyePtIndex++;
    V2 t_lefteyebrow_left5_pt;
    _generateDirPt(t_lefteyebrow_67_pt, horizontal_dir_right, t_lefteyebrow_left5_pt, t_lefteyebrow_height*1.1);
    eyebrowPts[2*t_eyePtIndex] = t_lefteyebrow_left5_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_lefteyebrow_left5_pt.y;
    t_eyePtIndex++;
    //右眼眉毛
    f32 t_righteyebrow_height = (FVec2(faceLandMark[2*40], faceLandMark[2*40+1]) - FVec2(faceLandMark[2*70], faceLandMark[2*70+1])).length();
    s32 t_righteyebrow_pointsIndex[9] = {42, 41, 40, 39, 38, 68, 69, 70, 71};
    V2 t_righteyebrow_point[9];
    for (s32 i = 0; i<9; i++) {
        s32 t_index = t_righteyebrow_pointsIndex[i];
        t_righteyebrow_point[i].x = faceLandMark[2*t_index];
        t_righteyebrow_point[i].y = faceLandMark[2*t_index+1];
    }
    V2 t_righteyebrow_curvePoint[60];
    s32 t_righteyebrow_curvePointNum = 0   ;
    IMIMathHelper::createCurve(t_righteyebrow_point, 9, 1,t_righteyebrow_curvePoint, t_righteyebrow_curvePointNum, true);
    for (s32 i = 0; i<t_righteyebrow_curvePointNum; i++) {
       V2 pt = t_righteyebrow_curvePoint[i];
       eyebrowPts[2*t_eyePtIndex] = pt.x;
       eyebrowPts[2*t_eyePtIndex+1] = pt.y;
       t_eyePtIndex++;
       V2 t_tar;
        if (i<t_righteyebrow_curvePointNum/2) {
            _generateDirPt(pt, vertical_dir_up, t_tar, t_righteyebrow_height*0.8);
            eyebrowPts[2*t_eyePtIndex] = t_tar.x;
            eyebrowPts[2*t_eyePtIndex+1] = t_tar.y;
            t_eyePtIndex++;
        }else if (i>t_righteyebrow_curvePointNum/2){
            _generateDirPt(pt, vertical_dir_down, t_tar, t_righteyebrow_height*0.8);
            eyebrowPts[2*t_eyePtIndex] = t_tar.x;
            eyebrowPts[2*t_eyePtIndex+1] = t_tar.y;
            t_eyePtIndex++;
        }
    }
    //四周的点
    V2 t_righteyebrow_42_pt;
    t_righteyebrow_42_pt.x = faceLandMark[2*42];
    t_righteyebrow_42_pt.y = faceLandMark[2*42+1];
    V2 t_righteyebrow_38_pt;
    t_righteyebrow_38_pt.x = faceLandMark[2*38];
    t_righteyebrow_38_pt.y = faceLandMark[2*38+1];
    V2 t_righteyebrow_68_pt;
    t_righteyebrow_68_pt.x = faceLandMark[2*68];
    t_righteyebrow_68_pt.y = faceLandMark[2*68+1];
    V2 t_righteyebrow_right1_pt;
    _generateDirPt(t_righteyebrow_42_pt, horizontal_dir_right, t_righteyebrow_right1_pt, t_lefteyebrow_height*1.1);
    eyebrowPts[2*t_eyePtIndex] = t_righteyebrow_right1_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_righteyebrow_right1_pt.y;
    t_eyePtIndex++;
    V2 t_righteyebrow_right2_pt;
    _generateDirPt(t_righteyebrow_right1_pt, vertical_dir_up, t_righteyebrow_right2_pt, t_lefteyebrow_height*0.8);
    eyebrowPts[2*t_eyePtIndex] = t_righteyebrow_right2_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_righteyebrow_right2_pt.y;
    t_eyePtIndex++;
    V2 t_righteyebrow_right3_pt;
    _generateDirPt(t_righteyebrow_right1_pt, vertical_dir_down, t_righteyebrow_right3_pt, t_lefteyebrow_height*0.8);
    eyebrowPts[2*t_eyePtIndex] = t_righteyebrow_right3_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_righteyebrow_right3_pt.y;
    t_eyePtIndex++;
    V2 t_righteyebrow_left4_pt;
    _generateDirPt(t_righteyebrow_38_pt, horizontal_dir_left, t_righteyebrow_left4_pt, t_lefteyebrow_height*1.1);
    eyebrowPts[2*t_eyePtIndex] = t_righteyebrow_left4_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_righteyebrow_left4_pt.y;
    t_eyePtIndex++;
    V2 t_righteyebrow_left5_pt;
    _generateDirPt(t_righteyebrow_68_pt, horizontal_dir_left, t_righteyebrow_left5_pt, t_lefteyebrow_height*1.1);
    eyebrowPts[2*t_eyePtIndex] = t_righteyebrow_left5_pt.x;
    eyebrowPts[2*t_eyePtIndex+1] = t_righteyebrow_left5_pt.y;
    t_eyePtIndex++;
    eyebrowPtsCount = t_eyePtIndex;
}

void IMIKeyPointExt::faceDataForFaceWithHead(f32 *faceLandMark, f32 *facePts, s32 &facePtsCount){
    if (faceLandMark == nullptr || facePts == nullptr) {
        return;
    }
    s32 t_facePtsCount = 106;
    memcpy(facePts, faceLandMark, t_facePtsCount * 2 * sizeof(f32));
    FVec2 vertical_dir_up = (FVec2(faceLandMark[2*43], faceLandMark[2*43+1]) - FVec2(faceLandMark[2*45], faceLandMark[2*45+1])).normalize();
    FVec2 horizontal_dir_left = (FVec2(faceLandMark[2*104], faceLandMark[2*104+1]) - FVec2(faceLandMark[2*105], faceLandMark[2*105+1])).normalize();
    FVec2 horizontal_dir_right = -horizontal_dir_left;
    FVec2 t_pt_43(faceLandMark[2*43], faceLandMark[2*43+1]);
    FVec2 t_pt_49(faceLandMark[2*49], faceLandMark[2*49+1]);
    FVec2 t_pt_0(faceLandMark[0], faceLandMark[1]);
    FVec2 t_pt_32(faceLandMark[2*32], faceLandMark[2*32+1]);
    f32 t_faceLen = (t_pt_32 - t_pt_0).length();
    FVec2 t_pt_n_0 = t_pt_0 + vertical_dir_up*t_faceLen*0.8;
    for (s32 i = 0; i<10; i++) {
        f32 t_delta_len = i*t_faceLen*0.1;
        FVec2 t_n_pt = (t_pt_n_0 + horizontal_dir_right*t_delta_len);
        facePts[2*t_facePtsCount] = t_n_pt.x;
        facePts[2*t_facePtsCount+1] = t_n_pt.y;
        t_facePtsCount++;
    }
    facePtsCount = t_facePtsCount;
}

void IMIKeyPointExt::faceDataForWhole(f32 *faceLandMark, f32 *facePts, s32 &facePtsCount){
    if (faceLandMark == nullptr || facePts == nullptr) {
        return;
    }
    s32 t_facePtsCount = 106;
    memcpy(facePts, faceLandMark, t_facePtsCount * 2 * sizeof(f32));
    //嘴补点
    s32 t_toptip_pointsIndex[12] = {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95};
    V2 t_toptip_point[12];
    for (s32 i = 0; i<12; i++) {
        s32 t_index = t_toptip_pointsIndex[i];
        t_toptip_point[i].x = faceLandMark[2*t_index];
        t_toptip_point[i].y = faceLandMark[2*t_index+1];
    }
    V2 t_toptip_curvePoint[60];
    s32 t_toptip_curvePointNum = 0   ;
    IMIMathHelper::createCurve(t_toptip_point, 12, 2,t_toptip_curvePoint, t_toptip_curvePointNum, false);
    
    for (s32 i = 0; i < t_toptip_curvePointNum; i++) {
        V2 point = t_toptip_curvePoint[i];
        s32 index = t_facePtsCount * 2;
        facePts[index] = point.x;
        facePts[index + 1] = point.y;
        t_facePtsCount++;
    }
    s32 t_bottomtip_pointsIndex[8] = {96, 97, 98, 99, 100, 101, 102, 103};
    V2 t_bottomtip_point[8];
    for (s32 i = 0; i<8; i++) {
        s32 t_index = t_bottomtip_pointsIndex[i];
        t_bottomtip_point[i].x = faceLandMark[2*t_index];
        t_bottomtip_point[i].y = faceLandMark[2*t_index+1];
    }
    V2 t_bottomtip_curvePoint[60];
    s32 t_bottomtip_curvePointNum = 0   ;
    IMIMathHelper::createCurve(t_bottomtip_point, 8, 2,t_bottomtip_curvePoint, t_bottomtip_curvePointNum, false);
    
    for (s32 i = 0; i < t_bottomtip_curvePointNum; i++) {
        V2 point = t_bottomtip_curvePoint[i];
        s32 index = t_facePtsCount * 2;
        facePts[index] = point.x;
        facePts[index + 1] = point.y;
        t_facePtsCount++;
    }
    //补额头
    FVec2 vertical_dir_up = (FVec2(faceLandMark[2*43], faceLandMark[2*43+1]) - FVec2(faceLandMark[2*45], faceLandMark[2*45+1])).normalize();
    FVec2 horizontal_dir_left = (FVec2(faceLandMark[2*104], faceLandMark[2*104+1]) - FVec2(faceLandMark[2*105], faceLandMark[2*105+1])).normalize();
    FVec2 horizontal_dir_right = -horizontal_dir_left;
    FVec2 t_pt_43(faceLandMark[2*43], faceLandMark[2*43+1]);
    FVec2 t_pt_49(faceLandMark[2*49], faceLandMark[2*49+1]);
    FVec2 t_pt_0(faceLandMark[0], faceLandMark[1]);
    FVec2 t_pt_32(faceLandMark[2*32], faceLandMark[2*32+1]);
    f32 t_faceLen = (t_pt_32 - t_pt_0).length();
    FVec2 t_pt_n_0 = t_pt_0 + vertical_dir_up*t_faceLen*0.8;
    for (s32 i = 0; i<10; i++) {
        f32 t_delta_len = i*t_faceLen*0.1;
        FVec2 t_n_pt = (t_pt_n_0 + horizontal_dir_right*t_delta_len);
        facePts[2*t_facePtsCount] = t_n_pt.x;
        facePts[2*t_facePtsCount+1] = t_n_pt.y;
        t_facePtsCount++;
    }
    facePtsCount = t_facePtsCount;
}

void IMIKeyPointExt::faceDataForTune(f32 *faceLandMarkTune, f32 *faceLandMark, f32 *facePts, s32 &facePtsCount){
    if (faceLandMarkTune == nullptr || faceLandMark == nullptr || facePts == nullptr) {
        return;
    }
    s32 t_ptIndex = 0;
    FVec2 vertical_dir_up = (FVec2(faceLandMark[2*43], faceLandMark[2*43+1]) - FVec2(faceLandMark[2*45], faceLandMark[2*45+1])).normalize();
    FVec2 vertical_dir_down = -vertical_dir_up;
    FVec2 horizontal_dir_left = (FVec2(faceLandMark[2*104], faceLandMark[2*104+1]) - FVec2(faceLandMark[2*105], faceLandMark[2*105+1])).normalize();
    FVec2 horizontal_dir_right = -horizontal_dir_left;
    FVec2 t_pt_104(faceLandMark[2*104], faceLandMark[2*104+1]);
    FVec2 t_pt_105(faceLandMark[2*105], faceLandMark[2*105+1]);
    f32 t_eyeDis = (t_pt_104 - t_pt_105).length();
    //左眼
    s32 t_lefteye_ptsIndex[8] = {52, 53, 72, 54, 55, 56, 73, 57};
    V2 t_lefteye_pts[8];
    V2 t_lefteye_tune_pts[8];
    for (s32 i = 0; i<8; i++) {
        s32 t_index = t_lefteye_ptsIndex[i];
        t_lefteye_pts[i].x = faceLandMark[2*t_index];
        t_lefteye_pts[i].y = faceLandMark[2*t_index+1];
        t_lefteye_tune_pts[i].x = faceLandMarkTune[2*t_index];
        t_lefteye_tune_pts[i].y = faceLandMarkTune[2*t_index+1];
    }
    
    V2 t_lefteye_tune_curvePoint[30];
    s32 t_lefteye_curvePointNum = 0;
    IMIMathHelper::createCurve(t_lefteye_tune_pts, 8, 1,t_lefteye_tune_curvePoint, t_lefteye_curvePointNum, true);
    for (s32 i = 0; i<t_lefteye_curvePointNum; i++) {
        facePts[2*t_ptIndex] = t_lefteye_tune_curvePoint[i].x;
        facePts[2*t_ptIndex+1] = t_lefteye_tune_curvePoint[i].y;
        t_ptIndex++;
    }
    
    V2 t_lefteye_curvePoint[30];
    IMIMathHelper::createCurve(t_lefteye_pts, 8, 1,t_lefteye_curvePoint, t_lefteye_curvePointNum, true);
    
    f32 t_lefteye_curve_pts[60];
    for (s32 i = 0; i<t_lefteye_curvePointNum; i++) {
        t_lefteye_curve_pts[2*i] = t_lefteye_curvePoint[i].x;
        t_lefteye_curve_pts[2*i+1] = t_lefteye_curvePoint[i].y;
    }
    f32 t_lefteye_curve_expand_pts[60];
    s32 t_lefteye_curve_expand_count = 0;
    _expandPts(t_lefteye_curve_pts, t_lefteye_curvePointNum, t_lefteye_curve_expand_pts, t_lefteye_curve_expand_count, vertical_dir_up, horizontal_dir_left, t_eyeDis*0.216);
    for (s32 i = 0; i<t_lefteye_curve_expand_count; i++) {
        facePts[2*t_ptIndex] = t_lefteye_curve_expand_pts[2*i];
        facePts[2*t_ptIndex+1] = t_lefteye_curve_expand_pts[2*i+1];
        t_ptIndex++;
    }
    //右眼
    s32 t_righteye_ptsIndex[8] = {58, 59, 75, 60, 61, 62, 76, 63};
    V2 t_righteye_pts[8];
    V2 t_righteye_tune_pts[8];
    for (s32 i = 0; i<8; i++) {
        s32 t_index = t_righteye_ptsIndex[i];
        t_righteye_pts[i].x = faceLandMark[2*t_index];
        t_righteye_pts[i].y = faceLandMark[2*t_index+1];
        t_righteye_tune_pts[i].x = faceLandMarkTune[2*t_index];
        t_righteye_tune_pts[i].y = faceLandMarkTune[2*t_index+1];
    }
    V2 t_righteye_tune_curvePoint[30];
    s32 t_righteye_curvePointNum = 0   ;
    IMIMathHelper::createCurve(t_righteye_tune_pts, 8, 1,t_righteye_tune_curvePoint, t_righteye_curvePointNum, true);
    for (s32 i = 0; i<t_righteye_curvePointNum; i++) {
        facePts[2*t_ptIndex] = t_righteye_tune_curvePoint[i].x;
        facePts[2*t_ptIndex+1] = t_righteye_tune_curvePoint[i].y;
        t_ptIndex++;
    }
    
    V2 t_righteye_curvePoint[30];
    IMIMathHelper::createCurve(t_righteye_pts, 8, 1,t_righteye_curvePoint, t_righteye_curvePointNum, true);
    f32 t_righteye_curve_pts[60];
    for (s32 i = 0; i<t_righteye_curvePointNum; i++) {
        t_righteye_curve_pts[2*i] = t_righteye_curvePoint[i].x;
        t_righteye_curve_pts[2*i+1] = t_righteye_curvePoint[i].y;
    }
    f32 t_righteye_curve_expand_pts[60];
    s32 t_righteye_curve_expand_count = 0;
    _expandPts(t_righteye_curve_pts, t_righteye_curvePointNum, t_righteye_curve_expand_pts, t_righteye_curve_expand_count, vertical_dir_up, horizontal_dir_left, t_eyeDis*0.216);
    for (s32 i = 0; i<t_righteye_curve_expand_count; i++) {
        facePts[2*t_ptIndex] = t_righteye_curve_expand_pts[2*i];
        facePts[2*t_ptIndex+1] = t_righteye_curve_expand_pts[2*i+1];
        t_ptIndex++;
    }
    FVec2 t_pt_43(faceLandMark[2*43], faceLandMark[2*43+1]);
    facePts[2*t_ptIndex] = t_pt_43.x;
    facePts[2*t_ptIndex+1] = t_pt_43.y;
    t_ptIndex++;
    //嘴
    //
    s32 t_toptip_ptsIndex[20] = {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103};
    for (s32 i = 0; i<20; i++) {
        s32 t_index = t_toptip_ptsIndex[i];
        facePts[2*t_ptIndex] = faceLandMarkTune[2*t_index];
        facePts[2*t_ptIndex+1] =
        faceLandMarkTune[2*t_index+1];
        t_ptIndex++;
    }
    //
    f32 t_bottomtip_pts[24];
    f32 t_bottomtip_expand_pts[40];
    s32 t_bottomtip_expand_count = 0;
    s32 t_bottomtip_ptsIndex[12] = {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95};
    for (s32 i = 0; i<12; i++) {
        s32 t_index = t_bottomtip_ptsIndex[i];
        t_bottomtip_pts[2*i] = faceLandMark[2*t_index];
        t_bottomtip_pts[2*i+1] = faceLandMark[2*t_index+1];
    }
    //
    _expandPts(t_bottomtip_pts, 12, t_bottomtip_expand_pts, t_bottomtip_expand_count, vertical_dir_up, horizontal_dir_left, t_eyeDis*0.36);
    for (s32 i = 0; i<t_bottomtip_expand_count; i++) {
        facePts[2*t_ptIndex] = t_bottomtip_expand_pts[2*i];
        facePts[2*t_ptIndex+1] = t_bottomtip_expand_pts[2*i+1];
        t_ptIndex++;
    }
    //四周的点
    FVec2 t_pt_0(faceLandMark[0], faceLandMark[1]);
    FVec2 t_pt_32(faceLandMark[2*32], faceLandMark[2*32+1]);
    f32 t_faceWidth = (t_pt_0 - t_pt_32).length();
    FVec2 t_pt_46(faceLandMark[2*46], faceLandMark[2*46+1]);
    V2 pt;
    pt.x = t_pt_46.x;
    pt.y = t_pt_46.y;
    V2 t_tarpt_0;
    _generateDirPt(pt, horizontal_dir_left, t_tarpt_0, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_0.x;
    facePts[2*t_ptIndex+1] = t_tarpt_0.y;
    t_ptIndex++;
    //
    V2 t_tarpt_1;
    _generateDirPt(t_tarpt_0, vertical_dir_up, t_tarpt_1, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_1.x;
    facePts[2*t_ptIndex+1] = t_tarpt_1.y;
    t_ptIndex++;
    //
    V2 t_tarpt_2;
    _generateDirPt(t_tarpt_0, vertical_dir_down, t_tarpt_2, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_2.x;
    facePts[2*t_ptIndex+1] = t_tarpt_2.y;
    t_ptIndex++;
    //
    V2 t_tarpt_3;
    _generateDirPt(pt, vertical_dir_up, t_tarpt_3, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_3.x;
    facePts[2*t_ptIndex+1] = t_tarpt_3.y;
    t_ptIndex++;
    //
    V2 t_tarpt_4;
    _generateDirPt(pt, vertical_dir_down, t_tarpt_4, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_4.x;
    facePts[2*t_ptIndex+1] = t_tarpt_4.y;
    t_ptIndex++;
    //
    V2 t_tarpt_5;
    _generateDirPt(pt, horizontal_dir_right, t_tarpt_5, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_5.x;
    facePts[2*t_ptIndex+1] = t_tarpt_5.y;
    t_ptIndex++;
    //
    V2 t_tarpt_6;
    _generateDirPt(t_tarpt_5, vertical_dir_up, t_tarpt_6, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_6.x;
    facePts[2*t_ptIndex+1] = t_tarpt_6.y;
    t_ptIndex++;
    //
    V2 t_tarpt_7;
    _generateDirPt(t_tarpt_5, vertical_dir_down, t_tarpt_7, t_faceWidth*0.8);
    facePts[2*t_ptIndex] = t_tarpt_7.x;
    facePts[2*t_ptIndex+1] = t_tarpt_7.y;
    t_ptIndex++;
    
    
    facePtsCount = t_ptIndex;
}

void IMIKeyPointExt::_generateDirPt(V2 &_ptO, V2 &_ptT, V2 &_tar, f32 _len){
    FVec2 t_vec1(_ptO.x, _ptO.y);
    FVec2 t_vec2(_ptT.x, _ptT.y);
    f32 t_len = _len;
    FVec2 t_dir = (t_vec2 - t_vec1).normalize();
    FVec2 t_tar_vec = t_vec2 + t_dir*t_len;
    _tar.x = t_tar_vec.x;
    _tar.y = t_tar_vec.y;
}

void IMIKeyPointExt::faceDataForFaceTune(IMI_S_FACETUNE_RATIO &_attribute, f32 *faceLandMark, s32 keyPtNum, f32 *faceTunePts, s32 &facePtsCount){
    facePtsCount = keyPtNum;
    memcpy(faceTunePts, faceLandMark, keyPtNum*2*sizeof(f32));
    FVec2 vertical_dir_up = (FVec2(faceTunePts[2*43], faceTunePts[2*43+1]) - FVec2(faceTunePts[2*45], faceTunePts[2*45+1])).normalize();
    FVec2 vertical_dir_down = -vertical_dir_up;
    FVec2 horizontal_dir_left = (FVec2(faceTunePts[2*104], faceTunePts[2*104+1]) - FVec2(faceTunePts[2*105], faceTunePts[2*105+1])).normalize();
    FVec2 horizontal_dir_right = -horizontal_dir_left;
    FVec2 t_pt_43(faceTunePts[2*43], faceTunePts[2*43+1]);
    FVec2 t_pt_46(faceTunePts[2*46], faceTunePts[2*46+1]);
    f32 t_noiseLen = (t_pt_43 - t_pt_46).length();
    if (_attribute.mouth_noise_ratio != 0) {
        //移动嘴巴
        s32 t_mouth_ptsIndex[7] = {84, 85, 86, 87, 88, 89, 90};
        for (s32 i = 0; i<7; i++) {
            s32 t_index = t_mouth_ptsIndex[i];
            FVec2 t_pt(faceTunePts[2*t_index], faceTunePts[2*t_index+1]);
            f32 t_ratio = 1.0;
            if (t_index == 84 || t_index == 90) {
                t_ratio = t_noiseLen*_attribute.mouth_noise_ratio*0.03;
            }else if (t_index == 85 || t_index == 89){
                t_ratio = t_noiseLen*_attribute.mouth_noise_ratio*0.04;
            }else{
                t_ratio = t_noiseLen*_attribute.mouth_noise_ratio*0.09;
            }
            FVec2 t_n_pt = t_pt + vertical_dir_up*t_ratio;
            faceTunePts[2*t_index] = t_n_pt.x;
            faceTunePts[2*t_index+1] = t_n_pt.y;
        }
    }
    if (_attribute.tip_thickness_ratio != 0) {
        //嘴唇厚度
        s32 t_toptip1_ptsIndex[5] = {85, 86, 87, 88, 89};
        for (s32 i = 0; i<5; i++) {
            s32 t_index = t_toptip1_ptsIndex[i];
            FVec2 t_pt(faceTunePts[2*t_index], faceTunePts[2*t_index+1]);
            FVec2 t_n_pt = t_pt + vertical_dir_down*t_noiseLen*_attribute.tip_thickness_ratio*0.15;
            faceTunePts[2*t_index] = t_n_pt.x;
            faceTunePts[2*t_index+1] = t_n_pt.y;
        }
        //
        s32 t_toptip2_ptsIndex[5] = {91, 92, 93, 94, 95};
        for (s32 i = 0; i<5; i++) {
            s32 t_index = t_toptip2_ptsIndex[i];
            FVec2 t_pt(faceTunePts[2*t_index], faceTunePts[2*t_index+1]);
            FVec2 t_n_pt = t_pt + vertical_dir_up*t_noiseLen*_attribute.tip_thickness_ratio*0.15;
            faceTunePts[2*t_index] = t_n_pt.x;
            faceTunePts[2*t_index+1] = t_n_pt.y;
        }
    }
    if (_attribute.eyes_down_ratio != 0) {
        //眼睑下至
        FVec2 t_pt_104(faceTunePts[2*104], faceTunePts[2*104+1]);
        FVec2 t_pt_57(faceTunePts[2*57], faceTunePts[2*57+1]);
        FVec2 t_vec_left_dir = (t_pt_57 - t_pt_104).normalize();
        FVec2 t_n_pt = t_pt_57 + t_vec_left_dir*t_noiseLen*_attribute.eyes_down_ratio*0.06;
        faceTunePts[2*57] = t_n_pt.x;
        faceTunePts[2*57+1] = t_n_pt.y;
        FVec2 t_pt_73(faceTunePts[2*73], faceTunePts[2*73+1]);
        FVec2 t_vec_left_dir1 = (t_pt_73 - t_pt_104).normalize();
        t_n_pt = t_pt_73 + t_vec_left_dir1*t_noiseLen*_attribute.eyes_down_ratio*0.03;
        faceTunePts[2*73] = t_n_pt.x;
        faceTunePts[2*73+1] = t_n_pt.y;
        //
        FVec2 t_pt_105(faceTunePts[2*105], faceTunePts[2*105+1]);
        FVec2 t_pt_62(faceTunePts[2*62], faceTunePts[2*62+1]);
        FVec2 t_vec_right_dir = (t_pt_62 - t_pt_105).normalize();
        t_n_pt = t_pt_62 + t_vec_right_dir*t_noiseLen*_attribute.eyes_down_ratio*0.06;
        faceTunePts[2*62] = t_n_pt.x;
        faceTunePts[2*62+1] = t_n_pt.y;
        FVec2 t_pt_76(faceTunePts[2*76], faceTunePts[2*76+1]);
        FVec2 t_vec_right_dir1 = (t_pt_76 - t_pt_105).normalize();
        t_n_pt = t_pt_76 + t_vec_right_dir1*t_noiseLen*_attribute.eyes_down_ratio*0.03;
        faceTunePts[2*76] = t_n_pt.x;
        faceTunePts[2*76+1] = t_n_pt.y;
    }
    if (_attribute.eyes_in_corner_ratio != 0) {
        FVec2 t_pt_55(faceTunePts[2*55], faceTunePts[2*55+1]);
        FVec2 t_n_pt = t_pt_55 + horizontal_dir_right*t_noiseLen*_attribute.eyes_in_corner_ratio*0.08;
        faceTunePts[2*55] = t_n_pt.x;
        faceTunePts[2*55+1] = t_n_pt.y;
        //
        FVec2 t_pt_58(faceTunePts[2*58], faceTunePts[2*58+1]);
        t_n_pt = t_pt_58 + horizontal_dir_left*t_noiseLen*_attribute.eyes_in_corner_ratio*0.08;
        faceTunePts[2*58] = t_n_pt.x;
        faceTunePts[2*58+1] = t_n_pt.y;
    }
    if (_attribute.eyes_out_corner_ratio != 0) {
        FVec2 t_pt_52(faceTunePts[2*52], faceTunePts[2*52+1]);
        FVec2 t_n_pt = t_pt_52 + horizontal_dir_left*t_noiseLen*_attribute.eyes_out_corner_ratio*0.08;
        faceTunePts[2*52] = t_n_pt.x;
        faceTunePts[2*52+1] = t_n_pt.y;
        //
        FVec2 t_pt_61(faceTunePts[2*61], faceTunePts[2*61+1]);
        t_n_pt = t_pt_61 + horizontal_dir_right*t_noiseLen*_attribute.eyes_out_corner_ratio*0.08;
        faceTunePts[2*61] = t_n_pt.x;
        faceTunePts[2*61+1] = t_n_pt.y;
    }
}

void IMIKeyPointExt::_generateDirPt(V2 &_pt, FVec2 &_dir, V2 &_tar, f32 _len){
    f32 t_len = _len;
    FVec2 t_vec1(_pt.x, _pt.y);
    FVec2 t_tar_vec = t_vec1 + _dir*t_len;
    _tar.x = t_tar_vec.x;
    _tar.y = t_tar_vec.y;
}

void IMIKeyPointExt::_expandPts(f32 *_keyPts, s32 _keyPtsCount, f32 *_expandPts, s32 &_expandPtsCount, FVec2 &_vertical_dir_up, FVec2 &_horizontal_dir_left, f32 _offLen){
    if (_keyPts == nullptr || _expandPts == nullptr) {
        return;
    }
    FVec2 vertical_dir_up = _vertical_dir_up;
    FVec2 vertical_dir_down = -vertical_dir_up;
    FVec2 horizontal_dir_left = _horizontal_dir_left;
    FVec2 horizontal_dir_right = -horizontal_dir_left;
    s32 t_ptIndex = 0;
    s32 t_half_count = floor(_keyPtsCount*0.5);
    for (s32 i = 0; i<_keyPtsCount; i++) {
        V2 keyPt;
        keyPt.x = _keyPts[2*i];
        keyPt.y = _keyPts[2*i+1];
        //
        V2 t_tar;
        if (i == 0) {
            _generateDirPt(keyPt, horizontal_dir_left, t_tar, _offLen);
            _expandPts[2*t_ptIndex] = t_tar.x;
            _expandPts[2*t_ptIndex+1] = t_tar.y;
            t_ptIndex++;
            //
            _generateDirPt(keyPt, vertical_dir_up, t_tar, _offLen);
            _expandPts[2*t_ptIndex] = t_tar.x;
            _expandPts[2*t_ptIndex+1] = t_tar.y;
            t_ptIndex++;
            //
            _generateDirPt(keyPt, vertical_dir_down, t_tar, _offLen);
            _expandPts[2*t_ptIndex] = t_tar.x;
            _expandPts[2*t_ptIndex+1] = t_tar.y;
            t_ptIndex++;
        }else if (i == t_half_count){
            _generateDirPt(keyPt, horizontal_dir_right, t_tar, _offLen);
            _expandPts[2*t_ptIndex] = t_tar.x;
            _expandPts[2*t_ptIndex+1] = t_tar.y;
            t_ptIndex++;
            //
            _generateDirPt(keyPt, vertical_dir_up, t_tar, _offLen);
            _expandPts[2*t_ptIndex] = t_tar.x;
            _expandPts[2*t_ptIndex+1] = t_tar.y;
            t_ptIndex++;
            //
            _generateDirPt(keyPt, vertical_dir_down, t_tar, _offLen);
            _expandPts[2*t_ptIndex] = t_tar.x;
            _expandPts[2*t_ptIndex+1] = t_tar.y;
            t_ptIndex++;
        }else{
            FVec2 t_vertical_dir = vertical_dir_up;
            if (i>t_half_count) {
                t_vertical_dir = vertical_dir_down;
            }
            _generateDirPt(keyPt, t_vertical_dir, t_tar,  _offLen);
            _expandPts[2*t_ptIndex] = t_tar.x;
            _expandPts[2*t_ptIndex+1] = t_tar.y;
            t_ptIndex++;
        }
    }
    _expandPtsCount = t_ptIndex;
}
