//
// SVRTargetMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTARGETMETAL_H
#define SV_RENDERTARGETMETAL_H

#include "../SVRTarget.h"

namespace sv {
    
    /*
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRTargetMetal : public SVGBaseEx {
    public:
        SVRTargetMetal(SVInstPtr _app);
        
        ~SVRTargetMetal();

    protected:
        void _preRender();
        
        void _render();
        
        void _afterRender();
    };

    
}//!namespace sv



#endif //SV_RENDERTARGET_H
