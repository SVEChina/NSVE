//
// IMIRenderMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERMGR_H
#define IMI_RENDERMGR_H

#include "IMIRenderDeclare.h"
#include "../base/IMIPreDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "../base/IMIGBase.h"
#include "../base/IMIMap.h"
#include "../base/IMIMat4.h"
#include <vector>

namespace imi {
    
    /*
     负责构建渲染器数据用的
     1.包含材质排序
     2.渲染指令的推入
     */

    class IMIRenderMgr : public IMIGBaseEx {
    public:
        IMIRenderMgr(IMIInstPtr _app);
        
        ~IMIRenderMgr();
        
        void init();
        
        void destroy();
        
        void registRenderHelper(IMISysBasePtr _sys);
        
        void unRegistRenderHelper(IMISysBasePtr _sys);
        
        void clearRenderHelper();
        
        void resize(s32 _w,s32 _h);
        
        void render();
        
        void setMainRT(IMIRTargetPtr _rt);
        
        IMIRTargetPtr getMainRT();
        
        void pushRCmdCreate(IMIRenderCmdPtr _rcmd);
        
        void pushRCmdDestory(IMIRenderCmdPtr _rcmd);
        
        void pushRCmd(IMIRenderCmdPtr _rcmd,IMI_RSTREAM _rstype);
        
        void addRTarget(IMIRTargetPtr _rt,bool _pre);
        
        void removeRTarget(IMIRTargetPtr _rt);

    protected:
        void _renderCache();
        
        void _sort();
        
        void _adapt();
        
        s32 m_adaptMode;
        
        typedef std::vector<IMISysBasePtr> RENDERHELPPOOL;
        RENDERHELPPOOL m_render_help_pool;
        
        //资源创建流
        IMIRenderStreamPtr m_stream_create;
        //资源销毁流
        IMIRenderStreamPtr m_stream_destroy;
        //
        IMILockSpinPtr m_render_lock;
        //
        IMILockSpinPtr m_logic_lock;
        //渲染的RT，不负责生命周期管理
        //前向RT
        IMIArray<IMIRTargetPtr> m_preRT;
        //后向RT
        IMIArray<IMIRTargetPtr> m_afterRT;
        //主RT
        IMIRTargetPtr m_mainRT;
    };


}//!namespace imi



#endif //IMI_RENDERMGR_H
