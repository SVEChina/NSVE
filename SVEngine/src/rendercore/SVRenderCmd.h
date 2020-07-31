//
// SVRenderCmd.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERCMD_H
#define SV_RENDERCMD_H

#include "SVRenderDef.h"
#include "SVRenderDeclare.h"
#include "../base/SVObject.h"
#include "../base/SVMat4.h"
#include "../base/SVPreDeclare.h"
#include "../basesys/SVLogicDeclare.h"
#include "../mtl/SVMtlDeclare.h"

namespace sv {
    
    //渲染命令基类
    class SVRenderCmd : public SVObject {
    public:
        SVRenderCmd();
        
        ~SVRenderCmd();
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        SVString mTag;
        
    };
    
    //普通渲染命令
    class SVRCmdNor : public SVRenderCmd {
    public:
        SVRCmdNor();
        
        ~SVRCmdNor();
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        void setMesh(SVRenderMeshPtr _mesh);
        
        void setMaterial(SVMtlCorePtr _material);
        
    protected:
        SVRenderMeshPtr m_pMesh;
        SVMtlCorePtr m_pMtl;
    };
    
    //适配命令
    class SVRCmdAdapt : public SVRenderCmd {
    public:
        SVRCmdAdapt();
        
        ~SVRCmdAdapt();
        
        void setWinSize(s32 _w,s32 _h);
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        s32 m_winWidth;
        
        s32 m_winHeight;
    };
    
    //多批次渲染命令
    class SVRCmdPass : public SVRCmdNor {
    public:
        SVRCmdPass();
        
        ~SVRCmdPass();

        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        void setFbo(SVRenderTexturePtr _fbo);
        
        void setTexture(SVTexturePtr _tex);
        
    protected:
        SVRenderTexturePtr m_fbo;
        
        SVTexturePtr m_tex;
    };
    
    //多批次渲染命令集合
    class SVRCmdPassCollection : public SVRCmdNor {
    public:
        SVRCmdPassCollection();
        
        ~SVRCmdPassCollection();
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        void setFbo(SVRenderTexturePtr _fbo);
        
        void setTexture(SVTexturePtr _tex);
        
        void addMtlMesh(SVMtlCorePtr _mtl ,SVRenderMeshPtr _mesh);
        
    protected:
        SVRenderTexturePtr m_fbo;
        
        SVTexturePtr m_tex;
        
        SVArray<SVMtlCorePtr> m_MtlArray;
        SVArray<SVRenderMeshPtr> m_MeshArray;
    };
    
    //FBO绑定(推送FBO)
    class SVRCmdFboResize : public SVRenderCmd {
    public:
        SVRCmdFboResize(SVRFboPtr _fbo,s32 _w,s32 _h);
        
        ~SVRCmdFboResize();
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        SVRFboPtr m_fbo;
        s32 m_width;
        s32 m_height;
    };

    //
    class SVRCmdTransGPU : public SVRenderCmd {
    public:
        SVRCmdTransGPU(SVTransPtr _trans);
        
        ~SVRCmdTransGPU();
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        SVTransPtr m_trans;
    };

        

}//!namespace sv

//
#endif //SV_RENDERCMD_H
