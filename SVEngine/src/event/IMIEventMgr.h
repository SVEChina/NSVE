//
// IMIEventMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_EVENTMGR_H
#define IMI_EVENTMGR_H

#include "../basesys/IMISysBase.h"
#include "../work/IMITdCore.h"
#include "IMIEventDef.h"
#include <vector>
#include <map>

namespace imi {
    
    class IMIEventMgr : public IMISysBase {
    public:
        IMIEventMgr(IMIInstPtr _app);
        
        ~IMIEventMgr();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
        void reset();
        
        //监听某一个具体的消息
        void listenSysEvent(IMIObjectPtr caller,proc_sys_event _cb);
        
        void unlistenSysEvent(IMIObjectPtr caller);
        
        void clearListenSysEvent();
        
        //推送事件
        void pushEvent(IMIEventPtr _event,bool _cache = false);
        
        //注册事件处理器
        bool hasRegist(IMIEventProcPtr _procer);
        
        void registProcer(IMIEventProcPtr _procer);
        
        void unregistProcer(IMIEventProcPtr _procer);
        
    private:
        void clearAllEvent();
        
        void clearAllEventProcer();
        
        void _processEvent(IMIEventPtr _event);
        
    private:
        //普通消息处理
        typedef std::vector<IMIEventPtr> EVENTPOOL;
        EVENTPOOL m_exe_eventList0;     //事件队列0
        EVENTPOOL m_exe_eventList1;     //事件队列1
        
        EVENTPOOL *m_active_pool;       //当前执行的消息池
        EVENTPOOL *m_waitevent_pool;    //等待消息池
        EVENTPOOL m_cachevent_pool;     //第二执行队列
        
        typedef std::vector<IMIEventProcPtr> PROCERPOOL;
        PROCERPOOL m_event_procers;
        
        //系统消息处理
        struct SYSEVTPROC {
            IMIObjectPtr caller;
            proc_sys_event _cb;
        };
        typedef std::vector<SYSEVTPROC> SYS_LISTEN_CB_POOL;
        SYS_LISTEN_CB_POOL m_sys_listen_pool;
        
        IMILock m_waitlock;
    };
    
}//!namespace imi

//
#endif //IMI_EVENTMGR_H
