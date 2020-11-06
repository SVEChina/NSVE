//
// IMIEventDef
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_EVENTDECLARE_H
#define IMI_EVENTDECLARE_H

#include "../base/IMIPreDeclare.h"

namespace imi {
    
    DECLARE_SHAREPTR(IMIEvent);
    //
    DECLARE_SHAREPTR(IMIvtRenderInit);
    //
    DECLARE_SHAREPTR(IMIvtRecycle);
    DECLARE_SHAREPTR(IMIPersonEvent);
    DECLARE_SHAREPTR(IMIFaceShapeEvent);
    DECLARE_SHAREPTR(IMIAnimateEvent);
    DECLARE_SHAREPTR(IMIParseEvent);
    DECLARE_SHAREPTR(IMIPickGetEvent);
    DECLARE_SHAREPTR(IMIPickGetUIEvent);
    DECLARE_SHAREPTR(IMIPickGetNothingEvent);
    DECLARE_SHAREPTR(IMIPickLoseEvent);
    DECLARE_SHAREPTR(IMIPickChangeEvent);
    DECLARE_SHAREPTR(IMIPacketUnitEndEvent);
    DECLARE_SHAREPTR(IMIPacketCloseEvent);
    DECLARE_SHAREPTR(IMIRedPacketEvent);
    //
    DECLARE_SHAREPTR(IMIEventPersonExpression);
    //
    DECLARE_SHAREPTR(IMIEventVideo);
    DECLARE_SHAREPTR(IMIEventVideoCtrl);
    DECLARE_SHAREPTR(IMIEventVideoStatus);
    DECLARE_SHAREPTR(IMIEventMixBegin);
    DECLARE_SHAREPTR(IMIEventMixEnd);
    //
    DECLARE_SHAREPTR(IMITouchEvent);
    DECLARE_SHAREPTR(IMITouchWorldEvent);
    DECLARE_SHAREPTR(IMIPickEvent);
    DECLARE_SHAREPTR(IMICameraOrenEvent);
    DECLARE_SHAREPTR(IMICameraMatrixEvent);
    DECLARE_SHAREPTR(IMIProjectMatrixEvent);
    DECLARE_SHAREPTR(IMICameraPosEvent);
    DECLARE_SHAREPTR(IMICameraDirEvent);
    DECLARE_SHAREPTR(IMIReactEvent);
    //
    DECLARE_SHAREPTR(IMIEventThread);
    //
    DECLARE_SHAREPTR(IMIvtDraw);
    
}

#endif //IMI_EVENTDECLARE_H
