//
// IMIModelMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MODELMGR_H
#define IMI_MODELMGR_H

#include "../basesys/IMISysBase.h"
#include "../base/IMIMap.h"
namespace imi {

    class IMIModelMgr : public IMISysBase{
    public:
        IMIModelMgr(IMIInstPtr _app);
        
        ~IMIModelMgr();
        
        void init();
        
        void update(f32 _dt);
        
        void destroy();
        
        void addModel(IMIModelPtr _model);
        
        IMIModelPtr getModel(IMIString _name);
        
    protected:
        bool _hasModel(IMIModelPtr _model);
        void _recycleUnuseModel();
        typedef IMIArray<IMIModelPtr> MODELPOOL;
        MODELPOOL m_modelPool;
        IMILockPtr m_lock;
    };


}//!namespace imi



#endif //IMI_MODELMGR_H
