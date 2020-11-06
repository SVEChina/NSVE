//
// IMIRenderCmdGeo.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERCMD_GEO_H
#define IMI_RENDERCMD_GEO_H


#include "IMIRenderCmd.h"
#include "../base/IMIBounds.h"
#include "../base/IMIRect.h"
#include "../base/IMIPreDeclare.h"

namespace imi {
    
    //线绘制
    class IMIRenderCmdGeo : public IMIRenderCmd {
    public:
        IMIRenderCmdGeo();
        
        ~IMIRenderCmdGeo();
        
        virtual bool render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
    protected:
        virtual void _render();
        
        IMIMtlCorePtr m_pMtl;
    };
    
    //线绘制
    class IMIRCmdLine : public IMIRenderCmdGeo {
    public:
        void setLine(FVec3& _start,FVec3& _end);
        
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
        FVec3 m_start;
        FVec3 m_end;
    };
    
    //矩形绘制
    class IMIRCmdRect : public IMIRenderCmdGeo {
    public:
        void setRect(IMIRect& _rect);
        
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
        IMIRect m_rect;
    };
    
    class IMIRCmdRectSolid : public IMIRCmdRect {
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
    };
    
    //曲线绘制
    class IMIRCmdCurve : public IMIRenderCmdGeo {
    public:
        
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
    
    public:
        IMIArray<FVec3> m_ptList;
    };
    
    //原型绘制
    class IMIRCmdCircle : public IMIRenderCmdGeo {
    public:
        
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        FVec3 m_center;
        f32 m_radius;
        f32 m_angle;
    };
    
    //圆固体绘制（实体）
    class IMIRCmdCircleSolid : public IMIRenderCmdGeo {
    public:
        
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        FVec3 m_center;
        f32 m_radius;
        f32 m_angle;
    };

    //AABB绘制
    class IMIRCmdAABB : public IMIRenderCmdGeo {
    public:
        void setAABB(IMIBoundBox& _aabb);
        
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
        IMIBoundBox m_aabb;
    };

    //AABB绘制(实体)
    class IMIRCmdAABBSolid : public IMIRCmdAABB {
    protected:
        virtual void _render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
    };

    
}//!namespace imi




#endif //IMI_RENDERCMD_GEO_H
