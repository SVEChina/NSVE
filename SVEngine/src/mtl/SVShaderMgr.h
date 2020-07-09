//
// SVShaderMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SHADERMGR_H
#define SV_SHADERMGR_H

#include "../base/SVDef.h"
#include "../base/SVObject.h"
#include "../base/SVMap.h"
#include "../basesys/SVSysBase.h"
#include "../rendercore/SVRShader.h"

namespace sv {
    /*
     尽量采用数组的方式
     */
    class SVShaderMgr : public SVSysBase {
    public:
        SVShaderMgr(SVInstPtr _app);
        
        ~SVShaderMgr();
        
        void init();
        
        void destroy();

        SVRShaderPtr getShader(cptr8 _name);
        
    private:
        void _loadAllShader();
        
        void _clearAllShader();
        
    protected:
        typedef SVMap<SVString,SVRShaderPtr> SHADERPOOL;
        SHADERPOOL ShaderMap;
    };
    
}//!namespace sv


#endif //SV_SHADERMGR_H
