//
// SVRenderPath.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERPATH_H
#define SV_RENDERPATH_H

#include "../basesys/SVSysBase.h"
#include "SVRenderDeclare.h"

namespace sv {
    
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
    class SVRenderPath : public SVSysBase {
    public:
        SVRenderPath(SVInstPtr _app);
        
        ~SVRenderPath();
        
        void openPreZ();
        
        void closePreZ();
        
        bool m_prez;
        
    public:
        
        //
        SVRTargetPtr m_target_preZ;
        //处理消息
        static void procSysEvent(SVObjectPtr _caller,SVEventPtr _event);
    };

}//!namespace sv



#endif //SV_RENDERPATH_H
