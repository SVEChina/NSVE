//
// SVEventMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_EVENTMGR_H
#define SV_EVENTMGR_H

#include "../basesys/SVSysBase.h"
#include "../work/SVTdCore.h"
#include "SVEventDef.h"
#include <vector>
#include <map>

namespace sv {
    
    class SVEventMgr : public SVSysBase {
    public:
        SVEventMgr(SVInstPtr _app);
        
        ~SVEventMgr();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
        void reset();
        
        //监听某一个具体的消息
        void listenSysEvent(SVObjectPtr caller,proc_sys_event _cb);
        
        void unlistenSysEvent(SVObjectPtr caller);
        
        void clearListenSysEvent();
        
        //推送事件
        void pushEvent(SVEventPtr _event,bool _cache = false);
        
        //注册事件处理器
        bool hasRegist(SVEventProcPtr _procer);
        
        void registProcer(SVEventProcPtr _procer);
        
        void unregistProcer(SVEventProcPtr _procer);
        
    private:
        void clearAllEvent();
        
        void clearAllEventProcer();
        
        void _processEvent(SVEventPtr _event);
        
    private:
        //普通消息处理
        typedef std::vector<SVEventPtr> EVENTPOOL;
        EVENTPOOL m_exe_eventList0;     //事件队列0
        EVENTPOOL m_exe_eventList1;     //事件队列1
        
        EVENTPOOL *m_active_pool;       //当前执行的消息池
        EVENTPOOL *m_waitevent_pool;    //等待消息池
        EVENTPOOL m_cachevent_pool;     //第二执行队列
        
        typedef std::vector<SVEventProcPtr> PROCERPOOL;
        PROCERPOOL m_event_procers;
        
        //系统消息处理
        struct SYSEVTPROC {
            SVObjectPtr caller;
            proc_sys_event _cb;
        };
        typedef std::vector<SYSEVTPROC> SYS_LISTEN_CB_POOL;
        SYS_LISTEN_CB_POOL m_sys_listen_pool;
        
        SVLock m_waitlock;
    };
    
}//!namespace sv

//
#endif //SV_EVENTMGR_H
