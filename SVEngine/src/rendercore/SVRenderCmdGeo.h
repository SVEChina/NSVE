//
// SVRenderCmdGeo.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERCMD_GEO_H
#define SV_RENDERCMD_GEO_H


#include "SVRenderCmd.h"
#include "../base/SVBounds.h"
#include "../base/SVRect.h"
#include "../base/SVPreDeclare.h"

namespace sv {
    
    //线绘制
    class SVRenderCmdGeo : public SVRenderCmd {
    public:
        SVRenderCmdGeo();
        
        ~SVRenderCmdGeo();
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    protected:
        virtual void _render();
        
        SVMtlCorePtr m_pMtl;
    };
    
    //线绘制
    class SVRCmdLine : public SVRenderCmdGeo {
    public:
        void setLine(FVec3& _start,FVec3& _end);
        
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        FVec3 m_start;
        FVec3 m_end;
    };
    
    //矩形绘制
    class SVRCmdRect : public SVRenderCmdGeo {
    public:
        void setRect(SVRect& _rect);
        
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        SVRect m_rect;
    };
    
    class SVRCmdRectSolid : public SVRCmdRect {
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
    };
    
    //曲线绘制
    class SVRCmdCurve : public SVRenderCmdGeo {
    public:
        
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
    
    public:
        SVArray<FVec3> m_ptList;
    };
    
    //原型绘制
    class SVRCmdCircle : public SVRenderCmdGeo {
    public:
        
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
        FVec3 m_center;
        f32 m_radius;
        f32 m_angle;
    };
    
    //圆固体绘制（实体）
    class SVRCmdCircleSolid : public SVRenderCmdGeo {
    public:
        
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
        FVec3 m_center;
        f32 m_radius;
        f32 m_angle;
    };

    //AABB绘制
    class SVRCmdAABB : public SVRenderCmdGeo {
    public:
        void setAABB(SVBoundBox& _aabb);
        
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        SVBoundBox m_aabb;
    };

    //AABB绘制(实体)
    class SVRCmdAABBSolid : public SVRCmdAABB {
    protected:
        virtual void _render(SVRendererPtr _renderer,SVRTargetPtr _target);
    };

    
}//!namespace sv




#endif //SV_RENDERCMD_GEO_H
