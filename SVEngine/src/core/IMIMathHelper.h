//
// IMIMathHelper.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MATHHELPER_H
#define IMI_MATHHELPER_H

#include "IMIVertDef.h"
#include "../base/IMIArray.h"
#define EPS 1e-8

namespace imi {
    class IMIMathHelper{
    public:
        //covered 是否覆盖原来的点
        static void createCurve(V2 *originpoint, s32 origincount, s32 step, V2 *outcurve, s32 &outptcount, bool covered = false);
    
        static f32 getEllipseY(f32 ellipse_a, f32 ellipse_b, f32 ellipse_x);
    
        static f32 fit_size(f32 srcw, f32 srch, f32 dstw, f32 dsth, s32 type);
    
        static f32 getDistanceFromPointToLine();
        //龙贝格积分
        static f64 rombergIntegration(f64 _low, f64 _high, f64 _e = EPS);
    };
}//!namespace imi

#endif //IMI_MATHHELPER_H
