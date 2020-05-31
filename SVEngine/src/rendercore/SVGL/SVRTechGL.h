//
// SVRTechMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTECH_GL_H
#define SV_RENDERTECH_GL_H

#include "../SVRTech.h"
#include "SVRenderDeclare.h"

namespace sv {

    /*
     render tech gl
     */

    class SVRTechGL : public SVRTech {
    public:
        SVRTechGL(SVInstPtr _app);
        
        ~SVRTechGL();
        
        virtual void render(SVRendererPtr _renderer);
        
    protected:
        
    };


}//!namespace sv


#endif //SV_RENDERTECH_GL_H
