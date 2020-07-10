//
// SVShader.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SHADER_H
#define SV_SHADER_H

#include "../base/SVGBase.h"
#include "../rendercore/SVRenderDeclare.h"

namespace sv {

    /*
    逻辑概念的shader
    */

    struct ShaderParam {
        s32 m_dsp;
        SVString m_programme_fname;
        SVString m_vs_fname;
        SVString m_fs_fname;
        SVString m_gs_fname;
        SVString m_cs_fname;
        SVString m_tsc_fname;
        SVString m_tse_fname;
        SVString m_attri_formate;
    };

    class SVShader : public SVGBaseEx {
    public:
        SVShader(SVInstPtr _app);
        
        ~SVShader();
        
        //渲染内核
        void bindRes(SVRShaderPtr _res);
        
        void unbindRes();
        
        SVRShaderPtr getResShader();
        
    protected:
        SVRShaderPtr m_res_shader;
        
    public:
        ShaderParam m_param;
    };
        
}//!namespace sv



#endif //SV_SHADER_H
