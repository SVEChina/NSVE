//
// SVFilterDef.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#ifndef SV_FILTERDEF_H
#define SV_FILTERDEF_H

#include "../../base/SVObject.h"

struct FtParamPic {
    FtParamPic() {
        //memset(this,0,sizeof(FtParam));
    };
    //阴影
    f32 m_shadows;
    //高光
    f32 m_highlights;
    //对比（颜色反差）
    f32 m_contrast;
    //包含度
    f32 m_saturation;
    //锐度
    f32 m_acutance;
    //明亮
    f32 m_brightness;
    //白平衡
    f32 m_whitening;
    //gamma
    f32 m_gamma;
    //RGB曲线
    f32 m_redShift;
    f32 m_greenShift;
    f32 m_blueShift;
    f32 m_sdredShift;
    f32 m_sdgreenShift;
    f32 m_sdblueShift;
    f32 m_hhredShift;
    f32 m_hhgreenShift;
    f32 m_hhblueShift;
    //温度
    f32 m_temperature;
    //色调
    f32 m_tint;
};




enum SVFILTERITEMTYPE {
    E_BEATY_FILTER=0,
    E_SHADOWS_FILTER,
    E_CONTRAST_FILTER,
    E_SATURATION_FILTER,
    E_ACUTANCE_FILTER,
    E_BRIGHTNESS_FILTER,
    E_WHITENING_FILTER,
    E_HIGHLIGHTS_FILTER,
    E_GAMMA_FILTER,
    E_REDSHIFT_FILTER,
    E_GREENSHIFT_FILTER,
    E_BLUESHIFT_FILTER,
    E_SDREDSHIFT_FILTER,
    E_SDGREENSHIFT_FILTER,
    E_SDBLUESHIFT_FILTER,
    E_HHREDSHIFT_FILTER,
    E_HHGREENSHIFT_FILTER,
    E_HHBLUESHIFT_FILTER,
    E_TEMPERATURE_FILTER,
    E_TINT_FILTER
};

enum SVFILTERFUNCTYPE{
    SV_FUNC_NONE=0,
    SV_FUNC_BEAUTY,
    SV_FUNC_BASEONFILTER,
    SV_FUNC_LOOKUP,
    SV_FUNC_BSPLINE,
    SV_FUNC_BRIGHTNESSCONTRAST,
    SV_FUNC_CLARITY,
    SV_FUNC_HAZE,
    SV_FUNC_GOF,
    SV_FUNC_GLOW,
    SV_FUNC_BLUR,
    SV_FUNC_SHARP,
    SV_FUNC_DARK,
    SV_FUNC_SHAKE,
    SV_FUNC_FLASHWHITE,
    SV_FUNC_ADBASE,
    SV_FUNC_FACE_MATTING
};

#endif /* SV_FILTERDEF_H */
