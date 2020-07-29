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
        //param
        std::vector<MtlParamDsp> m_paramTbl;  //参数表
        SVDataChunkPtr m_paramValues;    //参数值
        
        //纹理参数
        SVTextureParam m_paramTex;              //纹理参数
        SVBlendParam m_LogicParamBlend;         //融合参数
        SVCullFaceParam m_LogicParamCull;       //裁剪面参数
        SVDepthParam m_LogicParamDepth;         //深度参数
        SVStencilParam m_LogicParamStencil;     //模板参数
        SVAlphaParam m_LogicParamAlpha;         //alpha参数
        SVZOffParam m_LogicParamZOff;           //Z偏移参数
        
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
        
        void reloadShader(cptr8 _shader);
        
    public:
        SVString m_mtlname;
        s32 m_pShader;        //shaderid
        s32 m_LogicMtlFlag0;  //MTLFLAG0;
        
        SVMatrixParam m_LogicParamMatrix;            //矩阵信息
        
    protected:
        void _loadShader();
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
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    
    protected:
        virtual void _toJsonData(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                                 RAPIDJSON_NAMESPACE::Value &locationObj);
        virtual void _fromJsonData(RAPIDJSON_NAMESPACE::Value &item);
    };

    
    
}//!namespace sv



#endif //SV_MTLCORE_H
