//
// SVAniUnit.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ANIUNIT_H
#define SV_ANIUNIT_H

#include "../../event/SVEventProc.h"
#include "../../work/SVWorkDeclare.h"
#include "../../node/SVNodeDeclare.h"

namespace sv {
    
    /*相机节点
     不是节点*/

    class SVAniUnit : public SVEventProc {
    public:
        SVAniUnit(SVInstPtr _app);
        
        virtual ~SVAniUnit();
        
        virtual void init();

        virtual void destroy();
        
        virtual void bind(SVNodePtr _node){}

        virtual void update(f32 _dt,SVNodePtr _node);
    };
    
}//!namespace sv



#endif //SV_ANIUNIT_H
