//
// SVResMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RESMGR_H
#define SV_RESMGR_H

#include "../base/SVDef.h"
#include "SVSysBase.h"
#include "../rendercore/SVRenderDeclare.h"

namespace sv {
    
    /*
     资源管理
     */

    class SVResMgr : public SVSysBase {
    public:
        SVResMgr(SVInstPtr _app);
        
        virtual ~SVResMgr();
        
        void init();
        
        void destroy();
        
        void renderCache();
        
        //公共数据部分
        SVComDataPtr m_common_data;
        
        //shader部分
        SVShaderMgrPtr m_shader_mgr;
        
        //纹理部分
        SVTexMgrPtr m_tex_mgr;
        
        SVRTargetMgrPtr m_target_mgr;
        
    public:
        //处理消息
        static void procSysEvent(SVObjectPtr _caller,SVEventPtr _event);
        
    };
    
}//!namespace sv


#endif //SV_RESMGR_H
