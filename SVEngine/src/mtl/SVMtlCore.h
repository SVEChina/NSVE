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
#include "SVMtlParamBase.h"
//
#include <vector>
#include <string>

namespace sv {

    //
    class SVMtlCore : public SVGBaseEx {
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
        
        virtual void recoverMtl();
        
        //增加参数
        void addParam(cptr8 _name,cptr8 _type,cptr8 _value);
        
        //设置参数值 主要是针对uniform
        void setParam(cptr8 _name,s32 _value);
        
        void setParam(cptr8 _name,f32 _value);
        
        void setParam(cptr8 _name,FVec2 _value);
        
        void setParam(cptr8 _name,FVec3 _value);
        
        void setParam(cptr8 _name,FVec4 _value);
        
        void setParam(cptr8 _name,FMat4 _value);
        
        void* getParam(cptr8 _name);
        
        //
        void setTexture(s32 _chanel,cptr8 _fname);
        
        void setTexture(s32 _chanel,SVTexturePtr _texture);
               
        void setTexture(s32 _chanel,sv::SVTEXINID _from);
        
    protected:
        SVString m_mtl_name;
        SVString m_shader_name;
        //param
        std::vector<MtlParamDsp> m_paramTbl;  //参数表
        SVDataChunkPtr m_paramValues;    //参数值
        
        //
        bool m_blend_enable;
        MTLBLENDFUNC m_blend_src_param;
        MTLBLENDFUNC m_blend_dst_param;
        
        //裁剪面参数
        bool m_cull_enable;
        s32 frontFace;
        s32 cullFace;
        
        //深度参数
        bool m_depth_clear;
        bool m_depth_enable;        //开启深度测试
        //深度测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
        s32 m_depthtest_method;
        
        //模板参数
        bool m_stencil_clear;         //
        bool m_stencil_enable;        //开启模板测试
        s32 m_stencil_passMethod;     //通过模板测试的规则(GL_NEVER,GL_LESS < ,GL_LEQUAL <= ,GL_GREATER > ,GL_GEEQUAL >= ,GL_EQUAL == ,GL_ALWAYS)
        s32 m_stencil_refValue;       //通过模板测试的参考值(0-255)
        s32 m_stencil_maskValue;      //掩码( 模板值&掩码 * 参考值&掩码 )
        s32 m_stencil_sfail;          //模板测试失败     (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 m_stencil_zfail;          //模板通过 深度失败 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
        s32 m_stencil_zpass;          //模板通过 深度通过 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写≤
        
        //Z偏移参数
        bool m_zoff_enable;
        f32 m_zoff_factor;
        f32 m_zoff_unit;
        
         //alpha参数
        bool m_alpha_enable;        //开启alpha测试
        s32 m_alpha_testMethod;     //alpha测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
        
        //纹理参数
        SVTextureParam m_paramTex;
        
    public:
        SVShaderPtr m_shader;
        
        void swap();
        
        void setTextureParam(s32 _chanel,TEXTUREPARAM _type,s32 _value);
        
        void setTexSizeIndex(s32 index, f32 _w, f32 _h);
        
        void setLineSize(f32 _linewidth);
        
        void setBlendEnable(bool _bBlendEnable);
        
        void setBlendState(MTLBLENDFUNC _src , MTLBLENDFUNC _dst);
        
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
        
        s32 m_LogicMtlFlag0;  //MTLFLAG0;
        
        SVMatrixParam m_LogicParamMatrix;            //矩阵信息
        
    protected:
    
        virtual void _refreshMatrix();
        virtual void _refreshModify();
        virtual void _submitUniform(SVRendererPtr _render);
        virtual void _submitTexture(SVRendererPtr _render);
        virtual void _submitState(SVRendererPtr _render);
        virtual void _submitMtl(SVRendererPtr _render);
        
    public:
        //快捷接口而已
        void setModelMatrix(FMat4& _mat);

        void setViewMatrix(FMat4& _mat);

        void setProjMatrix(FMat4& _mat);

        void setVPMatrix(FMat4& _mat);
        
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON1(RAPIDJSON_NAMESPACE::Value &item);
    };

    
    
}//!namespace sv



#endif //SV_MTLCORE_H
