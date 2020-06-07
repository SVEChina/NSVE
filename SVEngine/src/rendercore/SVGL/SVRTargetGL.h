//
// SVRTGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTARGET_GL_H
#define SV_RENDERTARGET_GL_H

#include "../SVRTarget.h"

namespace sv {
    
    /*
     gl
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRTargetGL  : public SVRTarget {
    public:
        SVRTargetGL(SVInstPtr _app);
        
        ~SVRTargetGL();
        
    protected:
        void _preRender(SVRendererPtr _renderer);
        
        void _render(SVRendererPtr _renderer);
        
        void _afterRender(SVRendererPtr _renderer);
    };

    
}//!namespace sv



#endif //SV_RENDERTARGET_GL_H
