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
        
        void init(s32 _w,s32 _h);

        void init(id<MTLDevice> _device,s32 _w,s32 _h);
        
        //销毁
        void destroy();
        //重置大小
        void resize(s32 _w,s32 _h);

        /*
         create
         */
        SVRTexPtr createResTexture();

        //shader
        SVRShaderPtr createResShader() ;

        //buf-vbo 等
        SVRMeshResPtr createResBuf() ;

        //fbo
        SVRFboPtr createResFbo() ;

        /*
        process
        */
        //处理材质
        bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface);
        
        //处理纹理
        bool processTexture(SVRTexPtr _tex,s32 _chn,s32 _type);

        //处理mesh
        bool processMesh(SVRenderMeshPtr _mesh);

        /*
        draw
        */
        void drawMesh(SVRenderMeshPtr _mesh);
        
        //
        SVRTargetPtr createTarget(SVINTEX _texid);

    public:
        id<MTLDevice> m_pDevice;
        id<MTLCommandQueue> m_pCmdQueue;
        id<MTLLibrary> m_pLibrary;
        id<MTLRenderCommandEncoder> m_pCurEncoder;
        //prop
        bool m_iOS9Runtime;
        bool m_macOS11Runtime;
        bool m_hasPixelFormatDepth32Float_Stencil8;
        s32 m_samplenum;
        //
        void drawBox();
    };
        
}//!namespace sv
//
#endif //SV_RENDERER_METAL_H
