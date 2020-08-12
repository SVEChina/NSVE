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
#include "../core/SVVertDef.h"
#include <string>
#include <vector>

namespace sv {

    /*
     * shader描述
    */
    struct ShaderDsp {
        ShaderDsp() {
            m_dsp = 0;
            m_post = 0;
            m_programme_fname = "null";
            m_vs_fname = "null";
            m_fs_fname = "null";
            m_gs_fname = "null";
            m_cs_fname = "null";
            m_tsc_fname = "null";
            m_tse_fname = "null";
            m_attri_formate = "null";
            m_vft.clear();
        };
        //
        s32 m_dsp;
        s32 m_post; //是否是后处理
        std::vector<s32> m_vft;
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
        s32 m_stage; //0:vs 1:fs 2:gs
        SVString m_warps;
        SVString m_warpt;
        SVString m_min;
        SVString m_mag;
    };

    /*
     * 参数表描述
     */
    struct ParamTblDsp {
        s32 m_id;               //传递的bufid
        s32 m_stage;            // 0:vs, 1:fs
        SVParamTblPtr m_tbl;    //表
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
        
        void submitParam(SVParamTblPtr _param);
        
        bool toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                        RAPIDJSON_NAMESPACE::Value &_objValue);

        bool fromJSON(RAPIDJSON_NAMESPACE::Value &item);

    public:
        ShaderDsp m_shader_dsp;
        //采样器
        std::vector<SamplerDsp> m_samplers;
        //参数表
        std::vector<ParamTblDsp> m_paramtbl;
        
    protected:
        SVRShaderPtr m_res_shader;
        
    public:
        //创建采样器描述
        static void SamplerDspFromJson(RAPIDJSON_NAMESPACE::Value &item,SamplerDsp& _dsp);
        
        //创建参数表描述
        static void ParamTblFromJson(RAPIDJSON_NAMESPACE::Value &item,ParamTblDsp& _dsp);
    };

}//!namespace sv



#endif //SV_SHADER_H
