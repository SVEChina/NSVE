//
// SVRTarget.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTARGET_H
#define SV_RENDERTARGET_H

#include "../base/SVGbase.h"
#include "SVRenderDeclare.h"

namespace sv {
    
    /*
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRTarget : public SVGBaseEx {
    public:
        SVRTarget(SVInstPtr _app);
        
        ~SVRTarget();
        
        void render(SVRendererPtr _renderer);
        
    protected:
        virtual void _preRender(SVRendererPtr _renderer);
        
        virtual void _render(SVRendererPtr _renderer);
        
        virtual void _afterRender(SVRendererPtr _renderer);
        
    public:
        s32 m_order;
    };

    
}//!namespace sv



#endif //SV_RENDERTARGET_H
