//
// SVFilterLib.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFilterLib.h"
#include "../app/SVInst.h"
#include "../file/SVFileMgr.h"
#include "SVFilterBase.h"
#include "SVFilterCommon.h"

using namespace sv;

////滤镜类型
//enum FTTYPE {
//    FILTER_COMMON = 0,
//    FILTER_LUT,
//    FILTER_BLUR,
//    FILTER_SHARP,
//    FILTER_HUE
//};


SVFilterBasePtr SVFilterLib::createFilter(SVInstPtr _app,FTTYPE _type) {
    if(_type == FILTER_COMMON) {
        return MakeSharedPtr<SVFilterCommon>(_app);
    }else if(_type == FILTER_LUT) {
        
    }else if(_type == FILTER_BLUR) {
        
    }else if(_type == FILTER_SHARP) {
        
    }else if(_type == FILTER_HUE) {
        
    }
    return nullptr;
}
