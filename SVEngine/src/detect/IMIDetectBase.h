//
// IMIDetectBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_DETECTBASE_H
#define IMI_DETECTBASE_H

#include "../base/IMIListenBase.h"
#include "../base/IMIDatatDef.h"

namespace imi {

    class IMIDetectBase : public IMIListenBase {
    public:
        IMIDetectBase(IMIInstPtr _app);
        
        ~IMIDetectBase();
        
        virtual void update(f32 _dt);
        
        virtual s32 transformIndex(s32 index);
        
        virtual BINDREGION getIndexRegion(s32 index);
        
        virtual void pushData(void *_faceData);
        
    protected:
        s32 m_ptNum;
    };

}//!namespace imi




#endif //IMI_DETECTBASE_H
