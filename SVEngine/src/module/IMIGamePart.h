//
// IMIGamePart.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GAMEPART_H
#define IMI_GAMEPART_H

#include "IMIModuleDef.h"
#include "../event/IMIEventProc.h"
#include "../node/IMINodeDeclare.h"

namespace imi{
    
    class IMIGamePart : public IMIGBaseEx {
    public:
        IMIGamePart(IMIInstPtr _app);
        
        virtual ~IMIGamePart();
        
        virtual void init();
        
        virtual void destroy();
        
        virtual void reset();
        
        virtual void enter();
        
        virtual void exit();
        
        virtual void update(f32 _dt);
        
        virtual bool isEnd();
        
    protected:
        
    };
    
}//!namespace imi



#endif //IMI_GAMEPART_H
