//
// SVRTech.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTECH_H
#define SV_RENDERTECH_H

#include "../base/SVGBase.h"
#include "SVRenderDeclare.h"

namespace sv {

    /*
     技术是材质的集合，几种材质搞成一个技术
     render tech
     */

    class SVRTech : public SVGBaseEx {
    public:
        SVRTech(SVInstPtr _app);
        
        ~SVRTech();
        
        virtual void build(SVRendererPtr _renderer);
        
        virtual void render(SVRendererPtr _renderer);
        
    };


}//!namespace sv


#endif //SV_RENDERTECH_H
