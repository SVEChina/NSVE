//
// IMIBasicSys.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BASICSYS_H
#define IMI_BASICSYS_H

#include "IMISysBase.h"

namespace imi{
    
    class IMIBasicSys : public IMISysBase {
    public:
        IMIBasicSys(IMIInstPtr _app);
        
        ~IMIBasicSys();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
        void output();
        
        void loadDefaultFMFont();
        
        //回收模块
        IMIRecycleProcessPtr getRecycleModule();
        
        //拾取模块
        IMIPickProcessPtr getPickModule();
        
        //字体模块
        IMIFontProcessPtr getFontModule();
        
    protected:
        IMIRecycleProcessPtr m_pRecycleModule;
        
        IMIPickProcessPtr m_picker;

        IMIFontProcessPtr m_fonter;
    };

}//!namespace imi


#endif //IMI_BASICSYS_H
