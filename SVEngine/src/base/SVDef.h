//
// SVDef.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_BASEDEF_H
#define SV_BASEDEF_H

#include "SVTypes.h"
#include "svstr.h"
#include "SVArray.h"

#define SV_DEBUG_RENDERTIME 1
#define SV_SUPPORT_MAX_PERSON_NUM 4
#define SV_SUPPORT_MAX_TAREGT 4
#define SV_PI       3.14159265359f
#define SV_HALF_PI  SV_PI/2.0f

//默认一个小单位格子是64 ，64*64为一个tile 一个单一世界由
#define SV_WORLD_SIZE 64.0*64.0*8
#define SV_WORLD_DEPTH 3

namespace sv {

    enum {
        SV_INT = 0,
        SV_FLOAT,
        SV_FVEC2,
        SV_FVEC3,
        SV_FVEC4,
        SV_FMAT2,
        SV_FMAT3,
        SV_FMAT4,
        SV_BLOCK
    };

    enum SV_STATE{
        SV_ST_NULL = 0,
        SV_ST_WAIT,         //等待
        SV_ST_RUN,          //运行
        SV_ST_SUSPEND       //挂起
    };

    //引擎内核
    enum SV_ENGCORE {
        SV_E_CORE_GL = 0,
        SV_E_CORE_METAL,
        SV_E_CORE_VULKAN
    };

    //引擎状态
    enum SV_ENG_TIMESTATE {
        ENG_TS_NOR = 0,
        ENG_TS_FIX,
        ENG_TS_STOP
    };

    //sv线程阶段 回调
    enum SV_THREAD_STAGE {
        THREAD_STAGE_BEGIN = 0,
        THREAD_STAGE_END,
        THREAD_STAGE_SIGN_SUSPEND,
        THREAD_STAGE_UPDATE_BEGIN,
        THREAD_STAGE_UPDATE_END
    };

    //sv线程只有两个状态
    //work和free
    enum SV_THREAD_STATE {
        TS_INIT,
        TS_DESTROY,
        TS_WORK,
        TS_FREE
    };

    //sv渲染器类型 renderer
    enum SV_R_ENV {
        E_R_GLES_ANDORID,
        E_R_VULKAN_ANDORID,
        E_R_METAL_OSX,
        E_R_GL_OSX,
        E_R_METAL_IOS,
        E_R_GLES_IOS
    };

    //sv渲染流类型
    enum SV_RSTREAM {
        E_RSM_NOR = 0,          //普通流
        E_RSM_SKY,              //天空-背景
        E_RSM_FACEMORPH,          //面部微整
        E_RSM_SOLID,
        E_RSM_TRANSLATE,
        E_RSM_PRE,              //前向流
        E_RSM_AFTER,            //后处理流
        E_RSM_DEBUG,            //调试流
        E_RSM_CREATE_SHADOW,    //产生阴影流
        E_RSM_RECEIVE_SHADOW,   //接收阴影流
        E_RSM_PARTICLE,         //粒子流
        E_RSM_MAX
    };

//设计适配模式
    enum SV_DESIGN_ADAPT_MODE {
        E_APT_M_BODER = 1,   //留空白模式
        E_APT_M_FULL         //全屏铺满模式
    };

    //shader类型
    enum SV_SHADER_TYPE {
        SV_E_TECH_VS = 0x00000001,
        SV_E_TECH_FS = 0x00000010,
        SV_E_TECH_GS = 0x00000100,
        SV_E_TECH_TSE = 0x00001000,
        SV_E_TECH_TSD = 0x00010000,
        SV_E_TECH_CS = 0x00100000,
    };

    #define SV_STAGE_VS     0
    #define SV_STAGE_FS     1
    #define SV_STAGE_GS     2
    #define SV_STAGE_TSC    3
    #define SV_STAGE_TSE    4
    #define SV_STAGE_CS     5

    enum SV_SHADER_DEF {
        E_HAS_NORMALS = 0x0000001,
        E_HAS_TANGENTS = 0x0000002,
        E_HAS_UV = 0x0000004,
        E_USE_IBL = 0x0000008,
        E_HAS_BASECOLORMAP = 0x0000010,
        E_HAS_NORMALMAP = 0x0000020,
        E_HAS_EMISSIVEMAP = 0x0000040,
        E_HAS_METALROUGHNESSMAP = 0x0000080,
        E_HAS_OCCLUSIONMAP = 0x0000100
    };

    //相机图片格式
    enum SV_PIC_FORMATE {
        SV_PF_GRAY8 = 0,
        SV_PF_YV12,
        SV_PF_I420,
        SV_PF_NV12,
        SV_PF_NV21,
        SV_PF_BGRA,
        SV_PF_RGBA,
        SV_PF_RGB,
        SV_PF_NULL
    };

    //输出纹理格式
    enum SV_OUTSTEAMFORMATE {
        SV_OUT_STEAM_RGB2YUVNV12 = 0,
        SV_OUT_STEAM_RGBA,
        SV_OUT_STEAM_RGB2YUVNV21,
        SV_OUT_STEAM_RGB2YUVYV12,
        SV_OUT_STEAM_RGB2YUVI420,
        SV_OUT_STEAM_BGRA,
        SV_OUT_STEAM_NULL,
    };

    //bitfont 绑定枚举
    enum BITFONT_ATCH_PT {
        ATCH_LB,
        ATCH_LC,
        ATCH_LT,
        ATCH_MB,
        ATCH_MC,
        ATCH_MT,
        ATCH_RB,
        ATCH_RC,
        ATCH_RT
    };

    //纹理环绕方式
    enum SV_TEXWRAP {
        E_TEX_CLAMP,
        E_TEX_MIRROR,
        E_TEX_REPEAT,
        E_TEX_BORDER
    };

    //SV 支持的内置纹理种类
    enum SV_TEXIN {
        E_TEX_BEGIN = 0,
        E_TEX_MAIN,
        E_TEX_SHADOW,
        E_TEX_DEPTH,
        E_TEX_GBUF_POS,
        E_TEX_GBUF_NOR,
        E_TEX_GBUF_COLOR,
        E_TEX_FILE,
        E_TEX_CAMERA,
        E_TEX_INSTREAM,
        E_TEX_OUTSTREAM,
        E_TEX_HELP0,
        E_TEX_HELP1,
        E_TEX_HELP2,
        E_TEX_HELP3,
        E_TEX_AR_BG0,
        E_TEX_AR_BG1,
        E_TEX_AR_BG2,
        E_TEX_AR_BG3,
        E_TEX_FLITER,
        E_TEX_FLITER_GUASS,
        E_TEX_FLITER_GUASS01,
        E_TEX_FILTER_DEFORM01,
        E_TEX_FILTER_DEFORM02,
        E_TEX_FILTER_DEFORM03,
        E_TEX_FILTER_MATTING,
        E_TEX_FILTER_LUT_OUT,
        E_TEX_FILTER_LUT,
        E_TEX_FILTER_GENLUT_OUT,
        E_TEX_FILTER_GENLUT_H1,
        E_TEX_FILTER_GENLUT_H2,
        E_TEX_FILTER_GENLUT_H3,
        E_TEX_FILTER_GENLUT_H4,
        E_TEX_FILTER_MIP_1,
        E_TEX_FILTER_MIP_2,
        E_TEX_FILTER_GOF_1,
        E_TEX_FILTER_GOF_2,
        E_TEX_FILTER_GLOW_1,
        E_TEX_FILTER_GLOW_2,
        E_TEX_FILTER_GLOW_3,
        E_TEX_FILTER_0,
        E_TEX_FILTER_1,
        E_TEX_FILTER_2,
        E_TEX_FILTER_3,
        E_TEX_FILTER_SHAKE,
        E_TEX_FILTER_FLASHWHITE,
        E_TEX_INSTREAM_BEGIN,
        E_TEX_AVATAR_0,
        E_TEX_AVATAR_1,
        E_TEX_AVATAR_2,
        E_TEX_AVATAR_3,
        E_TEX_END = 64
    };

    //纹理类型
    enum SV_TEXTYPE {
        SV_IMAGE_1D = 0,
        SV_IMAGE_2D,            // 2D image
        SV_IMAGE_3D,            // 3D image
        SV_IMAGE_CUBE,          // Cube image
        SV_IMAGE_2D_ARRAY,      // 2D array image
    };

    //纹理格式
    enum SV_TEXFORMATE{
        SV_FORMAT_R8 = 0,        // 8-bits per channel unsigned formats
        SV_FORMAT_RG8,
        SV_FORMAT_RGB8,
        SV_FORMAT_RGBA8,
        SV_FORMAT_BGRA8,
        
        SV_FORMAT_R16,            // 16-bits per channel unsigned formats
        SV_FORMAT_RG16,
        SV_FORMAT_RGB16,
        SV_FORMAT_RGBA16,
        
        SV_FORMAT_R16F,        // 16-bits per channel float formats
        SV_FORMAT_RG16F,
        SV_FORMAT_RGB16F,
        SV_FORMAT_RGBA16F,
        
        SV_FORMAT_R32F,        // 32-bits per channel float formats
        SV_FORMAT_RG32F,
        SV_FORMAT_RGB32F,
        SV_FORMAT_RGBA32F,
        
        SV_FORMAT_R5G6B5,      // combined formats
        SV_FORMAT_RGBA4,
        SV_FORMAT_RGB5A1,
        SV_FORMAT_RGB10A2,
        
        SV_FORMAT_DXT1,        // compressed formats
        SV_FORMAT_DXT3,
        SV_FORMAT_DXT5,
        SV_FORMAT_ATI1,
        SV_FORMAT_ATI2,
        SV_FORMAT_ETC1,
        SV_FORMAT_ETC2,
        SV_FORMAT_ETC5,
        SV_FORMAT_EAC1,
        SV_FORMAT_EAC2,
        SV_FORMAT_ATC1,
        SV_FORMAT_ATC3,
        SV_FORMAT_ATC5,
        SV_FORMAT_PVR4,
        SV_FORMAT_ZLC1,
        SV_FORMAT_ZLC2,
    };

    class SVInst;

    class SVThread;

    //回调函数
    typedef void (*ThreadCallback)(sv::SVInstPtr _app,sv::SVThread* _thread,sv::SV_THREAD_STAGE _stage);
    //百分比回调
    typedef void (*cb_func_percent)(f32 percent);
    //百分比回调
    typedef void (*cb_func_record)(s32 _frames);
    //操作回调
    typedef void (*cb_func_op)(cptr8 _info, void *obj);
    //游戏信息回调
    typedef void (*cb_func_game)(s32 _type,cptr8 _info);
    //输出回调
    typedef void (*cb_out_stream)(s32 _w,s32 _h,s32 _formate,void* _pdata,long _timtap);
    //输出状态
    typedef void (*cb_outstream_state)(s32 _state);
    //
    typedef void (*lua_regist)(void* _ls);
    //
}



//最大同时支持的视频解析线程数目
#define SV_MAX_VIDEOLOAD_NUM 6


#endif //SV_BASEDEF_H
