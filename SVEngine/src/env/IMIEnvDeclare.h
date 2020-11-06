//
// IMIEnvDeclare.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_ENVDECLARE_H
#define IMI_ENVDECLARE_H

#include "../base/IMIDef.h"
#include "../base/IMIPreDeclare.h"

namespace imi {

    //环境
    DECLARE_SHAREPTR(IMICtxBase);

#ifdef IMI_IOS
    DECLARE_SHAREPTR(IMICtxIOSGLES);
    DECLARE_SHAREPTR(IMICtxIOSMetal);
#endif
        
#ifdef IMI_ANDROID
    DECLARE_SHAREPTR(IMIContextAndriod);
    DECLARE_SHAREPTR(IMIEGLContext);
#endif
        
#ifdef IMI_OSX
    DECLARE_SHAREPTR(IMICtxOSXGL);
    DECLARE_SHAREPTR(IMICtxOSXMetal);
#endif

}//!namespace imi

#endif //IMI_ENVDECLARE_H
