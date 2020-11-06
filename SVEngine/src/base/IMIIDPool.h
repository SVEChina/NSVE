//
// Created by xuziyu on 2017/2/24.
//

#ifndef IMI_IDPOOL_H
#define IMI_IDPOOL_H

#include "IMIObject.h"
#include "IMIArray.h"

//唯一ID池

namespace imi {
    
    class IMIIDPool : public IMIObject {
    public:
        IMIIDPool();
        
        ~IMIIDPool();
        
        u32 applyUID();
        
        void returnUID(u32 uid);
        
    private:
        u32 _random8();
        
        u32 _createID();
        
        bool _hasID(u32 _uid);
        
    public:
        u8 m_initialized;
        
        u64 m_seed;
        
        typedef IMIArray<s32> IDPOOL;
        IDPOOL m_idpool;
    };
    
}//!namespace imi




#endif //IMI_NODECREATOR_H
