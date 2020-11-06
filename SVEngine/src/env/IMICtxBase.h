//
// IMICtxBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_CONTEXT_BASE_H
#define IMI_CONTEXT_BASE_H

#include "../base/IMIGBase.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "IMIEnvDeclare.h"

namespace imi {
    
    /*
     环境不同，搭载的渲染器自然也不同，所以不必要显示创建渲染器
     */

    class IMICtxBase: public IMIGBaseEx {
    public:
        IMICtxBase(IMIInstPtr _app);
        
        ~IMICtxBase();
        
        virtual void destroy() {}
        
        virtual void resize(s32 _w,s32 _h){}
        
        virtual bool activeContext(IMIRendererPtr _renderer);
        
        virtual bool swap(IMIRendererPtr _renderer);
    };
    
}//!namespace imi


#endif //IMI_CONTEXT_BASE_H
