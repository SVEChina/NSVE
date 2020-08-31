//
// SVFilterLib.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FILTERLIB_H
#define SV_FILTERLIB_H

#include "../base/SVGBase.h"
#include "SVMtlDef.h"

namespace sv {
    
    /*引擎提供的默认滤镜库*/

    //特定滤镜，不允许更换材质
    //公共滤镜，可以替换材质
    
    class SVFilterLib : public SVGBaseEx {
    public:
        static SVFilterBasePtr createFilter(SVInstPtr _app,FTTYPE _type);
        
    };

}//!namespace sv


#endif //SV_FILTERLIB_H
