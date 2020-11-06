//
// IMIOpBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPERATEBASE_H
#define IMI_OPERATEBASE_H


#include "../base/IMIGBase.h"
#include "../node/IMINodeDeclare.h"

namespace imi {
    
    class IMIOpBase : public IMIGBaseEx {
    public:
        IMIOpBase(IMIInstPtr _app);
        
        ~IMIOpBase();
        
        virtual void process(f32 dt);
        
        void setCallBack(cb_func_op _cb, void* _obj, cptr8 _info);
        
    protected:
        virtual void _process(f32 dt);
        
        cb_func_op m_pCB;
        
        void *m_obj;
        
        IMIString m_info;
    };
    
    
    
    
}//!namespace imi



#endif //IMI_OPERATEBASE_H
