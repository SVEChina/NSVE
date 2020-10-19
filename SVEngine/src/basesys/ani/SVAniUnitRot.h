//
// SVAniUnit.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ANIUNIT_ROT_H
#define SV_ANIUNIT_ROT_H

#include "SVAniUnit.h"

namespace sv {

    class SVAniUnitRot  : public SVAniUnit {
    public:
        SVAniUnitRot(SVInstPtr _app);
        
        virtual ~SVAniUnitRot();
        
        virtual void init();

        virtual void destroy();

        virtual void update(f32 _dt,SVNodePtr _node);
    };
    
}//!namespace sv



#endif //SV_ANIUNIT_ROT_H
