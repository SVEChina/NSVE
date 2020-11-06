//
// IMIModify.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MODIFY_H
#define IMI_MODIFY_H

#include "IMIGBase.h"

namespace imi {
    
    class IMIModify : public IMIGBaseEx {
    public:
        IMIModify(IMIInstPtr _app);
        
        ~IMIModify();
        
        void exec(IMIObjectPtr _obj);
    };
    
}//!namespace imi


#endif //IMI_MODIFY_H
