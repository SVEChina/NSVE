//
// SVRendererGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERERGL_H
#define SV_RENDERERGL_H

#include "../SVRenderer.h"
#include "../../core/SVVertDef.h"

namespace sv {
        
    /*
     GL渲染器
     */
    
    class SVRendererGL : public SVRenderer {
    public:
        SVRendererGL(SVInstPtr _app);
        
        ~SVRendererGL();
        
        SVRendererGLPtr share();
        
        void init(s32 _w,s32 _h);

        void init(s32 _w,s32 _h,bool _offline);

        void resize(s32 _w,s32 _);
    
        //create-texture
        SVRTexPtr createResTexture() ;

        //create-shader
        SVRShaderPtr createResShader() ;

        //create-buf-vbo
        SVRMeshResPtr createResBuf() ;

        //create-fbo
        SVRFboPtr createResFbo() ;
        
        //create-target
        SVRTargetPtr createTarget(SVINTEX _texid,bool _depth,bool _stencil);
        
        SVRTargetPtr createTarget(SVINTEX _texid,s32 _w,s32 _h,bool _depth,bool _stencil);
        
        //处理材质
        bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface);
        
        //处理纹理
        bool processTexture(SVRTexPtr _tex,s32 _chn,s32 _type);
       
        //处理mesh
        bool processMesh(SVRenderMeshPtr _mesh);
        
        //绘制mesh
        void drawMesh(SVRenderMeshPtr _mesh);
        
        //绘制屏幕
        void drawScreen(SVINTEX _texid);
        
    public:
        u32 m_cur_program;  //当前的program
    };


}//!namespace sv




//
#endif //SV_RENDERERGL_H
