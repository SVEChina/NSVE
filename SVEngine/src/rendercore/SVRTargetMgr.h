//
// SVShaderMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TARGETMGR_H
#define SV_TARGETMGR_H

#include "../base/SVDef.h"
#include "../basesys/SVSysBase.h"
#include <map>

namespace sv {

    class SVRTargetMgr : public SVGBaseEx {
    public:
        SVRTargetMgr(SVInstPtr _app);
        
        virtual ~SVRTargetMgr();
        
        void init();
        
        void destroy();
        
        //创建默认的target
        void loadDefault();
        
    public:
        
    };
    
}//!namespace sv


#endif //SV_TARGETMGR_H
