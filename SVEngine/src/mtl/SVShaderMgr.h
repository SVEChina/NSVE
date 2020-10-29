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

        SVShaderPtr getShader(cptr8 _name,s32 _sdef = 0);
        
        void loadSDSP(cptr8 _sdsp);
        
        void loadSDSP(cptr8 _sdsp,std::vector<SVString>& _defs);
        
        s32 getDefValue(cptr8 _defname);
        
        s32 getDefCode(std::vector<SVString>& _defs);
        
    private:
        void _loadShaderDef();
        
        void _loadAllShader();
        
        void _clearAllShader();
        
    protected:
        //普通shader池子
        typedef std::map<SVString,SVShaderPtr> SHADERPOOL;
        SHADERPOOL m_shaderMap;
        
        typedef std::map<SVString,s32> DEFTBL;
        DEFTBL m_deftbl;
        
        SVString m_language;
    };
    
}//!namespace sv


#endif //SV_SHADERMGR_H
