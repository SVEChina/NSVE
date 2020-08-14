//
// SVRendererVK.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERER_VULKAN_H
#define SV_RENDERER_VULKAN_H

#include "../SVRenderer.h"

namespace sv {
    
    //vulkan 渲染器

    class SVRendererVK : public SVRenderer {
    public:
        SVRendererVK(SVInstPtr _app);
        
        ~SVRendererVK();
        
        //初始化
        virtual void init(s32 _w,s32 _h){}
        
        //销毁
        virtual void destroy(){}
        
        //重置大小
        virtual void resize(s32 _w,s32 _h){}
        
        //创建纹理资源
        virtual SVRTexPtr createResTexture() { return nullptr; }
        
        //创建shader资源
        virtual SVRShaderPtr createResShader() { return nullptr; }
        
        //创建buf资源
        virtual SVRMeshResPtr createResBuf() { return nullptr; }
        
        //创建fbo资源
        virtual SVRFboPtr createResFbo() { return nullptr; }
        
        //创建target资源
        virtual SVRTargetPtr createTarget(SVINTEX _texid){ return nullptr; }
        
        //获取target
        virtual SVRTargetPtr getTarget(SVINTEX _texid){ return nullptr; }
        
        //销毁Target
        virtual void destroyTarget(SVINTEX _texid) {}
        
        //处理材质
        virtual bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface){ return false; }
        
        //处理纹理
        virtual bool processTexture(SVRTexPtr _tex,s32 _chn,s32 _type) { return false; }
        
        //处理mesh
        virtual bool processMesh(SVRenderMeshPtr _mesh){ return false; }
        
        //绘制mesh
        virtual void drawMesh(SVRenderMeshPtr _mesh){ }
        
        //绘制屏幕
        virtual void drawScreen(SVINTEX _texid) { }
        
    };
    

}//!namespace sv





//
#endif //SV_RENDERER_VULKAN_H
