//
// Created by yizhou Fu on 2017/3/16.
//

#ifndef IMI_LISTENBASE_H
#define IMI_LISTENBASE_H

#include "IMIGBase.h"
#include "IMIArray.h"

namespace imi {
    
    //监听函数池
    struct LISTENFUNC {
        IMIObject *listener;
        dataListenFunc func;
    };
    
    class IMIListenBase : public IMIGBaseEx {
    public:
        IMIListenBase(IMIInstPtr _app);
        
        ~IMIListenBase();
        
        //类函数指针监听
        void registListenFunc(IMIObject *listener, dataListenFunc func);
        
        void unregistListenFunc(IMIObject *listener, dataListenFunc func);
        
        void noticeListener(f32 dt);
        
    protected:
        virtual void _updateSelf(f32 dt);
        
        virtual void _notice(f32 dt);
        
        typedef IMIArray<LISTENFUNC> LISTENFUNCPOOL;
        LISTENFUNCPOOL m_listenfunc_pool;
        IMILockPtr m_listenlock;
        bool m_listenDirty;
    };

}//!namespace imi


#endif //IMI_LISTENBASE_H
