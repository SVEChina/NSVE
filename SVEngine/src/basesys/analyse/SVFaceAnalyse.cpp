//
// SVFaceAnalyse.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFaceAnalyse.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../file/SVFileMgr.h"
#include "../base/SVDataSwap.h"
#include "../base/SVDataChunk.h"

using namespace sv;

SVFaceAnalyse::SVFaceAnalyse()
:SVObject() {
}

SVFaceAnalyse::~SVFaceAnalyse() {
}

//分析人脸
s32 SVFaceAnalyse::analyseFace(SVInstPtr _inst,std::vector<FVec2>& points) {
    return 0;
}

//分析眼眉
s32 SVFaceAnalyse::analyseEyebow(SVInstPtr _inst,std::vector<FVec2>& points) {
    return 0;
}

//分析眼睛
s32 SVFaceAnalyse::analyseEye(SVInstPtr _inst,std::vector<FVec2>& points) {
    return 0;
}

//分析鼻子
s32 SVFaceAnalyse::analyseNoise(SVInstPtr _inst,std::vector<FVec2>& points) {
    return 0;
}
