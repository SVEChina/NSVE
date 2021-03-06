//
// SVMtlDeclare.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MTLDECLARE_H
#define SV_MTLDECLARE_H

#include "../base/SVPreDeclare.h"

namespace sv {

    DECLARE_SHAREPTR(SVMtlCore);
    DECLARE_SHAREPTR(SVSurface);
    DECLARE_SHAREPTR(SVMtlPack);
    DECLARE_SHAREPTR(SVMtlLib);

    //
    DECLARE_SHAREPTR(SVMtlGLTF);
    DECLARE_SHAREPTR(SVMtlGLTFSkin);
    DECLARE_SHAREPTR(SVMtlBrightnessContrast);
    DECLARE_SHAREPTR(SVMtlSaturation);
    DECLARE_SHAREPTR(SVMtlVibrance);
    DECLARE_SHAREPTR(SVMtlWhiteBalance);
    DECLARE_SHAREPTR(SVMtlExposure);
    DECLARE_SHAREPTR(SVMtlGamma);
    DECLARE_SHAREPTR(SVMtlShadowHighlight);
    DECLARE_SHAREPTR(SVMtlWhiteBlackLevel);
    DECLARE_SHAREPTR(SVMtlColorBalance);
    DECLARE_SHAREPTR(SVMtlSmooth);
    DECLARE_SHAREPTR(SVMtlHSL);
    DECLARE_SHAREPTR(SVMtlGeo3d);
    DECLARE_SHAREPTR(SVMtlCoord);
    DECLARE_SHAREPTR(SVMtlNetGrid);
    DECLARE_SHAREPTR(SVMtlBeauty);
    DECLARE_SHAREPTR(SVMtlGradientMap);
    DECLARE_SHAREPTR(SVMtlMask);
    DECLARE_SHAREPTR(SVMtlRGB2YUV);
    DECLARE_SHAREPTR(SVMtl3D);
    DECLARE_SHAREPTR(SVMtlBillboard);
    DECLARE_SHAREPTR(SVMtlShadowMapping);

    //美颜
    DECLARE_SHAREPTR(SVMtlFilterBrilaterl);
    DECLARE_SHAREPTR(SVMtlFilterBrilaterl2);
    DECLARE_SHAREPTR(SVMtlGaussian);
    DECLARE_SHAREPTR(SVMtlBlurFair);
    DECLARE_SHAREPTR(SVMtlFairLtraLow);
    DECLARE_SHAREPTR(SVMtlFaceShape);
    DECLARE_SHAREPTR(SVMtlFaceShapeVaried);
    DECLARE_SHAREPTR(SVMtlBlur);
    DECLARE_SHAREPTR(SVMtlParticleAni);

    //滤镜
    DECLARE_SHAREPTR(SVMtlBasedOn);
    DECLARE_SHAREPTR(SVMtlAcutance);
    //texture
    DECLARE_SHAREPTR(SVTexture);
    DECLARE_SHAREPTR(SVTexturePList);
    DECLARE_SHAREPTR(SVTextureIOS);

}//!namespace sv


#endif //SV_MTLDECLARE_H
