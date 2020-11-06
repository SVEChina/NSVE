//
// IMIRenderCmd.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERCMD_RES_H
#define IMI_RENDERCMD_RES_H

#include "IMIRenderCmd.h"

namespace imi {

    //关于底层资源创建喝销毁的地方

    //创建r-buffer
    class IMIRCmdCreateMesh : public IMIRenderCmd {
    public:
        IMIRCmdCreateMesh(IMIRenderMeshPtr _mesh);
        
        ~IMIRCmdCreateMesh();
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        IMIRenderMeshPtr m_rendermesh;
    };

    //创建R-shader
    class IMIRCmdCreateShader : public IMIRenderCmd {
    public:
        IMIRCmdCreateShader(IMIShaderPtr _shader);
        
        ~IMIRCmdCreateShader();
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        IMIShaderPtr m_shader;
    };

    //创建R-tex
    class IMIRCmdCreateTex : public IMIRenderCmd {
    public:
        IMIRCmdCreateTex(IMITexturePtr _texture);
        
        ~IMIRCmdCreateTex();
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        IMITexturePtr m_texture;
    };

    
    //创建R-fbo
    class IMIRCmdCreateTarget : public IMIRenderCmd {
    public:
        IMIRCmdCreateTarget(IMIRTargetPtr _target);
        
        ~IMIRCmdCreateTarget();
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        IMIRTargetPtr m_rtarget;
    };

}//!namespace imi

//
#endif //IMI_RENDERCMD_RES_H
