//
// IMIPersonModule.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PERSONMODULE_H
#define IMI_PERSONMODULE_H

#include "../event/IMIEventProc.h"
namespace imi {
    
    class IMIPersonModule : public IMIEventProc {
    public:
        IMIPersonModule(IMIInstPtr _app);
        
        ~IMIPersonModule();
        
        void initModule();
        
        void destoryModule();
        
        IMIPersonPtr getPerson(s32 _personId);
        
    protected:
        IMIPersonPtr m_persons[IMI_SUPPORT_MAX_PERSON_NUM];
    };

}//!namespace imi



//
#endif //IMI_PERSONMODULE_H
