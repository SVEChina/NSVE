//
// IMIAniUnit.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_ANIUNIT_H
#define IMI_ANIUNIT_H

#include "../../event/IMIEventProc.h"
#include "../../work/IMIWorkDeclare.h"
#include "../../node/IMINodeDeclare.h"

namespace imi {
    
    /*相机节点
     不是节点*/

    class IMIAniUnit : public IMIEventProc {
    public:
        IMIAniUnit(IMIInstPtr _app);
        
        virtual ~IMIAniUnit();
        
        virtual void init();

        virtual void destroy();
        
        virtual void bind(IMINodePtr _node){}

        virtual void update(f32 _dt,IMINodePtr _node);
    };
    
}//!namespace imi



#endif //IMI_ANIUNIT_H
