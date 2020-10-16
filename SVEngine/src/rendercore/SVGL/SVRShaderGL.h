//
// SVRShaderGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RSHADER_GL_H
#define SV_RSHADER_GL_H

#include "../SVRShader.h"

namespace sv {

    /*
     GL Shader
     */

    class SVRShaderGL: public SVRShader {
    public:
        SVRShaderGL(SVInstPtr _app);

        ~SVRShaderGL();

        void create(SVRendererPtr _renderer,ShaderDsp* _shader_dsp);
        
        void destroy(SVRendererPtr _renderer);

        bool active(SVRendererPtr _renderer);

        void submitSurface(SVSurfacePtr _surface);
        
        void submitParamTbl();

    private:
        static u32 _loadShader(SVInstPtr _app,SVRendererPtr _renderer,cptr8 _filename,s32 _shaderType);

        u32 _createProgram();

        void _clearShaderRes();

        u32 m_programm;
        
        u32 m_vs;

        u32 m_fs;

        u32 m_gs;

        u32 m_tsc;

        u32 m_tse;

        u32 m_cs;
        
        bool m_block;
    };
        
}//!namespace sv



//
#endif //SV_RSHADER_GL_H
