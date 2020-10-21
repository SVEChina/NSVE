//
// SVFilterLib.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FILTERLIB_H
#define SV_FILTERLIB_H

#include "../base/SVGBase.h"
#include "SVMtlDef.h"

namespace sv {
    
    /*引擎提供的默认滤镜库*/

    //特定滤镜，不允许更换材质
    //公共滤镜，可以替换材质
    
    LUA_REG_DECLARE(SVFilterLib);

    class SVFilterLib : public SVGBaseEx {
    public:        
        static SVFilterBasePtr openFilter(SVInstPtr _app,FTTYPE _name,SV_TEXIN _texin = E_TEX_FLITER );
        
        static bool closeFilter(SVInstPtr _app,FTTYPE _name);
        
        static SVFilterBasePtr getFilter(SVInstPtr _app,FTTYPE _name);
        
        static void openGOF(SVInstPtr _app,SV_TEXIN _target);
        
        static void clostGOF(SVInstPtr _app);
        
        //美白
        static void openBeauty(SVInstPtr _app,SV_TEXIN _target);
        
        static void clostBeauty(SVInstPtr _app);
        
        //磨皮等接口
    };

}//!namespace sv


#endif //SV_FILTERLIB_H
