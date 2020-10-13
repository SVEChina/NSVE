//
// SVShaderMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SHADERMGR_H
#define SV_SHADERMGR_H

#include "../base/SVDef.h"
#include "../basesys/SVSysBase.h"
#include <map>

namespace sv {

    /*
     尽量采用数组的方式
     */

    class SVShaderMgr : public SVGBaseEx {
    public:
        SVShaderMgr(SVInstPtr _app);
        
        virtual ~SVShaderMgr();
        
        void init();
        
        void destroy();
        
        void loadDefault();

        SVShaderPtr getShader(cptr8 _name);
        
        void loadSDSP(cptr8 _sdsp,cptr8 _language);
        
    private:
        void _loadAllShader();
        
        void _clearAllShader();
        
    protected:
        typedef std::map<SVString,SVShaderPtr> SHADERPOOL;
        SHADERPOOL m_shaderMap;
    };
    
}//!namespace sv


#endif //SV_SHADERMGR_H
