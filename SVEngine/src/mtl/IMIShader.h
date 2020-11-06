//
// IMIShader.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SHADER_H
#define IMI_SHADER_H

#include "IMIMtlDeclare.h"
#include "../base/IMIGBase.h"
#include "../base/IMIResDsp.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../core/IMIVertDef.h"
#include <string>
#include <vector>

namespace imi {

    /*
     * 包含文件和采样器
     */
    class IMIShader : public IMIGBaseEx {
    public:
        IMIShader(IMIInstPtr _app);
        
        ~IMIShader();
        
        IMIShaderPtr share();

        void dispatch();
        
        //渲染内核
        void bindRes(s32 _instid);
        
        void unbindRes();
        
        IMIRShaderPtr getResShader();
        
        bool active();
        
        void submitParam(IMIParamTblPtr _param);
        
        bool toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                        RAPIDJSON_NAMESPACE::Value &_objValue);

        bool fromJSON(RAPIDJSON_NAMESPACE::Value &item,cptr8 _language);
        
        IMISurfacePtr createSurface();
        
        ShaderDsp* getShaderDsp() { return &m_shader_dsp; }
        
        IMIString getSamplerName(s32 stage,s32 _chn);

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

}//!namespace imi



#endif //IMI_SHADER_H
