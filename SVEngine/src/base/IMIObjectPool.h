//
// IMIObjectPool.h
// IMIngine
// Copyright 2017-2020
// yizhou Fu
// 

#ifndef IMI_OBJECT_POOL_H
#define IMI_OBJECT_POOL_H

#include "IMIGBase.h"
#include <vector>

namespace imi {

#define OBJPOOL_DEFAULT_SIZE 100

    template <class ShareT,class T> class IMIObjectPool : IMIGBaseEx {
    public:
        IMIObjectPool(IMIInstPtr _app)
        :IMIGBaseEx(_app) {
            m_size = 0;
            m_use = 0;
            m_step = 100;
            _ex_pool(OBJPOOL_DEFAULT_SIZE);
        }

        IMIObjectPool(IMIInstPtr _app,s32 _size,s32 _step)
        :IMIGBaseEx(_app) {
            m_size = 0;
            m_use = 0;
            m_step = _step;
            _ex_pool(_size);
        }

        ShareT applyObject() {
            if(!m_FREE_ID.empty()) {
                s32 t_id = m_FREE_ID.back();
                m_FREE_ID.pop_back();
                return m_OBJ_POOL[t_id];
            }
            if(m_use>=m_size) {
                _ex_pool(m_size + m_step);
            }
            //
            ShareT t_obj = m_OBJ_POOL[m_use++];
            return t_obj;
        }

        ShareT getObject(s32 _id) {
            if( _id<m_OBJ_POOL.size() && _id>=0 ) {
                return m_OBJ_POOL[_id];
            }
            return nullptr;
        }

        ShareT removeObject(s32 _id) {
            if( _id<m_OBJ_POOL.size() && _id>=0 ) {
                ShareT t_obj = m_OBJ_POOL[_id];
                m_OBJ_POOL[_id]->unload();   //这里应该调用卸载函数
                m_FREE_ID.push_back(_id);
                return t_obj;
            }
            return nullptr;
        }
        
        void clear() {
            
        }

    private:
        void _ex_pool(s32 _size) {
            if(m_size == 0) {
                //第一次分配
                m_OBJ_POOL.resize(_size);
                for(s32 i=0;i<_size;i++) {
                    m_OBJ_POOL[i] = MakeSharedPtr<T>(mApp);
                    m_OBJ_POOL[i]->m_pool_id = i;
                }
                m_size = _size;
                return ;
            }
            if(_size<m_size) {
                //不能越扩充越小
                return ;
            }
            //保留数据
            std::vector<ShareT> tmpPool;
            tmpPool.resize(m_size);
            for(s32 i=0;i<m_OBJ_POOL.size();i++) {
                tmpPool[i] = m_OBJ_POOL[i];
            }
            //
            m_OBJ_POOL.clear();
            m_OBJ_POOL.resize(m_size);
            for(s32 i=0;i<m_size;i++) {
                if(i<tmpPool.size()) {
                    m_OBJ_POOL[i] = tmpPool[i];
                }else{
                    m_OBJ_POOL[i] = MakeSharedPtr<T>(mApp);
                    m_OBJ_POOL[i]->m_pool_id = i;
                }
            }
            m_size = _size;
        }

        
    protected:
        //大小
        s32 m_size;
        //
        s32 m_use;
        //扩充的步伐
        s32 m_step;
        //空闲ID
        std::vector<s32> m_FREE_ID;
        //对象池
        std::vector<ShareT> m_OBJ_POOL;
    };

    //DECLARE_SHAREPTR(IMIObjectPool);
    
}//!namespace imi


#endif //IMI_OBJECT_POOL_H
