//
// IMISysBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SYSBASE_H
#define IMI_SYSBASE_H

#include "../event/IMIEventProc.h"
#include "../node/IMINodeDeclare.h"

namespace imi {
    
    class IMISysBase : public IMIEventProc {
    public:
        IMISysBase(IMIInstPtr _app);
        
        ~IMISysBase();
        
        virtual void renderCache() {}
        
    protected:
        s32 m_subsysType;
    };
    
}//!namespace imi


#endif //IMI_SYSBASE_H
