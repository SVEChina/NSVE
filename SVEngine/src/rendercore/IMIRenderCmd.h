//
// IMIRenderCmd.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERCMD_H
#define IMI_RENDERCMD_H

#include "IMIRenderDef.h"
#include "IMIRenderDeclare.h"
#include "../base/IMIPreDeclare.h"
#include "../basesys/IMILogicDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../base/IMIObject.h"
#include "../base/IMIMat4.h"

namespace imi {
    
    //渲染命令基类
    class IMIRenderCmd : public IMIObject {
    public:
        IMIRenderCmd();
        
        ~IMIRenderCmd();
        
        virtual bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
        IMIString mTag;
    };
    
    //普通渲染命令
    class IMIRCmdNor : public IMIRenderCmd {
    public:
        IMIRCmdNor();
        
        ~IMIRCmdNor();
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
        void setMesh(IMIRenderMeshPtr _mesh);
        
        void setMaterial(IMIMtlCorePtr _material);
        
        void setSurface(IMISurfacePtr _surface);
        
    protected:
        IMIRenderMeshPtr m_pMesh;
        IMIMtlCorePtr m_pMtl;
        IMISurfacePtr m_pSurface;
    };

    //多批次渲染命令
    class IMIRCmdPass : public IMIRCmdNor {
    public:
        IMIRCmdPass();
        
        ~IMIRCmdPass();

        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
        //设置目标
        void setSwapTarget(IMI_TEXIN _aim);
        
        //设置辅助目标
        void setUseTarget(IMI_TEXIN _aim);
        
    protected:
        IMI_TEXIN m_aim_swap;
        IMI_TEXIN m_aim_use;
    };

    
    //FBO绑定(推送FBO)
    class IMIRCmdTargetResize : public IMIRenderCmd {
    public:
        IMIRCmdTargetResize(IMIRFboPtr _fbo,s32 _w,s32 _h);
        
        ~IMIRCmdTargetResize();
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        IMIRFboPtr m_fbo;
        s32 m_width;
        s32 m_height;
    };

    //
    class IMIRCmdTransGPU : public IMIRenderCmd {
    public:
        IMIRCmdTransGPU(IMITransPtr _trans);
        
        ~IMIRCmdTransGPU();
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        IMITransPtr m_trans;
    };


    //适配命令
    class IMIRCmdAdapt : public IMIRenderCmd {
    public:
        IMIRCmdAdapt();
        
        ~IMIRCmdAdapt();
        
        void setWinSize(s32 _w,s32 _h);
        
        bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        s32 m_winWidth;
        
        s32 m_winHeight;
    };


}//!namespace imi

//
#endif //IMI_RENDERCMD_H
