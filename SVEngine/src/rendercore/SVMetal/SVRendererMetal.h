//
// SVRendererMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERER_METAL_H
#define SV_RENDERER_METAL_H

#include "../SVRenderer.h"
#include "../SVRenderDeclare.h"
#include "SVRTexMetal.h"
#include <vector>

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <Metal/Metal.h>
#import <Metal/MTLRenderCommandEncoder.h>
#import <MetalKit/MetalKit.h>

namespace sv {

    /*
    Metal渲染器
    */

    class SVRendererMetal : public SVRenderer {
    public:
        SVRendererMetal(SVInstPtr _app);

        ~SVRendererMetal();
        
        SVRendererMetalPtr share();
        
        void init();

        void init(id<MTLDevice> _device);
        
        //销毁
        void destroy();
        
        //重置大小
        void resize(s32 _w,s32 _h);

        //create-texture
        SVRTexPtr createResTexture();

        //create-shader
        SVRShaderPtr createResShader();

        //create-buf
        SVRMeshResPtr createResBuf();

        //create-fbo
        SVRFboPtr createResFbo();
        
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

        /*
        process
        */
        //处理材质
        bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface);
        
        //处理纹理
        bool processTexture(SVRTexPtr _tex,s32 _chn,s32 _type);

        //处理mesh
        bool processMesh(SVRenderMeshPtr _mesh);

        //
        void drawMesh(SVRenderMeshPtr _mesh);
        
        //
        void drawScreen(SV_TEXIN _texid);

        //
        void pushEncoder(id<MTLRenderCommandEncoder> _encoder);
        
        //
        void popEncoder();
        
    public:
        id<MTLDevice> m_pDevice;
        id<MTLCommandQueue> m_cmdQuene;
        id<MTLCommandBuffer> m_cmdBuffer;
        id<MTLLibrary> m_pLibrary;
        //
        id<MTLRenderCommandEncoder> m_curEncoder;   //encoder不要支持嵌套
        //prop
        bool m_iOS9Runtime;
        bool m_macOS11Runtime;
        bool m_hasPixelFormatDepth32Float_Stencil8;
        s32 m_samplenum;
        //
        void drawBox();
        
        typedef SVObjectPool<SVRFboMetalPtr,SVRFboMetal> PoolFboMetal;
        typedef SVObjectPool<SVRMeshMetalPtr,SVRMeshMetal> PoolMeshMetal;
        typedef SVObjectPool<SVRShaderMetalPtr,SVRShaderMetal> PoolShaderMetal;
        typedef SVObjectPool<SVRTexMetalPtr,SVRTexMetal> PoolTexMetal;
        typedef std::shared_ptr<PoolFboMetal> RFboPoolPtr;
        typedef std::shared_ptr<PoolMeshMetal> RMeshPoolPtr;
        typedef std::shared_ptr<PoolShaderMetal> RShaderPoolPtr;
        typedef std::shared_ptr<PoolTexMetal> RTexPoolPtr;
        //对象池
        RFboPoolPtr m_rfbo_pool;
        RMeshPoolPtr m_rmesh_pool;
        RShaderPoolPtr m_rshader_pool;
        RTexPoolPtr m_rtex_pool;
    };
        
}//!namespace sv
//
#endif //SV_RENDERER_METAL_H
