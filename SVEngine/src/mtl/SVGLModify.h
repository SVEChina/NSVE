//
// SVGLModify.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_GL_MODIFY_H
#define SV_GL_MODIFY_H

#include "../base/SVModify.h"

//GL渲染命令

namespace sv {
        
    class SVGLModify: public SVModify {
    public:
        SVGLModify(SVInstPtr _app);
    };
    
    //修正纹理参数
    class SVGLModifyTex: public SVGLModify {
    public:
        SVGLModifyTex(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        u32 m_texChanel;
        u32 m_texID;
    };
    
    //修正纹理参数
    class SVGLModifyTexParam: public SVGLModify {
    public:
        SVGLModifyTexParam(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        u32 m_texChanel;
        u32 m_texID;
        u32 m_paramType;
        u32 m_paramValue;
    };
    
    //线宽
    class SVGLModifyLineWidth: public SVGLModify {
    public:
        SVGLModifyLineWidth(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        u32 m_size;
    };
    
    //点大小
    class SVGLModifyPointSize: public SVGLModify {
    public:
        SVGLModifyPointSize(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        u32 m_size;
    };
    
    //修正融合
    class SVGLModifyBlend: public SVGLModify {
    public:
        SVGLModifyBlend(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        bool m_enable;
        u32 m_srcparam;
        u32 m_dstparam;
    };
    
    //修正CullFace
    class SVGLModifyCullFace: public SVGLModify {
    public:
        SVGLModifyCullFace(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        bool m_enable;
        u32 m_front;
        u32 m_cull;
    };
    
    //修正深度
    class SVGLModifyDepth: public SVGLModify {
    public:
        SVGLModifyDepth(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        bool m_clear;
        bool m_enable;
    };
    
    //修正Stencil
    class SVGLModifyStencil: public SVGLModify {
    public:
        SVGLModifyStencil(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        //
        bool m_clear;
        f32 m_clearValue;
        //
        bool m_enable;
        u32 m_passMethod;
        u32 m_refValue;
        u32 m_maskValue;
        u32 m_sfail;
        u32 m_zfail;
        u32 m_zpass;
    };
    
    //修正shader
    class SVGLModifyShader: public SVGLModify {
    public:
        SVGLModifyShader(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        u32 m_shaderID;
    };
    
    //传递uniform
    class SVGLModifyUnif32: public SVGLModify {
    public:
        SVGLModifyUnif32(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        u32 m_shaderID;
        SVString m_name;
        f32 m_value;
    };
    
    //传递uniform
    class SVGLModifyUnif32v2: public SVGLModify {
    public:
        SVGLModifyUnif32v2(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        SVString m_name;
        f32 m_data[2];
    };
    
    //传递uniform
    class SVGLModifyUniMatrix: public SVGLModify {
    public:
        SVGLModifyUniMatrix(SVInstPtr _app);
        void exec(SVObjectPtr _obj);
        u32 m_shaderID;
        SVString m_name;
        f32 m_mat_model[16];
    };
        
    
}//!namespace sv



#endif //SV_GL_MODIFY_H
