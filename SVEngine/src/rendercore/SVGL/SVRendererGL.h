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
        
        void init(s32 _version);

        void init(s32 _version,bool _offline);

        void resize(s32 _w,s32 _);
        
        void info();
    
        //create-texture
        SVRTexPtr createResTexture() ;

        //create-shader
        SVRShaderPtr createResShader() ;

        //create-buf-vbo
        SVRMeshResPtr createResBuf() ;

        //create-fbo
        SVRFboPtr createResFbo() ;
        
        //销毁纹理资源
        void destroyResTexture(s32 _uid);

        //销毁shader资源
        void destroyResShader(s32 _uid) ;

        //销毁buf资源
        void destroyResBuf(s32 _uid);

        //销毁fbo资源
        void destroyResFbo(s32 _uid) ;
        
        //获取纹理资源
        SVRTexPtr getResTexture(s32 _uid) const;

        //获取shader资源
        SVRShaderPtr getResShader(s32 _uid) const;

        //获取buf资源
        SVRMeshResPtr getResBuf(s32 _uid) const;

        //获取fbo资源
        SVRFboPtr getResFbo(s32 _uid) const;
        
        void bindTarget(s32 _poolid);

        void unbindTarget(s32 _poolid);
        
        //处理材质
        bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface);
        
        //处理纹理
        bool processTexture(SVRTexPtr _tex,s32 _index,cptr8 _samplename);
       
        //处理mesh
        bool processMesh(SVRenderMeshPtr _mesh);
        
        //绘制mesh
        void drawMesh(SVRenderMeshPtr _mesh);
        
        //绘制屏幕
        void drawScreen(SV_TEXIN _texid);
        
        void debugMesh2d(SVRenderMeshPtr _mesh);
        
        void debugMesh3d(SVRenderMeshPtr _mesh);
        
    public:
        u32 m_cur_program;  //当前的program
        s32 m_gl_version;
        //
        typedef SVObjectPool<SVRFboGLPtr,SVRFboGL> PoolFboGL;
        typedef SVObjectPool<SVRMeshGLPtr,SVRMeshGL> PoolMeshGL;
        typedef SVObjectPool<SVRShaderGLPtr,SVRShaderGL> PoolShaderGL;
        typedef SVObjectPool<SVRTexGLPtr,SVRTexGL> PoolTexGL;
        typedef std::shared_ptr<PoolFboGL> RFboPoolPtr;
        typedef std::shared_ptr<PoolMeshGL> RMeshPoolPtr;
        typedef std::shared_ptr<PoolShaderGL> RShaderPoolPtr;
        typedef std::shared_ptr<PoolTexGL> RTexPoolPtr;
        //对象池
        RFboPoolPtr m_rfbo_pool;
        RMeshPoolPtr m_rmesh_pool;
        RShaderPoolPtr m_rshader_pool;
        RTexPoolPtr m_rtex_pool;
    };

}//!namespace sv




//
#endif //SV_RENDERERGL_H
