//
// IMIRenderPath.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERPATH_H
#define IMI_RENDERPATH_H

#include "../basesys/IMISysBase.h"
#include "IMIRenderDeclare.h"

namespace imi {
    
    /*
     渲染路径(为进行光照计算而设计的渲染方式) 这里其实可以分为离线和在线，上层根据材质的属性，自动丢到不同的渲染路径当中
     1. forward render
     2. defer render
     3. light pre-pass
     4. tbdr
     5. forward+
     等等
     */
    /*
     由渲染路径产出指令，所以这是个逻辑概念
     */
    //不同RPath 需要设定不同的流
    class IMIRenderPath : public IMISysBase {
    public:
        IMIRenderPath(IMIInstPtr _app);
        
        ~IMIRenderPath();
        
        void openPreZ();
        
        void closePreZ();
        
        void openShadow();
        
        void closeShadow();
        
    public:
        bool m_prez;
        
        bool m_has_shadow;
        
        IMIRTargetPtr m_target_preZ;
        IMIRTargetPtr m_target_shadow;
        //处理消息
        static void procSysEvent(IMIObjectPtr _caller,IMIEventPtr _event);
    };

}//!namespace imi



#endif //IMI_RENDERPATH_H
