// IMIDataSwap.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_DATASWAP_H
#define IMI_DATASWAP_H

//数据交换区 有信号量互斥 共享区域

#include "../base/IMIObject.h"
#include "../work/IMITdCore.h"
#include "../base/IMIPreDeclare.h"

namespace imi {
    
    class IMIDataSwap : public IMIObject {
    public:
        IMIDataSwap();
        
        ~IMIDataSwap();
        
        void resize(u32 _size);
        
        void extendSize(u32 _size);
        
        void reback();
        
        void writeData(void *_data, u32 len);
        
        void appendData(void *_data, u32 len);
        
        void fetchData(void *_data, u32 len);
        
        void *getData();
        
        u32 getSize();
        
        u32 getCacheSize();
        
        void lockData();
        
        void unlockData();
        
        void unlockData(u32 _realSize);
        
        void swap(IMIDataSwapPtr pTarget);
        
    protected:
        void *m_pData;
        u32 m_cacheSize;        //缓存空间大小
        u32 m_realSize;         //真实空间大小
        IMILockPtr m_swapLock;
    };
    
}//!namespace imi


#endif //IMI_DATASWAP_H
