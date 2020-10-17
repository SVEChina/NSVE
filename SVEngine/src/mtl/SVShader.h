//
// SVShader.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SHADER_H
#define SV_SHADER_H

#include "SVMtlDeclare.h"
#include "../base/SVGBase.h"
#include "../base/SVResDsp.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../core/SVVertDef.h"
#include <string>
#include <vector>

namespace sv {

    /*
     * 包含文件和采样器
     */
    class SVShader : public SVGBaseEx {
    public:
        SVShader(SVInstPtr _app);
        
        ~SVShader();
        
        SVShaderPtr share();

        void dispatch();
        
        //渲染内核
        void bindRes(s32 _instid);
        
        void unbindRes();
        
        SVRShaderPtr getResShader();
        
        bool active();
        
        void submitParam(SVParamTblPtr _param);
        
        bool toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                        RAPIDJSON_NAMESPACE::Value &_objValue);

        bool fromJSON(RAPIDJSON_NAMESPACE::Value &item,cptr8 _language);
        
        SVSurfacePtr createSurface();
        
        ShaderDsp* getShaderDsp() { return &m_shader_dsp; }
        
        SVString getSamplerName(s32 stage,s32 _chn);

    protected:
        //描述
        ShaderDsp m_shader_dsp;
        
        //对应的资源ID
        s32 m_res_shader_id;
        
    public:
        //创建采样器描述
        static void SamplerDspFromJson(RAPIDJSON_NAMESPACE::Value &item,SamplerDsp& _dsp);
        
        //创建参数表描述
        static void ParamTblFromJson(RAPIDJSON_NAMESPACE::Value &item,ParamTblDsp& _dsp);
    };

}//!namespace sv



#endif //SV_SHADER_H
