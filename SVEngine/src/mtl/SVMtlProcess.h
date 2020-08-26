//
// SVMtlProcess.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MTLPROCESS_H
#define SV_MTLPROCESS_H

#include "../base/SVGBase.h"
#include "SVMtlDef.h"
#include "SVMtlDeclare.h"
#include "../base/SVObject.h"
#include "../third/rapidjson/rapidjson.h"
#include "../third/rapidjson/document.h"

#include <map>
#include <vector>
#include <string>

namespace sv {
    
    /*材质处理*/

    class SVMtlProcess : public SVGBaseEx {
    public:
        SVMtlProcess(SVInstPtr _app);
        
        ~SVMtlProcess();
        
        void init();
        
        void destroy();
        
        void update(f32 _dt);
        
    };

}//!namespace sv


#endif //SV_MTLPROCESS_H
