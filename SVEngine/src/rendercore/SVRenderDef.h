//
// SVRenderDef.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERDEF_H
#define SV_RENDERDEF_H

#include "../base/SVCompileConfig.h"

#include "../base/SVDef.h"

//定义了Metal
#define SV_METAL

//一堆宏定义
#ifdef SV_METAL

#include "SVMetal/SVMetalDef.h"

#elif defined SV_VULKAN

#include "SVMetal/SVVulkanDef.h"

#elif defined SV_GLES

#include "SVMetal/SVGLDef.h"

#elif defined SV_WEBGL

#include "SVMetal/SVWebGLDef.h"

#endif

//#if defined(SV_ANDROID)
//#endif
//
////MAC平台 或 IPHONE平台
//#if defined(SV_IOS)
//#endif  //__MACOSX__ || __APPLE__

namespace sv {

enum RENDERSTREAMTYPE {
    RST_BEGIN = 0,
    RST_SCENE_BEGIN,        //场景渲染是在设计分辨率下玩的内容
    RST_SKY,                //背景
    RST_BEAUTY,             //美颜
    RST_FACEACCELENT,       //面部增强
    RST_FACEMORPH,          //面部微整
    RST_IMGFILTER,          //风格化
    RST_IMGFILTER_OUT,      //lut数据输出
    RST_SHADOW_BEGIN,       //阴影开始
    RST_SHADOW,             //阴影相关
    RST_SHADOW_END,         //阴影结束
    RST_AR_BEGIN,           //ar开始
    RST_AR,                 //ar相关
    RST_AR_END,             //ar结束
    RST_SOLID_3D,           //3d正常固体
    RST_ALPHA_3D,           //3d正常透明
    RST_MASK2D,             //2d面具+头饰
    RST_FREETYPE,           //2d字体
    RST_SOLID_2D,           //跟人2d先绘制
    RST_DEBUG_INNER,        //图像内部测试
    RST_LASTFILTER,         //图形后处理滤镜
    RST_MAGIC_OUT,          //图像输出
    RST_SCENE_END,          //场景之后是在界面尺寸(真分辨率)下玩的内容
    RST_DATATRANS,          //数据转换流
    RST_ADAPT_SCENE,        //scene单独使用，将设计分辨率的内容 适配给真是分辨率
    RST_UI_BEGIN,           //ui开始
    RST_UI,                 //ui
    RST_UI_END,             //ui结束
    RST_UI_FRONT,           //ui上层
    RST_LOGO,               //logo
    RST_DEBUG,              //测试
    RST_END
};

/* Buffer mask
 */
enum {
    BUFFER_NONE = 0,
    BUFFER_RED = 1 << 0,
    BUFFER_GREEN = 1 << 1,
    BUFFER_BLUE = 1 << 2,
    BUFFER_ALPHA = 1 << 3,
    BUFFER_DEPTH = 1 << 4,
    BUFFER_STENCIL = 1 << 5,
    BUFFER_COLOR = (BUFFER_RED | BUFFER_GREEN | BUFFER_BLUE | BUFFER_ALPHA),
    BUFFER_DEPTH_STENCIL = (BUFFER_DEPTH | BUFFER_STENCIL),
    BUFFER_ALL = (BUFFER_COLOR | BUFFER_DEPTH_STENCIL),
};

/* Depth testing
 */
enum {
    DEPTH_NONE = 0,
    DEPTH_NEVER,
    DEPTH_LESS,
    DEPTH_EQUAL,
    DEPTH_LEQUAL,
    DEPTH_GREATER,
    DEPTH_NOTEQUAL,
    DEPTH_GEQUAL,
    DEPTH_ALWAYS,
    NUM_DEPTH_FUNC,
};

/* Blending
 */
enum {
    BLEND_NONE = 0,
    BLEND_ZERO,
    BLEND_ONE,
    BLEND_SRC_COLOR,
    BLEND_ONE_MINUS_SRC_COLOR,
    BLEND_SRC_ALPHA,
    BLEND_ONE_MINUS_SRC_ALPHA,
    BLEND_DEST_COLOR,
    BLEND_ONE_MINUS_DEST_COLOR,
    BLEND_DEST_ALPHA,
    BLEND_ONE_MINUS_DEST_ALPHA,
    BLEND_SRC1_COLOR,
    BLEND_ONE_MINUS_SRC1_COLOR,
    BLEND_SRC1_ALPHA,
    BLEND_ONE_MINUS_SRC1_ALPHA,
    NUM_BLEND_FUNC,
};

/* Downsize
 */
enum {
    DOWNSIZE_NONE = 0,
    DOWNSIZE_SCALE,
    DOWNSIZE_FILTER,
    DOWNSIZE_BACKGROUND_SCALE,
    DOWNSIZE_BACKGROUND_FILTER,
    NUM_DOWNSIZE_MODES,
};

/* Alpha Func
 */
enum {
    ALPHA_NONE,
    ALPHA_COVERAGE,
    NUM_ALPHA_FUNC,
};

/* Front face
 */
enum {
    FRONT_CCW = 0,
    FRONT_CW,
    FRONT_INVERT,
    NUM_FRONT_MODES,
};

/* Face culling
 */
enum {
    CULL_NONE = 0,
    CULL_BACK,
    CULL_FRONT,
    NUM_CULL_MODES,
};

/* Polygon fill
 */
enum {
    FILL_SOLID = 0,
    FILL_WIREFRAME,
    NUM_FILL_MODES,
};



/*
 逻辑层面的纹理
 */

struct SVTextureDsp {
    
    SVTextureDsp() {
        m_image_type = SV_IMAGE_2D;
        m_data_formate = SV_FORMAT_RGBA8;    // 数据格式
        m_warp_s = E_TEX_CLAMP;             // S方向环绕
        m_warp_t = E_TEX_CLAMP;             // T方向环绕
        m_width = 1;                        // 宽
        m_height = 1;                       // 高
        m_depth = 1;                        // 深度    //3d纹理使用
        m_minmap = true;                    // 是否开启mipmap
        m_computeWrite = false;             // metal
        m_renderTarget = false;             // 是否renderTarget
        m_srgb = false;                     // metal
    };
    
    SV_TEXTYPE m_image_type;
    SV_TEXFORMATE m_data_formate;      //数据格式
    SV_TEXWRAP m_warp_s;
    SV_TEXWRAP m_warp_t;
    s32 m_width;            //宽
    s32 m_height;           //高
    s32 m_depth;            //深度    //3d纹理使用
    bool m_minmap;          //是否开启mipmap
    bool m_computeWrite;    //metal 是否可以
    bool m_renderTarget;    //metal 是否是renderTarget
    bool m_srgb;
};


}//!namespace sv


#endif //SV_RENDERDEF_H
