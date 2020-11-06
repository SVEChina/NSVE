#ifndef __SET_SPU_H__
#define __SET_SPU_H__

#include "IMICoreTree.spu.h"

namespace imi {
    
    //
    class SetData {
    public:
        SetData() {
        }
        
        ~SetData() {
        }
    };
    
    //
    template <class Key,u16 Capacity = 128> class IMISet : public IMICoreTree<Key,SetData,Capacity> {
    public:
        IMISet() {
        }
        
        ~IMISet() {
        }
        
        sv_inline void append(const Key &key) {
            s16 change = 0;
            typename IMISet<Key,Capacity>::Node *parent = 0;
            append_proc(key,IMICoreTree<Key,SetData,Capacity>::root,parent,change);
        }
    };
        
    
    
}//!namespace imi



#endif /* __SET_SPU_H__ */
