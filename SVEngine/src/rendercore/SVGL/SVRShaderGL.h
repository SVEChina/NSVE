//
// SVRShaderGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RRESGL_SHADER_H
#define SV_RRESGL_SHADER_H

#include "../SVRRes.h"
#include "../SVRTex.h"
#include "../SVRFbo.h"
#include "../SVRShader.h"
#include "../../base/SVPreDeclare.h"
#include "../../base/SVRect.h"
#include "../../core/SVVertDef.h"
#include "../../base/SVDataChunk.h"

namespace sv {
        /*
         GL Shader
         */
        
        class SVRShaderGL: public SVRShader {
        public:
            SVRShaderGL(SVInstPtr _app);

            virtual ~SVRShaderGL();

            virtual void create(SVRendererPtr _renderer);

            virtual void destroy(SVRendererPtr _renderer);
            
            virtual bool active(SVRendererPtr _render);

            void setTechFName(cptr8 _filename);

        private:
            static u32 _loadShader(SVInstPtr _app,cptr8 _filename,s32 _shaderType);
            
            bool _parseTech();

            u32 _loadTechVS(cptr8 _precision,cptr8 _src);

            u32 _loadTechFS(cptr8 _precision,cptr8 _src);

            u32 _loadTechGS(cptr8 _precision,cptr8 _src);

            u32 _createProgram();

            void _clearShaderRes();

            bool m_use_tech;

            SVString m_tech_fname;   //技术

            u32 m_programm;
            
            u32 m_vs;

            u32 m_fs;

            u32 m_gs;

            u32 m_tsc;

            u32 m_tse;

            u32 m_cs;
        };
        

    

}//!namespace sv



//
#endif //SV_RRESGL_SHADER_H
