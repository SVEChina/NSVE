//
// SVMathHelper.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MATHHELPER_H
#define SV_MATHHELPER_H

#include "SVVertDef.h"
#include "../base/SVArray.h"
#define EPS 1e-8

namespace sv {
    class SVMathHelper{
    public:
        //covered 是否覆盖原来的点
        static void createCurve(V2 *originpoint, s32 origincount, s32 step, V2 *outcurve, s32 &outptcount, bool covered = false);
    
        static f32 getEllipseY(f32 ellipse_a, f32 ellipse_b, f32 ellipse_x);
    
        static f32 fit_size(f32 srcw, f32 srch, f32 dstw, f32 dsth, s32 type);
    
        static f32 getDistanceFromPointToLine();
        //龙贝格积分
        static f64 rombergIntegration(f64 _low, f64 _high, f64 _e = EPS);
    };
}//!namespace sv

#endif //SV_MATHHELPER_H
