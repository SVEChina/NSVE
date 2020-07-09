//
// SVRTarget.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDER_TARGET_H
#define SV_RENDER_TARGET_H

#include "../base/SVGBase.h"
#include "SVRenderDeclare.h"

namespace sv {
    
    /*
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRTarget : public SVGBaseEx {
    public:
        SVRTarget(SVInstPtr _app);
        
        ~SVRTarget();
        
        void setFbo(SVRFboPtr _fbo) {
            m_fbo = _fbo;
        }
        
        void render(SVRendererPtr _renderer);
        
    protected:
        virtual void _preRender(SVRendererPtr _renderer);
        
        virtual void _render(SVRendererPtr _renderer);
        
        virtual void _afterRender(SVRendererPtr _renderer);
        
        SVRFboPtr m_fbo;
    };

    
}//!namespace sv



#endif //SV_RENDER_TARGET_H
