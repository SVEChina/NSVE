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
        
        virtual void create(SVRendererPtr _renderer) {}
        
        virtual void destroy(SVRendererPtr _renderer) {}
        
        virtual s32 process(SVRendererPtr _renderer) { return -1; }
        
        //
        SVObjectPtr m_logic_obj;
        bool m_exist;
    };
        
}//!namespace sv



//
#endif //SV_ROBJBASE_H
