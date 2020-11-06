//
// IMIOutMission.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OUTMISSION_H
#define IMI_OUTMISSION_H

#include "../../event/IMIEventProc.h"
#include "../IMILogicDeclare.h"

//输出任务

namespace imi{
    
    enum MISSIONSTATE{
        E_MS_RUN = 0,
        E_MS_END
    };
    
    class IMIOutMission : public IMIEventProc {
    public:
        IMIOutMission(IMIInstPtr _app,cptr8 _name);
        
        ~IMIOutMission();
        
        virtual void output();
        
        virtual bool isEnd();
        
        void sendEnd();
        
        void setStateCallback(cb_outstream_state _cb) { m_pOutStreamStateCB = _cb; }
        
        cptr8 getMissionName();
        
    protected:
        cb_outstream_state m_pOutStreamStateCB;
        IMIString m_name;
    };
    
}//!namespace imi





#endif //IMI_OUTMISSION_H
