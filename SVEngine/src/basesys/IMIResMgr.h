//
// IMIResMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RESMGR_H
#define IMI_RESMGR_H

#include "../base/IMIDef.h"
#include "IMISysBase.h"
#include "../rendercore/IMIRenderDeclare.h"

namespace imi {
    
    /*
     资源管理
     */

    class IMIResMgr : public IMISysBase {
    public:
        IMIResMgr(IMIInstPtr _app);
        
        virtual ~IMIResMgr();
        
        void init();
        
        void destroy();
        
        void renderCache();
        
        //公共数据部分
        IMIComDataPtr m_common_data;
        
        //shader部分
        IMIShaderMgrPtr m_shader_mgr;
        
        //纹理部分
        IMITexMgrPtr m_tex_mgr;
        
        IMIRTargetMgrPtr m_target_mgr;
        
    public:
        //处理消息
        static void procSysEvent(IMIObjectPtr _caller,IMIEventPtr _event);
        
    };
    
}//!namespace imi


#endif //IMI_RESMGR_H
