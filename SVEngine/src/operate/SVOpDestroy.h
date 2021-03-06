//
// SVOpDestroy.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#ifndef SV_OPDESTROY_H
#define SV_OPDESTROY_H

#include "SVOpBase.h"
#include "../base/SVDatatDef.h"

namespace sv {
    class SVOpDestroyEffect : public SVOpBase {
    public:
        SVOpDestroyEffect(SVInstPtr _app, cptr8 _name);
        
    protected:
        void _process(f32 dt);
        
        SVString m_name;
    };

    //
    class SVOpDestroyGameZCMgr : public SVOpBase {
    public:
        SVOpDestroyGameZCMgr(SVInstPtr _app);
        
    protected:
        void _process(f32 dt);
    };
}//!namespace sv



#endif //SV_OPDESTROY_H
