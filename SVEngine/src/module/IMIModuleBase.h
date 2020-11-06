//
// IMIModuleBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MODULEBASE_H
#define IMI_MODULEBASE_H

#include "IMIModuleDef.h"
#include "../event/IMIEventProc.h"
#include "../base/IMIDef.h"
#include "../node/IMINodeDeclare.h"

namespace imi{
    
    class IMIModuleBase : public IMIEventProc {
    public:
        IMIModuleBase(IMIInstPtr _app);
        
        virtual ~IMIModuleBase();
        
        virtual void init();
        
        virtual void destroy();
        
        virtual void update(f32 _dt);
        
        virtual void open();
        
        virtual void close();
        
        virtual bool isOpen();
        
        virtual void setOpCallBack(cb_func_op _cb, void *_obj);
        
        void setModuleName(cptr8 _name){ m_module_name = _name;}
        
        cptr8 getModuleName() { return m_module_name.c_str() ;}
        
    protected:
        bool m_isOpen;
        
        cb_func_op m_cb;
        
        void *m_obj;
        
        IMIString m_module_name;
    };
    
}//!namespace imi





#endif //IMI_MODULESYS_H
