//
// IMIGameBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GAMEBASE_H
#define IMI_GAMEBASE_H

#include "IMIModuleBase.h"

namespace imi{
    //
    class IMIGameBase : public IMIModuleBase {
    public:
        //游戏阶段
        enum IMIGameStage {
            E_G_STAGE_WAIT,
            E_G_STAGE_BEGIN,
            E_G_STAGE_RUN,
            E_G_STAGE_END
        };
        IMIGameBase(IMIInstPtr _app);
        
        ~IMIGameBase();
        
        virtual void init(IMIGameReadyPtr _ready,IMIGameRunPtr _run,IMIGameEndPtr _end);
        
        virtual void destroy();
        
        virtual void update(f32 _dt);
        
        virtual void open();
        
        virtual void close();
        
        virtual bool procEvent(IMIEventPtr _event);
        
    protected:
        IMIGameReadyPtr m_pGameReady;
        IMIGameRunPtr m_pGameRun;
        IMIGameEndPtr m_pGameEnd;
        IMIGameStage m_stage;
    };
}//!namespace imi





#endif //IMI_GAMEBASE_H
