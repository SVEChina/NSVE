//
// IMIRRes.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_ROBJBASE_H
#define IMI_ROBJBASE_H

#include "../base/IMIGBase.h"
#include "IMIRenderDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "IMIRenderDef.h"

//渲染资源对象

namespace imi {
        
    class IMIRRes: public IMIGBaseEx {
    public:
        IMIRRes(IMIInstPtr _app);
        
        virtual ~IMIRRes();
        
        virtual void load(IMIRendererPtr _renderer) {}

        virtual void unload() {}
        
        virtual s32 process(IMIRendererPtr _renderer) { return -1; }
        
        bool m_exist;
        s32 m_pool_id;
    };
        
}//!namespace imi



//
#endif //IMI_ROBJBASE_H
