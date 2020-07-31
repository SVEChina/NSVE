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
#include <string>
#include <vector>

namespace sv {

    /*
     * shader描述
    */
    struct ShaderDsp {
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

    /*
     * 采样描述
     */
    struct SamplerDsp {
        s32 m_chn;
        SVString m_warps;
        SVString m_warpt;
        SVString m_min;
        SVString m_mag;
    };

    /*
     * 包含文件和采样器
     */

    class SVShader : public SVGBaseEx {
    public:
        SVShader(SVInstPtr _app);
        
        ~SVShader();
        
        //渲染内核
        void bindRes(SVRShaderPtr _res);
        
        void unbindRes();
        
        SVRShaderPtr getResShader();
        
        bool active();
        
    public:
        ShaderDsp m_dsp;
        std::vector<SamplerDsp> m_vs_sampler;
        std::vector<SamplerDsp> m_fs_sampler;
        std::vector<SamplerDsp> m_gs_sampler;
        
    protected:
        SVRShaderPtr m_res_shader;
    };

}//!namespace sv



#endif //SV_SHADER_H
