//
// IMIMtlDef.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTLDEF_H
#define IMI_MTLDEF_H

#include "../base/IMIDef.h"
#include "../rendercore/IMIRenderDef.h"
#include "IMIMtlDeclare.h"

#define IMI_MTL_CLONE(classname) \
virtual IMIMtlCorePtr clone() {\
    return MakeSharedPtr<classname>(this);\
}

namespace imi {

#define MAX_TEXUNIT 8

//暂时用这个

/* AccumOp */
#define IMI_ACCUM                          0x0100
#define IMI_LOAD                           0x0101
#define IMI_RETURN                         0x0102
#define IMI_MULT                           0x0103
#define IMI_ADD                            0x0104

/* AlphaFunction */
#define IMI_NEVER                          0x0200
#define IMI_LESS                           0x0201
#define IMI_EQUAL                          0x0202
#define IMI_LEQUAL                         0x0203
#define IMI_GREATER                        0x0204
#define IMI_NOTEQUAL                       0x0205
#define IMI_GEQUAL                         0x0206
#define IMI_ALWAYS                         0x0207

#define IMI_KEEP                           0x1E00
#define IMI_REPLACE                        0x1E01
#define IMI_INCR                           0x1E02
#define IMI_DECR                           0x1E03

#define IMI_CCW      1
#define IMI_CW       2

#define IMI_BACK     1
#define IMI_FRONT    2


struct BlendParam{
    bool enable;
    s32 srcParam;
    s32 dstParam;
};

struct CullFaceParam{
    bool enable;
    s32 frontFace;
    s32 cullFace;
};

//深度参数
struct DepthParam{
    bool clear;
    bool enable;        //开启深度测试
    s32 testMethod;     //深度测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
};

//透明测试参数
struct AlphaParam{
    bool enable;        //开启alpha测试
    s32 testMethod;    //alpha测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
};

//模板参数
struct StencilParam{
    bool clear;         //
    bool enable;        //开启模板测试
    s32 passMethod;     //通过模板测试的规则(GL_NEVER,GL_LESS < ,GL_LEQUAL <= ,GL_GREATER > ,GL_GEEQUAL >= ,GL_EQUAL == ,GL_ALWAYS)
    s32 refValue;       //通过模板测试的参考值(0-255)
    s32 maskValue;      //掩码( 模板值&掩码 * 参考值&掩码 )
    s32 sfail;          //模板测试失败     (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
    s32 zfail;          //模板通过 深度失败 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
    s32 zpass;          //模板通过 深度通过 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写≤
};

//材质标记
enum MTLFLAG0{
    MTL_F0_MAT_NULL     = 0x00000000,
    MTL_F0_MAT_M        = 0x00000001,
    MTL_F0_MAT_V        = 0x00000002,
    MTL_F0_MAT_P        = 0x00000004,
    MTL_F0_MAT_VP       = 0x00000008,
    MTL_F0_TEX0         = 0x00000010,
    MTL_F0_TEX1         = 0x00000020,
    MTL_F0_TEX2         = 0x00000040,
    MTL_F0_TEX3         = 0x00000080,
    MTL_F0_TEX4         = 0x00000100,
    MTL_F0_TEX5         = 0x00000200,
    MTL_F0_TEX6         = 0x00000400,
    MTL_F0_TEX7         = 0x00000800,
    MTL_F0_POINT_SIZE   = 0x00002000,
    MTL_F0_LINE_SIZE    = 0x00004000,
    MTL_F0_BLEND        = 0x00010000,
    MTL_F0_CULL         = 0x00020000,
    MTL_F0_STENCIL      = 0x00040000,
    MTL_F0_ALPHA        = 0x00080000,
    MTL_F0_DEPTH        = 0x00100000,
    MTL_F0_TEX_SIZE     = 0x01000000,
    MTL_F1_TEX_SIZE     = 0x02000000,
    MTL_F2_TEX_SIZE     = 0x04000000,
    MTL_F3_TEX_SIZE     = 0x08000000,
    MTL_F0_BLENDMODE    = 0x10000000,
    MTL_F0_ZOFF         = 0x20000000
};

//材质标记
enum MTLFLAG_BASEON{
    MTL_F_BASEON_NONE         = 0x00000000,
    MTL_F_BASEON_SHADOW       = 0x00000001,
    MTL_F_BASEON_HL           = 0x00000002,
    MTL_F_BASEON_CONSTRAST    = 0x00000004,
    MTL_F_BASEON_SATURATION   = 0x00000008,
    MTL_F_BASEON_ACUTANCE     = 0x00000010,
    MTL_F_BASEON_BRIGHTNESS   = 0x00000020,
    MTL_F_BASEON_WHITENING    = 0x00000040,
    MTL_F_BASEON_GAMMA        = 0x00000080,
    MTL_F_BASEON_REDSHIFT     = 0x00000100,
    MTL_F_BASEON_GREENSHIFT   = 0x00000200,
    MTL_F_BASEON_BLUESHIFT    = 0x00000400,
    MTL_F_BASEON_SDREDSHIFT   = 0x00000800,
    MTL_F_BASEON_SDGREENSHIFT = 0x00001000,
    MTL_F_BASEON_SDBLUESHIFT  = 0x00002000,
    MTL_F_BASEON_HHREDSHIFT   = 0x00004000,
    MTL_F_BASEON_HHGREENSHIFT = 0x00008000,
    MTL_F_BASEON_HHBLUESHIFT  = 0x00010000,
    MTL_F_BASEON_TEMPERATURE  = 0x00020000,
    MTL_F_BASEON_TINT         = 0x00040000,
};

/* Blending
 */
enum {
    MTL_BLEND_NONE = 0,
    MTL_BLEND_ZERO,
    MTL_BLEND_ONE,
    MTL_BLEND_SRC_COLOR,
    MTL_BLEND_ONE_MINUS_SRC_COLOR,
    MTL_BLEND_SRC_ALPHA,
    MTL_BLEND_ONE_MINUS_SRC_ALPHA,
    MTL_BLEND_DST_COLOR,
    MTL_BLEND_ONE_MINUS_DST_COLOR,
    MTL_BLEND_DST_ALPHA,
    MTL_BLEND_ONE_MINUS_DEST_ALPHA,
    MTL_NUM_BLEND_FUNC
};

//美颜滤镜(FTB filter beauty)
enum FTBTYPE{
    FTB_ORIGIN = 0,
    FTB_ORIGIN02,
    FTB_VALENCIA,
    FTB_VALENCIA01,
    FTB_NASHVILLE,
    FTB_WALDEN,
    FTB_WALDEN01,
    FTB_BRANNAN,
    FTB_INKWELL,
    FTB_INKWELL01,
    FTB_INKWELL02,
    FTB_INKWELL03,
    FTB_PINK,
    FTB_PINK01,
    FTB_GUASS,
    FTB_GUASS01,
    FTB_GRASS,
    FTB_BEACH,
    FTB_BEACH01,
    FTB_NEW3,
    FTB_SWEETY,
    FTB_SWEETY01,
    FTB_SWEETY02,
    FTB_NATURE,
    FTB_NATURE01,
    FTB_NATURE02,
    FTB_CLEAN,
    FTB_CLEAN01,
    FTB_CLEAN02,
    FTB_FRESH,
    FTB_FRESH01,
    FTB_CORAL,
    FTB_CORAL01,
    FTB_SUNSET,
    FTB_VIVID,
    FTB_LOLITA,
    FTB_ROSY,
    FTB_URBAN,
    FTB_VINTAGE,
    FTB_KISSKISS,
    FTB_SNOW,
    FTB_GLOSSY
};

//滤镜类型
enum FTTYPE {
    FILTER_COMMON = 0,
    FILTER_LUT,
    FILTER_HDR,
    FILTER_BLUR,
    FILTER_SHARP,
    FILTER_HUE,
    FILTER_HAZE,
    FILTER_GRAY
};



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

}//!namespace imi



#endif //IMI_MTLDEF_H
