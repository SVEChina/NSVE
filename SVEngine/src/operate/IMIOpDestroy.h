//
// IMIOpDestroy.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#ifndef IMI_OPDESTROY_H
#define IMI_OPDESTROY_H

#include "IMIOpBase.h"
#include "../base/IMIDatatDef.h"

namespace imi {
    class IMIOpDestroyEffect : public IMIOpBase {
    public:
        IMIOpDestroyEffect(IMIInstPtr _app, cptr8 _name);
        
    protected:
        void _process(f32 dt);
        
        IMIString m_name;
    };

    //
    class IMIOpDestroyGameZCMgr : public IMIOpBase {
    public:
        IMIOpDestroyGameZCMgr(IMIInstPtr _app);
        
    protected:
        void _process(f32 dt);
    };
}//!namespace imi



#endif //IMI_OPDESTROY_H
