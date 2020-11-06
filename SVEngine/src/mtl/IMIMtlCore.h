//
// IMIMtlCore.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTLCORE_H
#define IMI_MTLCORE_H

#include "IMIMtlDef.h"
#include "../base/IMIGBase.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "IMIShaderMgr.h"
#include <vector>
#include <string>

namespace imi {

    //
    LUA_REG_DECLARE(TexUnit);
    //
    struct TexUnit {
    public:
        TexUnit();
        
        ~TexUnit();
        //重置
        void reset();
        //纹理使用阶段类型，0:fs 1:vs
        s32 m_stage_type;
        //纹理使用的通道
        s32 m_chn;
        //纹理来源
        IMI_TEXIN m_texForm;
        //纹理名称
        IMIString m_fname;
        //纹理指针
        IMITexturePtr m_pTex;
    };

    //
    LUA_REG_DECLARE(IMIMtlCore);
    //
    class IMIMtlCore : public IMIGBaseEx {
        friend class IMIMtlLib;
        friend class IMIRenderer;
        friend class IMIRendererMetal;
        friend class IMIRendererGL;
        friend class std::shared_ptr<IMIRenderer> ;
        friend class std::shared_ptr<IMIRendererMetal> ;
        friend class std::shared_ptr<IMIRendererGL> ;
    public:
        IMIMtlCore(IMIInstPtr _app);
        
        IMIMtlCore(IMIInstPtr _app, cptr8 _shader);
        
        IMIMtlCore(IMIInstPtr _app, IMIShaderPtr _shader);
        
        IMIMtlCore(IMIMtlCore* _mtl);
        
        virtual ~IMIMtlCore();
        
        virtual IMIMtlCorePtr clone();
        
        virtual void reset();
        
        virtual void update(f32 dt);
        
        virtual s32 submitMtl();
        
        void setTexture(s32 _chn,s32 _stage,IMI_TEXIN _from,cptr8 _name);

        void setTexture(s32 _chn,s32 _stage,cptr8 _fname);
        
        void setTexture(s32 _chn,s32 _stage,IMITexturePtr _texture);
               
        void setTexture(s32 _chn,s32 _stage,imi::IMI_TEXIN _from);
        
        void setShader(ptr8 _sname,std::vector<IMIString>& _sdef);
        
        IMIShaderPtr getShader() { return m_shader_obj; }
        
    protected:
        //材质名称
        IMIString m_mtl_name;
        //shader名称
        IMIString m_shader_name;
        //绑定脚本
        IMIString m_script;
        //
        s32 m_LogicMtlFlag0;
        //融合参数
        s32 m_blend_enable;
        s32 m_blend_src_param;
        s32 m_blend_dst_param;
        
        s32 m_blend_separate_enable;
        s32 m_blend_separate_src_rgb;
        s32 m_blend_separate_dst_rgb;
        s32 m_blend_separate_src_alpha;
        s32 m_blend_separate_dst_alpha;
        s32 m_blend_separate_equation;
        
        //裁剪面参数
        s32 m_cull_enable;
        s32 m_frontFace;
        s32 m_cullFace;
        //深度参数
        s32 m_depth_clear;
        //开启深度测试
        s32 m_depth_enable;
        //深度测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
        s32 m_depth_method;
        //模板参数
        s32 m_stencil_clear;
        //开启模板测试
        s32 m_stencil_enable;
        //通过模板测试的规则(GL_NEVER,GL_LESS < ,GL_LEQUAL <= ,GL_GREATER > ,GL_GEEQUAL >= ,GL_EQUAL == ,GL_ALWAYS)
        s32 m_stencil_passMethod;
        //通过模板测试的参考值(0-255)
        s32 m_stencil_ref;
        //掩码( 模板值&掩码 * 参考值&掩码 )
        s32 m_stencil_mask;
        //模板测试失败(GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 m_stencil_sfail;
        //模板通过，深度失败(GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 m_stencil_zfail;
        //模板通过 深度通过 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写≤
        s32 m_stencil_zpass;
        //Z偏移参数
        s32 m_zoff_enable;
        f32 m_zoff_factor;
        f32 m_zoff_unit;
        //开启alpha测试
        s32 m_alpha_enable;
        //alpha测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
        s32 m_alpha_method;
        //纹理参数
        TexUnit m_vs_texUnit[MAX_TEXUNIT];
        TexUnit m_fs_texUnit[MAX_TEXUNIT];
        //shader宏
        std::vector<IMIString> m_shader_defs;
        //shader对象
        IMIShaderPtr m_shader_obj;
        //
        bool m_shader_dirty;
        
    public:
        void swap();
        
        void setBlendEnable(bool _bBlendEnable);
        
        void setBlendState(s32 _src, s32 _dst);
        
        void setBlendSeparateEnable(bool _enable);
        void setBlendSeparateState(s32 _srcRGB, s32 _dstRGB, s32 _srcAlpha, s32 _dstAlpha, s32 _equation);
        
        void setDepthEnable(bool _enable);
        void setDepthMethod(s32 _method);
        
        void setCullEnable(bool _bCullEnable);
        
        void setCullFace(s32 _frontFace, s32 _cullFace);
        
        void setZOffEnable(bool _enable);
        
        void setZOffParam(f32 _factor,f32 _unit);
        
        //设置模版测试
        void setStencilEnable(bool _bStencilEnable);
        
        void setStencilClear(bool _clear);
        
        void setStencilPass(s32 _pass);
        
        void setStencilRef(s32 _ref);
        
        void setStencilMask(s32 _mask);
        
        void setStencilZPass(s32 _method);
        
        void setStencilZfail(s32 _method);
        
        void setStencilSfail(s32 _method);
        
        void reloadShader();
        
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON1(RAPIDJSON_NAMESPACE::Value& item);
        
    protected:
        virtual void _submitUniform(IMIRendererPtr _render);
        
        virtual void _submitMtl(IMIRendererPtr _render);
    };


}//!namespace imi



#endif //IMI_MTLCORE_H
