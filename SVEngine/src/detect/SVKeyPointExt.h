//
// SVKeyPointExt.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_KEYPOINTEXT_H
#define SV_KEYPOINTEXT_H
#include "../base/SVTypes.h"
#include "../core/SVVertDef.h"
#include "../base/SVVec2.h"
namespace sv {
        //sensetime
        class SVKeyPointExt {
        public:
            static void faceDataForEyes(f32 *faceLandMark, f32 *eyesPts, s32 &eyesPtsCount);
            
            static void faceDataForEyeBrow(f32 *faceLandMark, f32 *eyebrowPts, s32 &eyebrowPtsCount);
            
            static void faceDataForFaceWithHead(f32 *faceLandMark, f32 *facePts, s32 &facePtsCount);
            
            static void faceDataForWhole(f32 *faceLandMark, f32 *facePts, s32 &facePtsCount);
            
            static void faceDataForTune(f32 *faceLandMarkTune, f32 *faceLandMark, f32 *facePts, s32 &facePtsCount);
        protected:
            static void _generateDirPt(V2 &_ptO, V2 &_ptT, V2 &_tar, f32 _len);
            static void _generateDirPt(V2 &_pt, FVec2 &_dir, V2 &_tar, f32 _len);
            //顺时针外扩一圈点（如眼睛，嘴巴这些）
            static void _expandPts(f32 *_keyPts, s32 _keyPtsCount, f32 *_expandPts, s32 &_expandPtsCount, FVec2 &_vertical_dir_up, FVec2 &_horizontal_dir_left, f32 _offLen);
        };
        
}//!namespace sv



//
#endif //SV_KEYPOINTEXT_H
