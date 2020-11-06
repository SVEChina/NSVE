//
// IMIWorkDeclare.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_WORKDECLARE_H
#define IMI_WORKDECLARE_H

#include "../base/IMIDef.h"
#include "../base/IMIPreDeclare.h"

namespace imi {

    DECLARE_SHAREPTR(IMILockSpin);
    DECLARE_SHAREPTR(IMICond);
    DECLARE_SHAREPTR(IMISem);
    DECLARE_SHAREPTR(IMIThread);
    DECLARE_SHAREPTR(IMIThreadGroup);
    DECLARE_SHAREPTR(IMIThreadPool);
    DECLARE_SHAREPTR(IMIMis);

}//!namespace imi

#endif //IMI_WORKDECLARE_H
