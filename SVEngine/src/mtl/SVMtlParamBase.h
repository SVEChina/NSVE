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
        
    
}//!namespace sv




#endif //SV_MTLPARAM_H
