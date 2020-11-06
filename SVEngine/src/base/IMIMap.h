#ifndef __MAP_H__
#define __MAP_H__

#include "IMICoreTree.h"

namespace imi {
    
   
        
        //
        template <class Type> struct MapData {
            Type data;
        };
        
        //
        template <class Key,class Type> class IMIMap : public IMICoreTree<Key,MapData<Type> > {
        public:
            IMIMap() {
            }
            
            ~IMIMap() {
            }

            typename IMIMap<Key,Type>::Iterator findData(const Type &t) const {
                typename IMIMap<Key,Type>::Iterator end_it = IMICoreTree<Key,MapData<Type> >::end();
                for(typename IMIMap<Key,Type>::Iterator it = IMICoreTree<Key,MapData<Type> >::begin(); it != end_it; ++it) {
                    if(it->data == t) {
                         return it;
                    }
                }
                return end_it;
            }
            
            sv_inline Type &operator[](const Key &key) {
                s32 change = 0;
                typename IMIMap<Key,Type>::Node *parent = 0;
                typename IMIMap<Key,Type>::Node *node = IMICoreTree<Key,MapData<Type> >::append_proc(key,IMICoreTree<Key,MapData<Type> >::root,parent,change);
                return node->data;
            }
            
            sv_inline Type &get(const Key &key) {
                s32 change = 0;
                typename IMIMap<Key,Type>::Node *parent = 0;
                typename IMIMap<Key,Type>::Node *node = IMICoreTree<Key,MapData<Type> >::append_proc(key,IMICoreTree<Key,MapData<Type> >::root,parent,change);
                return node->data;
            }
            
            sv_inline Type &append(const Key &key) {
                s32 change = 0;
                typename IMIMap<Key,Type>::Node *parent = 0;
                typename IMIMap<Key,Type>::Node *node = IMICoreTree<Key,MapData<Type> >::append_proc(key,IMICoreTree<Key,MapData<Type> >::root,parent,change);
                return node->data;
            }
            
            sv_inline void append(const Key &key,const Type &t) {
                s32 change = 0;
                typename IMIMap<Key,Type>::Node *parent = 0;
                typename IMIMap<Key,Type>::Node *node = IMICoreTree<Key,MapData<Type> >::append_proc(key,IMICoreTree<Key,MapData<Type> >::root,parent,change);
                node->data = t;
            }
            
            void append(const IMIMap<Key,Type> &m) {
                typename IMIMap<Key,Type>::Iterator end_it = m.end();
                for(typename IMIMap<Key,Type>::Iterator it = m.begin(); it != end_it; ++it) {
                    append(it->key,it->data);
                }
            }
        };
        
    
    
}//!namespace imi



#endif /* __MAP_H__ */
