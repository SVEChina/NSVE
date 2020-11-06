//
// IMIRShaderGL.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RSHADER_GL_H
#define IMI_RSHADER_GL_H

#include "../IMIRShader.h"

namespace imi {

    /*
     GL Shader
     */

    class IMIRShaderGL: public IMIRShader {
    public:
        IMIRShaderGL(IMIInstPtr _app);

        ~IMIRShaderGL();

        void load(IMIRendererPtr _renderer,ShaderDsp* _shader_dsp);
        
        void unload();

        bool active(IMIRendererPtr _renderer);
        
        void submitParamTbl();

    private:
        u32 _loadShader(IMIRendererPtr _renderer,ShaderDsp* _shader_dsp,cptr8 _filename,s32 _shaderType);

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
        
}//!namespace imi



//
#endif //IMI_RSHADER_GL_H
