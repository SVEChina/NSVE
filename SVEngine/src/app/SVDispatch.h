//
// SVInst.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_DISPATCH_H
#define SV_DISPATCH_H

#include "../base/SVIDPool.h"
#include "../rendercore/SVRenderDeclare.h"
#include "SVGlobalMgr.h"
#include "SVGlobalParam.h"

namespace sv {
    
    /*
     分发 投递器
     */

    class SVDispatch : public SVObject {
    public:
        //投递shader create
        static void dispatchShaderCreate(SVInstPtr _app,SVRShaderPtr _shader);
        
        //投递mesh create
        static void dispatchMeshCreate(SVInstPtr _app,SVRMeshPtr _mesh);
 
        //投递texture create
        static void dispatchTextureCreate(SVInstPtr _app,SVRTexPtr _tex);
        
       
    };
    
}//!namespace sv



#endif //SV_DISPATCH_H
