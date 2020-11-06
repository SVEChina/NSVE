//
// IMIRGBToneCurveCore.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RGBTONECURVECORE_H
#define IMI_RGBTONECURVECORE_H

#include "../base/IMIGBase.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../node/IMINodeDeclare.h"
#include "../core/IMIVertDef.h"

namespace imi {

void createSplineCurve(imi::IMIArray<V2> points,
                       imi::IMIArray<f32> *preparedSplinePoints);

void getPreparedSplineCurve(imi::IMIArray<V2>  mRgbCompositeControlPoints,
                            imi::IMIArray<V2>  mRedControlPoints,
                            imi::IMIArray<V2>  mGreenControlPoints,
                            imi::IMIArray<V2>  mBlueControlPoints,
                            u8* outRgba);
}


#endif /* IMI_RGBTONECURVECORE_H */
