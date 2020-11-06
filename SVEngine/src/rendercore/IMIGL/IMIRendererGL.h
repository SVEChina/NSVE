//
// IMIRendererGL.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERERGL_H
#define IMI_RENDERERGL_H

#include "../IMIRenderer.h"
#include "../../core/IMIVertDef.h"

namespace imi {
    /*
     GL渲染器
     */
    class IMIRendererGL : public IMIRenderer {
    public:
        IMIRendererGL(IMIInstPtr _app);
        
        ~IMIRendererGL();
        
        IMIRendererGLPtr share();
        
        void init(s32 _version);

        void init(s32 _version,bool _offline);

        void resize(s32 _w,s32 _);
        
        void info();
    
        //create-texture
        IMIRTexPtr createResTexture() ;

        //create-shader
        IMIRShaderPtr createResShader() ;

        //create-buf-vbo
        IMIRMeshResPtr createResBuf() ;

        //create-fbo
        IMIRFboPtr createResFbo() ;
        
        //销毁纹理资源
        void destroyResTexture(s32 _uid);

        //销毁shader资源
        void destroyResShader(s32 _uid) ;

        //销毁buf资源
        void destroyResBuf(s32 _uid);

        //销毁fbo资源
        void destroyResFbo(s32 _uid) ;
        
        //获取纹理资源
        IMIRTexPtr getResTexture(s32 _uid) const;

        //获取shader资源
        IMIRShaderPtr getResShader(s32 _uid) const;

        //获取buf资源
        IMIRMeshResPtr getResBuf(s32 _uid) const;

        //获取fbo资源
        IMIRFboPtr getResFbo(s32 _uid) const;
        
        void bindTarget(s32 _poolid);

        void unbindTarget(s32 _poolid);
        
        //处理材质
        bool processMtl(IMIMtlCorePtr _mtl,IMISurfacePtr _surface);
        
        //处理纹理
        bool processTexture(IMIRTexPtr _tex,s32 _index,cptr8 _samplename);
       
        //处理mesh
        bool processMesh(IMIRenderMeshPtr _mesh);
        
        //绘制mesh
        void drawMesh(IMIRenderMeshPtr _mesh);
        
        //绘制屏幕
        void drawScreen(IMI_TEXIN _texid);
        
        void debugMesh2d(IMIRenderMeshPtr _mesh);
        
        void debugMesh3d(IMIRenderMeshPtr _mesh);
        
    public:
        u32 m_cur_program;  //当前的program
        s32 m_gl_version;
        //
        typedef IMIObjectPool<IMIRFboGLPtr,IMIRFboGL> PoolFboGL;
        typedef IMIObjectPool<IMIRMeshGLPtr,IMIRMeshGL> PoolMeshGL;
        typedef IMIObjectPool<IMIRShaderGLPtr,IMIRShaderGL> PoolShaderGL;
        typedef IMIObjectPool<IMIRTexGLPtr,IMIRTexGL> PoolTexGL;
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

}//!namespace imi




//
#endif //IMI_RENDERERGL_H
