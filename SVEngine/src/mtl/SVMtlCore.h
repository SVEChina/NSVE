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
    
        class SVMtlCoreParam : public SVObject {
        public:
            SVMtlCoreParam();
            
            virtual SVMtlCorePtr genMtl(SVInst *_app);
            
            s32 m_shader;
        };
        
        //
        class SVMtlCore : public SVGBase {
            friend class SVRenderer;
            friend class SVRendererGL;
            friend class SVRendererMetal;
            friend class SVRendererVulkan;
            
        public:
            SVMtlCore(SVInst *_app, cptr8 _shader);
            
            SVMtlCore(SVMtlCore* _mtl);
            
            ~SVMtlCore();
            
            virtual SVMtlCorePtr clone();
            
            virtual void reset();
            
            virtual void update(f32 dt);
            
            virtual s32 submitMtl();
            
            virtual void recoverMtl();
            
            //设置参数值 主要是针对uniform
            void setParam(cptr8 _name,s32 _value);
            
            void setParam(cptr8 _name,f32 _value);
            
            void setParam(cptr8 _name,FVec2 _value);
            
            void setParam(cptr8 _name,FVec3 _value);
            
            void setParam(cptr8 _name,FVec4 _value);
            
            void setParam(cptr8 _name,FMat4 _value);
            
            void* getParam(cptr8 _name);
            
            //
        protected:
            //参数表
            struct InParam {
                std::string m_name; //参数名称
                int m_size;         //参数数据大小
                u64 m_off;          //参数数据偏移
            };
            //
            std::vector<InParam> m_aramTbl;
            //参数值
            SVDataChunkPtr m_ParamValues;
            
        public:
            SVRTechPtr _tech;
            //技术（shader）
            
            //uniform
            
            //采样器
            
            //状态
            
        public:
            
            void swap();
                        
            void setTexture(s32 _chanel,SVTexturePtr _texture);
            
            void setTexture(s32 _chanel,SVTEXTYPE _from);
            
            void setTexcoordFlip(f32 _x, f32 _y);
            
            void setTextureParam(s32 _chanel,TEXTUREPARAM _type,s32 _value);
            
            void setModelMatrix(f32 *_mat);
            
            void setViewMatrix(f32 *_mat);
            
            void setProjMatrix(f32 *_mat);
            
            void setVPMatrix(f32 *_mat);
            
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
            s32 m_pShader;                  //shaderid
            s32 m_LogicMtlFlag0;                         //MTLFLAG0;
            SVMatrixParam m_LogicParamMatrix;            //矩阵信息
            SVTextureParam m_LogicParamTex;              //纹理参数
            SVBlendParam m_LogicParamBlend;              //融合参数
            SVCullFaceParam m_LogicParamCull;            //裁剪面参数
            SVDepthParam m_LogicParamDepth;              //深度参数
            SVStencilParam m_LogicParamStencil;          //模板参数
            SVAlphaParam m_LogicParamAlpha;              //alpha参数
            SVSizeParam m_LogicParamSize;                //尺寸参数
            SVZOffParam m_LogicParamZOff;                //Z偏移参数
            
        protected:
            void _loadShader();
            virtual void _refreshMatrix();
            virtual void _refreshModify();
            virtual void _submitUniform(SVRendererPtr _render);
            virtual void _submitTexture(SVRendererPtr _render);
            virtual void _submitState(SVRendererPtr _render);
            virtual void _submitMtl(SVRendererPtr _render);
            
            
        public:
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
