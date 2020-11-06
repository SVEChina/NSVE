//
// IMILogicDeclare.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_LOGICDECLARE_H
#define IMI_LOGICDECLARE_H

#include "../base/IMIPreDeclare.h"

namespace imi {
    
    DECLARE_SHAREPTR(IMITrans);
    DECLARE_SHAREPTR(IMITransCPU);
    DECLARE_SHAREPTR(IMITransGPU);
    //
    DECLARE_SHAREPTR(StreamInCore);
    //

    DECLARE_SHAREPTR(IMIOutMission);
    DECLARE_SHAREPTR(IMIOutMissionNor);

}//!namespace imi

#endif //IMI_LOGICDECLARE_H
