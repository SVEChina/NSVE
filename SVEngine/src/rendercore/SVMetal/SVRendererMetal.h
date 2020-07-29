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

        virtual void init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex);

        //初始化
        virtual void init(s32 _w,s32 _h);
        //销毁
        virtual void destroy();
        //重置大小
        virtual void resize(s32 _w,s32 _h);

    public:
        SVRTexPtr createResTexture();

        //shader
        SVRShaderPtr createResShader() ;

        //buf-vbo 等
        SVRBufferPtr createResBuf() ;

        //fbo
        SVRFboPtr createResFbo() ;

    public:
        //
        virtual void processTech(SVRTechPtr _tech);

        //处理材质
        virtual void processMtl(SVMtlCorePtr _mtl);

        //处理mesh
        virtual void processMesh(SVRenderMeshPtr _mesh);

    public:
        id<MTLDevice> m_pDevice;
        id<MTLCommandQueue> m_pCmdQueue;
        id<MTLLibrary> m_pLibrary;
        id<MTLRenderCommandEncoder> m_pCurEncoder;
        
    public:
        //prop
        bool m_iOS9Runtime;
        bool m_macOS11Runtime;
        bool m_hasPixelFormatDepth32Float_Stencil8;
        s32 m_samplenum;
        
    public:
        void drawBox();
    };
        
    
    
}//!namespace sv
//
#endif //SV_RENDERER_METAL_H
