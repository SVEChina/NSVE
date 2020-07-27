//
// Created by yizhou Fu on 2017/3/16.
//

#ifndef SV_LISTENBASE_H
#define SV_LISTENBASE_H

#include "SVGBase.h"
#include "SVArray.h"

namespace sv {
    
    //监听函数池
    struct LISTENFUNC {
        SVObject *listener;
        dataListenFunc func;
    };
    
    class SVListenBase : public SVGBaseEx {
    public:
        SVListenBase(SVInstPtr _app);
        
        ~SVListenBase();
        
        //类函数指针监听
        void registListenFunc(SVObject *listener, dataListenFunc func);
        
        void unregistListenFunc(SVObject *listener, dataListenFunc func);
        
        void noticeListener(f32 dt);
        
    protected:
        virtual void _updateSelf(f32 dt);
        
        virtual void _notice(f32 dt);
        
        typedef SVArray<LISTENFUNC> LISTENFUNCPOOL;
        LISTENFUNCPOOL m_listenfunc_pool;
        SVLockPtr m_listenlock;
        bool m_listenDirty;
    };

}//!namespace sv


#endif //SV_LISTENBASE_H
