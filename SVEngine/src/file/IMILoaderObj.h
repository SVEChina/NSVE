//
// IMILoaderObj.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OBJLOADER_H
#define IMI_OBJLOADER_H

#include "IMIFileLoader.h"

namespace imi {
    
    class IMILoaderObj : public IMIFileLoader {
    public:
        IMILoaderObj(IMIInstPtr _app);
        
        IMIModelPtr loadModel(cptr8 _fname);
    };
    
}//!namespace imi



#endif //IMI_OBJLOADER_H
