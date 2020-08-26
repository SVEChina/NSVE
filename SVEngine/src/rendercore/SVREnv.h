//
// SVREnv.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENV_H
#define SV_RENV_H

#include "../base/SVGBase.h"
#include "../base/SVPreDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../core/SVVertDef.h"

/*
 渲染环境，外部对接的那种
*/

namespace sv {
    
    class SVREnv: public SVGBaseEx{
    public:
        SVREnv(SVInstPtr _app);

        virtual ~SVREnv();

//        virtual void create(SVRendererPtr _renderer){}
//
//        virtual void destroy(SVRendererPtr _renderer){}
//
//        virtual bool active(SVRendererPtr _render){ return false; }
//
//        virtual void submitSurface(SVSurfacePtr _surface){}
    };
        
}//!namespace sv


#endif /* SV_RENV_H */
