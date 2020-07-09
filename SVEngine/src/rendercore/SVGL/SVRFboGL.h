//
// SVRTGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RFBO_GL_H
#define SV_RFBO_GL_H

#include "../SVRFbo.h"

namespace sv {
    
    /*
     gl
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRFboGL  : public SVRFbo {
    public:
        SVRFboGL(SVInstPtr _app);
        
        ~SVRFboGL();
        
    protected:
        void _preRender(SVRendererPtr _renderer);
        
        void _render(SVRendererPtr _renderer);
        
        void _afterRender(SVRendererPtr _renderer);
    };

    
}//!namespace sv



#endif //SV_RFBO_GL_H
