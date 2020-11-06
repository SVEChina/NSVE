#ifndef __SET_H__
#define __SET_H__

#include "IMICoreTree.h"

namespace imi {
       
    struct SetData {
        
    };

    template <class Key> class IMISet : public IMICoreTree<Key,SetData> {
    public:
        IMISet() {
        }

        ~IMISet() {
        }
        
        sv_inline void append(const Key &key) {
            s32 change = 0;
            typename IMISet<Key>::Node *parent = 0;
            IMICoreTree<Key,SetData>::append_proc(key,IMICoreTree<Key,SetData>::root,parent,change);
        }
        
        void append(const IMISet<Key> &s) {
            typename IMISet<Key>::Iterator end_it = s.end();
            for(typename IMISet<Key>::Iterator it = s.begin(); it != end_it; ++it) {
                append(it->key);
            }
        }
    };
        
    
    
}//!namespace imi


#endif /* __SET_H__ */
