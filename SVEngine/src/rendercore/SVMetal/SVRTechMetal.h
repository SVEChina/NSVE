//
// SVRTechMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTECH_METAL_H
#define SV_RENDERTECH_METAL_H

#include "../SVRTech.h"
#include "SVRenderDeclare.h"

namespace sv {

    /*
     render tech
     */

    class SVRTechMetal : public SVRTech {
    public:
        SVRTechMetal(SVInstPtr _app);
        
        ~SVRTechMetal();
        
        virtual void render(SVRendererPtr _renderer);
        
    protected:
        
    };


}//!namespace sv


#endif //SV_RENDERTECH_METAL_H
