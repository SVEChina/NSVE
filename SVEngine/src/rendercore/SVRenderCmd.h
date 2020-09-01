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
#include "../base/SVPreDeclare.h"
#include "../basesys/SVLogicDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../base/SVObject.h"
#include "../base/SVMat4.h"

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
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        void setMesh(SVRenderMeshPtr _mesh);
        
        void setMaterial(SVMtlCorePtr _material);
        
        void setSurface(SVSurfacePtr _surface);
        
    protected:
        SVRenderMeshPtr m_pMesh;
        SVMtlCorePtr m_pMtl;
        SVSurfacePtr m_pSurface;
    };

    //多批次渲染命令
    class SVRCmdPass : public SVRCmdNor {
    public:
        SVRCmdPass();
        
        ~SVRCmdPass();

        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        //设置目标
        void setTarget(SV_TEXIN _aim);
        
        //设置辅助目标
        void setHelpTarget(SV_TEXIN _aim);
        
    protected:
        SV_TEXIN m_aim;
        SV_TEXIN m_aim_help;
    };

    
    //FBO绑定(推送FBO)
    class SVRCmdTargetResize : public SVRenderCmd {
    public:
        SVRCmdTargetResize(SVRFboPtr _fbo,s32 _w,s32 _h);
        
        ~SVRCmdTargetResize();
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
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
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        SVTransPtr m_trans;
    };


    //适配命令
    class SVRCmdAdapt : public SVRenderCmd {
    public:
        SVRCmdAdapt();
        
        ~SVRCmdAdapt();
        
        void setWinSize(s32 _w,s32 _h);
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        s32 m_winWidth;
        
        s32 m_winHeight;
    };


}//!namespace sv

//
#endif //SV_RENDERCMD_H
