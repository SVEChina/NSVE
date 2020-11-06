//
// IMIOutMissionNor.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OUTMISSION_NOR_H
#define IMI_OUTMISSION_NOR_H

#include "IMIOutMission.h"

//输出任务

namespace imi{
    
    class IMIOutMissionNor : public IMIOutMission {
    public:
        IMIOutMissionNor(IMIInstPtr _app,cptr8 _name);
        
        virtual ~IMIOutMissionNor();
        
        void output();
        
        bool isEnd();
        
        void setEnd();
        
    protected:
        bool m_end;
    };
    
}//!namespace imi





#endif //IMI_OUTMISSION_NOR_H
