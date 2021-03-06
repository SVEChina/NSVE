//
// SVRRes.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ROBJBASE_H
#define SV_ROBJBASE_H

#include "../base/SVGBase.h"
#include "SVRenderDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "SVRenderDef.h"

//渲染资源对象

namespace sv {
        
    class SVRRes: public SVGBaseEx {
    public:
        SVRRes(SVInstPtr _app);
        
        virtual ~SVRRes();
        
        virtual void load(SVRendererPtr _renderer) {}

        virtual void unload() {}
        
        virtual s32 process(SVRendererPtr _renderer) { return -1; }
        
        bool m_exist;
        s32 m_pool_id;
    };
        
}//!namespace sv



//
#endif //SV_ROBJBASE_H
