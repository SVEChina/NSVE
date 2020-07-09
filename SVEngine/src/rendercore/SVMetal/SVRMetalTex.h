//
// SVRMetalTex.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RESMETAL_TEX_H
#define SV_RESMETAL_TEX_H

#include "../SVRResTex.h"
#include "../SVRShader.h"
#import <Metal/MTLTexture.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLLibrary.h>
#import <Metal/MTLRenderPipeline.h>

namespace sv {

        /*
        纹理资源
         */
        class SVRMetalTex: public SVRResTex {
        public:
            SVRMetalTex(SVInstPtr _app);
            
            virtual ~SVRMetalTex();
            
            virtual void create(SVRendererPtr _renderer);
            
            virtual void destroy(SVRendererPtr _renderer);
            
            virtual void setTexData(void *_data, s32 _len);
            
            virtual void commit();  //数据提交到显卡
            
            virtual bool getbLoad();
            
            u32  getTexID();
            
            u32  getuid();
            
        protected:
            id<MTLTexture> m_srcTex;
        };
        
        /*
         Shader资源
         */
        class SVRMetalShader: public SVRShader {
        public:
            SVRMetalShader(SVInstPtr _app);
            
            virtual ~SVRMetalShader();
            
            virtual void create(SVRendererPtr _renderer);
            
            virtual void destroy(SVRendererPtr _renderer);
            
            virtual bool active(SVRendererPtr _render);
            
        protected:
            id<MTLFunction> m_pVS;
            id<MTLFunction> m_pFS;
            id<MTLRenderPipelineState> m_pProgram;
        };
        
    

}//!namespace sv



//
#endif //SV_RRESMETAL_TEX_H
