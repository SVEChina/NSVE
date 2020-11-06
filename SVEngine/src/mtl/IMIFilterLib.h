//
// IMIFilterLib.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FILTERLIB_H
#define IMI_FILTERLIB_H

#include "../base/IMIGBase.h"
#include "IMIMtlDef.h"

namespace imi {
    
    /*引擎提供的默认滤镜库*/

    //特定滤镜，不允许更换材质
    //公共滤镜，可以替换材质
    
    LUA_REG_DECLARE(IMIFilterLib);

    class IMIFilterLib : public IMIGBaseEx {
    public:        
        static IMIFilterBasePtr openFilter(IMIInstPtr _app,FTTYPE _name,IMI_TEXIN _texin = E_TEX_FLITER );
        
        static bool closeFilter(IMIInstPtr _app,FTTYPE _name);
        
        static IMIFilterBasePtr getFilter(IMIInstPtr _app,FTTYPE _name);
        
        static void openGOF(IMIInstPtr _app,IMI_TEXIN _target);
        
        static void clostGOF(IMIInstPtr _app);
        
        //美白
        static void openBeauty(IMIInstPtr _app,IMI_TEXIN _target);
        
        static void clostBeauty(IMIInstPtr _app);
        
        //磨皮等接口
    };

}//!namespace imi


#endif //IMI_FILTERLIB_H
