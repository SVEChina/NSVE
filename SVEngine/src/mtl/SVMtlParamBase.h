//
// SVMtlParamBase.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MTLPARAM_H
#define SV_MTLPARAM_H

#include "../base/SVObject.h"
#include "../base/SVPreDeclare.h"
#include "SVMtlDef.h"
#include <string>

#define MAX_TEXUNIT 8

namespace sv {
        
    //
    struct SVMatrixParam  {
        SVMatrixParam();
        
        ~SVMatrixParam();
        
        void reset();
        
        void copy(SVMatrixParam& _param);
        
        s8 m_self_view;
        s8 m_self_proj;
        s8 m_self_vp;
        s8 m_self_null;
        f32 m_mat_model[16];
        f32 m_mat_view[16];
        f32 m_mat_project[16];
        f32 m_mat_vp[16];
    };

    //材质参数描述
    struct MtlParamDsp {
        std::string m_name; //参数名称
        std::string m_type; //参数类型
        s32 m_size;         //参数数据大小
        u64 m_off;          //参数数据偏移
    };

    //材质纹理描述
    struct MtlTextureDsp {
        std::string m_name; //参数名称
        std::string m_type; //参数类型
        s32 m_size;         //参数数据大小
        u64 m_off;          //参数数据偏移
    };
        
    //
    struct TexUnit {
    public:
        TexUnit();
        
        ~TexUnit();
        
        void copy(TexUnit& _texunit);
        
        void reset();
        
        SVTexturePtr m_pTex;
        
        SVTEXINID m_texForm;  //纹理来源
        
        u32 m_min_filter;
        
        u32 m_mag_filter;
        
        u32 m_s_wrap;
        
        u32 m_t_wrap;
    };
    
    struct SVTextureParam {
        
        SVTextureParam();
        
        void reset();
        
        void copy(SVTextureParam& _param);
        
        void setTexture(u32 _index,SVTexturePtr _tex);
        
        void setTexture(u32 _index,sv::SVTEXINID _from);
        
        //设置纹理环绕
        void setTexWrapS(u32 _index,s32 _type);
        
        void setTexWrapT(u32 _index,s32 _type);
        
        //设置纹理过滤器
        void setTexFilterMax(u32 _index,s32 _type);
        
        void setTexFilterMin(u32 _index,s32 _type);

    public:
        TexUnit m_texUnit[MAX_TEXUNIT];
    };
        
    //
    struct SVBlendParam {
    public:
        SVBlendParam();
        
        ~SVBlendParam();
        
        void reset();
        
        void copy(SVBlendParam& _param);
        
        bool enable;
        MTLBLENDFUNC srcParam;
        MTLBLENDFUNC dstParam;
    };
    
    //
    struct SVCullFaceParam {
    public:
        SVCullFaceParam();
        
        ~SVCullFaceParam();
        
        void reset();
        
        void copy(SVCullFaceParam& _param);
        
        bool enable;
        s32 frontFace;
        s32 cullFace;
    };
    
    //
    struct SVDepthParam {
    public:
        SVDepthParam();
        
        ~SVDepthParam();
        
        void reset();
        
        void copy(SVDepthParam& _param);
        
        bool clear;
        bool enable;        //开启深度测试
        s32 testMethod;     //深度测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
    };
    
    //
    struct SVStencilParam {
    public:
        SVStencilParam();
        
        ~SVStencilParam();
        
        void copy(SVStencilParam& _param);
        
        void reset();
        
        bool clear;         //
        bool enable;        //开启模板测试
        s32 passMethod;     //通过模板测试的规则(GL_NEVER,GL_LESS < ,GL_LEQUAL <= ,GL_GREATER > ,GL_GEEQUAL >= ,GL_EQUAL == ,GL_ALWAYS)
        s32 refValue;       //通过模板测试的参考值(0-255)
        s32 maskValue;      //掩码( 模板值&掩码 * 参考值&掩码 )
        s32 sfail;          //模板测试失败     (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 zfail;          //模板通过 深度失败 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 zpass;          //模板通过 深度通过 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写≤
    };
    
    //
    struct SVAlphaParam {
    public:
        SVAlphaParam();
        
        ~SVAlphaParam();
        
        void reset();
        
        void copy(SVAlphaParam& _param);
        
        bool enable;        //开启alpha测试
        s32 testMethod;    //alpha测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
    };
    
    //z偏移参数
    struct SVZOffParam {
    public:
        SVZOffParam();
        
        ~SVZOffParam();
        
        void reset();
        
        void copy(SVZOffParam& _param);
        
        bool enable;
        f32 m_factor;
        f32 m_unit;
    };
        
    
}//!namespace sv




#endif //SV_MTLPARAM_H
