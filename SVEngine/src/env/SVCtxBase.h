//
// SVCtxBase.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CONTEXTBASE_H
#define SV_CONTEXTBASE_H

#include "../base/SVObject.h"
#include "../rendercore/SVRenderDeclare.h"
#include "SVEnvDeclare.h"

namespace sv {
    
    /*
     环境不同，搭载的渲染器自然也不同，所以不必要显示创建渲染器
     */

    class SVCtxBase: public SVObject {
    public:
        SVCtxBase();
        
        ~SVCtxBase();
        
        virtual void resize(s32 _w,s32 _h){}
        
        virtual bool activeContext(SVRendererPtr _renderer);
        
        virtual bool swap(SVRendererPtr _renderer);
    };
    
}//!namespace sv


#endif //SV_CONTEXTBASE_H
