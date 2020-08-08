//
// SVMtlCore.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MTLCORE_H
#define SV_MTLCORE_H

#include "SVMtlDef.h"
#include "../base/SVGBase.h"
#include "../app/SVInst.h"
#include "../rendercore/SVRenderDeclare.h"
#include "SVShaderMgr.h"

//
#include <vector>
#include <string>

namespace sv {

    //
    struct TexUnit {
    public:
        TexUnit();
        
        ~TexUnit();
        
        void copy(TexUnit& _texunit);
        
        void reset();
        
        s32 m_stage_type;   //纹理使用阶段类型，0:fs 1:vs
        
        s32 m_chn;          //纹理使用的通道
        
        SVTEXINID m_texForm;  //纹理来源
        
        SVString m_fname;
        
        SVTexturePtr m_pTex;
    };

    //
    class SVMtlCore : public SVGBaseEx {
        //
        friend class SVMtlLib;
        friend class SVRenderer;
        friend class SVRendererMetal;
        friend class SVRendererGL;
        friend class std::shared_ptr<SVRenderer> ;
        friend class std::shared_ptr<SVRendererMetal> ;
        friend class std::shared_ptr<SVRendererGL> ;
        //
    public:
        SVMtlCore(SVInstPtr _app);
        
        SVMtlCore(SVInstPtr _app, cptr8 _shader);
        
        SVMtlCore(SVInstPtr _app, SVShaderPtr _shader);
        
        SVMtlCore(SVMtlCore* _mtl);
        
        ~SVMtlCore();
        
        virtual SVMtlCorePtr clone();
        
        virtual void reset();
        
        virtual void update(f32 dt);
        
        virtual s32 submitMtl();
        
        void setTexture(s32 _chn,s32 _stage,SVTEXINID _from,cptr8 _name);

        void setTexture(s32 _chn,cptr8 _fname);
        
        void setTexture(s32 _chn,SVTexturePtr _texture);
               
        void setTexture(s32 _chn,sv::SVTEXINID _from);
        
        SVShaderPtr getShader() { return m_shader_obj; }
        
    protected:
        //材质名称
        SVString m_mtl_name;
        //shader名称
        SVString m_shader_name;
        //MTLFLAG0;
        s32 m_LogicMtlFlag0;
        //融合参数
        s32 m_blend_enable;
        s32 m_blend_src_param;
        s32 m_blend_dst_param;
        //裁剪面参数
        s32 m_cull_enable;
        s32 m_frontFace;
        s32 m_cullFace;
        //深度参数
        s32 m_depth_clear;
        s32 m_depth_enable;        //开启深度测试
        //深度测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
        s32 m_depthtest_method;
        //模板参数
        s32 m_stencil_clear;         //
        s32 m_stencil_enable;        //开启模板测试
        s32 m_stencil_passMethod;     //通过模板测试的规则(GL_NEVER,GL_LESS < ,GL_LEQUAL <= ,GL_GREATER > ,GL_GEEQUAL >= ,GL_EQUAL == ,GL_ALWAYS)
        s32 m_stencil_refValue;       //通过模板测试的参考值(0-255)
        s32 m_stencil_maskValue;      //掩码( 模板值&掩码 * 参考值&掩码 )
        s32 m_stencil_sfail;          //模板测试失败     (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 m_stencil_zfail;          //模板通过 深度失败 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 m_stencil_zpass;          //模板通过 深度通过 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写≤
        //Z偏移参数
        s32 m_zoff_enable;
        f32 m_zoff_factor;
        f32 m_zoff_unit;
         //alpha参数
        s32 m_alpha_enable;         //开启alpha测试
        s32 m_alpha_testMethod;     //alpha测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
        //纹理参数
        TexUnit m_texUnit[MAX_TEXUNIT];
        //
        SVShaderPtr m_shader_obj;   //pointer
        //
    public:
        void swap();
        
        void setBlendEnable(bool _bBlendEnable);
        
        void setBlendState(s32 _src , s32 _dst);
        
        void setDepthEnable(bool _bDepthEnable);
        
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
        
        virtual void fromJSON1(RAPIDJSON_NAMESPACE::Value &item);
        
    protected:
        virtual void _submitUniform(SVRendererPtr _render);
        
        virtual void _submitMtl(SVRendererPtr _render);
    };

}//!namespace sv



#endif //SV_MTLCORE_H
