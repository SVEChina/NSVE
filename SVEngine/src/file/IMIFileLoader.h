//
// IMIFileLoader.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FILELOADER_H
#define IMI_FILELOADER_H

#include "../base/IMIObject.h"
#include "../base/IMIGBase.h"
#include "../mtl/IMIMtlDeclare.h"

namespace imi {
    
    class IMIFileLoader : public IMIGBaseEx {
    public:
        IMIFileLoader(IMIInstPtr _app);

        virtual ~IMIFileLoader();
    };

}//!namespace imi



#endif //IMI_FILELOADER_H
