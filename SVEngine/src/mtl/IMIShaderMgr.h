//
// IMIShaderMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SHADERMGR_H
#define IMI_SHADERMGR_H

#include "../base/IMIDef.h"
#include "../basesys/IMISysBase.h"
#include <map>

namespace imi {

    /*
     尽量采用数组的方式
     */

    class IMIShaderMgr : public IMIGBaseEx {
    public:
        IMIShaderMgr(IMIInstPtr _app);
        
        virtual ~IMIShaderMgr();
        
        void init();
        
        void destroy();
        
        void loadDefault();

        IMIShaderPtr getShader(cptr8 _name,s32 _sdef = 0);
        
        IMIShaderPtr loadSDSP(cptr8 _sdsp);
        
        IMIShaderPtr loadSDSP(cptr8 _sdsp,std::vector<IMIString>& _defs);
        
        s32 getDefValue(cptr8 _defname);
        
        s32 getDefCode(std::vector<IMIString>& _defs);
        
    private:
        void _loadShaderDef();
        
        void _loadAllShader();
        
        void _clearAllShader();
        
    protected:
        //普通shader池子
        typedef std::map<IMIString,IMIShaderPtr> SHADERPOOL;
        SHADERPOOL m_shaderMap;
        
        typedef std::map<IMIString,s32> DEFTBL;
        DEFTBL m_deftbl;
        
        IMIString m_language;
    };
    
}//!namespace imi


#endif //IMI_SHADERMGR_H
