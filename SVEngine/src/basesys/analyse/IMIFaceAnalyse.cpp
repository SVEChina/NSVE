//
// IMIFaceAnalyse.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFaceAnalyse.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../file/IMIFileMgr.h"
#include "../base/IMIDataSwap.h"
#include "../base/IMIDataChunk.h"

using namespace imi;

//分析脸型
s32 IMIFaceAnalyse::analyseFace(IMIInstPtr _inst,std::vector<FVec2>& points) {
    if(points.size()<123) {
        return 0;
    }
    //
    /*
     五眼比例
     左眼：52-55
     右眼：58-61
     内眼角间距：55-58
     外眼角颧(quan)弓留白(左)1-52
     外眼角颧(quan)弓留白(右)31-61
     中轴线：取43-44构建的直线
     */
    {
        //标准方程ax+by+c=0;
        //43-44直线(标准)方程
        FVec2 pt0 = points[42];
        FVec2 pt1 = points[43];
        f32 line_a = pt1.y - pt0.y;
        f32 line_b = pt0.x - pt1.x;
        f32 line_c = pt1.x*pt0.y - pt0.x*pt1.y;
        f32 line_k = 1.0f;
        //dis
        f32 dis_eye_l = 0.0f;
        f32 dis_eye_r = 0.0f;
        f32 dis_eye_l_hull = 0.0f;
        f32 dis_eye_r_hull = 0.0f;
        f32 dis_eye_d = 0.0f;
//        if(fix_x == 1) {
//            //直线方程
//            dis_eye_l = points[51].x - points[54].x;
//            dis_eye_r = points[57].x - points[60].x;
//            dis_eye_l_hull = points[0].x - points[51].x;
//            dis_eye_r_hull = points[30].x - points[60].x;
//            dis_eye_d = points[54].x - points[57].x;
//        } else if(fix_y == 1) {
//            //直线方程
//            dis_eye_l = points[51].y - points[54].y;
//            dis_eye_r = points[57].y - points[60].y;
//            dis_eye_l_hull = points[0].y - points[51].y;
//            dis_eye_r_hull = points[30].y - points[60].y;
//            dis_eye_d = points[54].y - points[57].x;
//        } else {
////            dis_eye_l = points[51].x - points[54].x;
////            dis_eye_r = points[57].x - points[60].x;
////            dis_eye_l_hull = points[0].x - points[51].x;
////            dis_eye_r_hull = points[30].x - points[60].x;
////            dis_eye_d = points[54].x - points[57].x;
//        }
    }
    return 0;
}

//分析眼眉
s32 IMIFaceAnalyse::analyseEyebow(IMIInstPtr _inst,std::vector<FVec2>& points) {
    return 0;
}

//分析眼睛
s32 IMIFaceAnalyse::analyseEye(IMIInstPtr _inst,std::vector<FVec2>& points) {
    return 0;
}

//分析鼻子
s32 IMIFaceAnalyse::analyseNoise(IMIInstPtr _inst,std::vector<FVec2>& points) {
    return 0;
}
