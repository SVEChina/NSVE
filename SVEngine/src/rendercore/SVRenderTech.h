//
// SVRenderTech.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTECH_H
#define SV_RENDERTECH_H

#include "../base/SVGBase.h"

namespace sv {

    /*
     render tech
     */

    class SVRenderTech : public SVGBaseEx {
    public:
        SVRenderTech(SVInstPtr _app);
        
        ~SVRenderTech();
        
        virtual void render();
        
    };


}//!namespace sv


#endif //SV_RENDERTECH_H
