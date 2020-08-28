//
// SVRGBToneCurveCore.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RGBTONECURVECORE_H
#define SV_RGBTONECURVECORE_H

#include "../../base/SVGBase.h"
#include "../../mtl/SVMtlDeclare.h"
#include "../../node/SVNodeDeclare.h"
#include "../../core/SVVertDef.h"

namespace sv {

void createSplineCurve(sv::SVArray<V2> points,
                       sv::SVArray<f32> *preparedSplinePoints);

void getPreparedSplineCurve(sv::SVArray<V2>  mRgbCompositeControlPoints,
                            sv::SVArray<V2>  mRedControlPoints,
                            sv::SVArray<V2>  mGreenControlPoints,
                            sv::SVArray<V2>  mBlueControlPoints,
                            u8* outRgba);
}


#endif /* SV_RGBTONECURVECORE_H */
