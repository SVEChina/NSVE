//
// SVRenderCmd.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERCMD_RES_H
#define SV_RENDERCMD_RES_H

#include "SVRenderCmd.h"

namespace sv {

    //关于底层资源创建喝销毁的地方

    //创建r-buffer
    class SVRCmdCreateMesh : public SVRenderCmd {
    public:
        SVRCmdCreateMesh(SVRenderMeshPtr _mesh);
        
        ~SVRCmdCreateMesh();
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        SVRenderMeshPtr m_rendermesh;
    };

    //创建R-shader
    class SVRCmdCreateShader : public SVRenderCmd {
    public:
        SVRCmdCreateShader(SVShaderPtr _shader);
        
        ~SVRCmdCreateShader();
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        SVShaderPtr m_shader;
    };

    //创建R-tex
    class SVRCmdCreateTex : public SVRenderCmd {
    public:
        SVRCmdCreateTex(SVTexturePtr _texture);
        
        ~SVRCmdCreateTex();
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        SVTexturePtr m_texture;
    };

    
    //创建R-fbo
    class SVRCmdCreateTarget : public SVRenderCmd {
    public:
        SVRCmdCreateTarget(SVRTargetPtr _target);
        
        ~SVRCmdCreateTarget();
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        SVRTargetPtr m_rtarget;
    };



}//!namespace sv

//
#endif //SV_RENDERCMD_RES_H
