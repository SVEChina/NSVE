//
// IMIModuleSys.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MODULESYS_H
#define IMI_MODULESYS_H

#include "../basesys/IMISysBase.h"
#include "../base/IMIMap.h"

namespace imi{
    
    class IMIModuleBase;
    
    class IMIModuleSys : public IMISysBase {
    public:
        IMIModuleSys(IMIInstPtr _app);
        
        ~IMIModuleSys();
        
        void init();
        
        void destroy();
        
        void update(f32 _dt);
        
        void regist(IMIModuleBasePtr _module,cptr8 _name);
        
        void unregist(cptr8 _name);
        
        bool hasRegist(cptr8 _name);
        
        IMIModuleBasePtr getModule(cptr8 _name);
        
        bool openModule(cptr8 _name);
        
        bool closeModule(cptr8 _name);

    protected:
        typedef IMIMap<IMIString,IMIModuleBasePtr> MODULEPOOL;
        
        MODULEPOOL m_modulePool;
        
        IMILockPtr m_moduleLock;
    };
    
}//!namespace imi





#endif //IMI_MODULESYS_H
