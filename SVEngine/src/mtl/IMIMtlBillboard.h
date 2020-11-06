//
// IMIMtlBillboard.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTL_BILLBOARD_H
#define IMI_MTL_BILLBOARD_H


#include "IMIMtlCore.h"

namespace imi {

    class IMIMtlBillboard : public IMIMtlCore {
    public:
        IMIMtlBillboard(IMIInstPtr _app);
        
        IMIMtlBillboard(IMIMtlBillboard *_mtl);
        
        ~IMIMtlBillboard();
        
        virtual void reset();
        
        virtual IMIMtlCorePtr clone();
        
        void setObjectPos(FVec3 &_pos);//物体世界位置
        
        void setViewPos(FVec3 &_viewPos);
        
        void setUp(FVec3 &_up);
    protected:
        virtual void _submitUniform(IMIRendererPtr _render);
        FVec3 m_objPos;
        FVec3 m_viewPos;
        FVec3 m_up;
    };

}//!namespace imi


#endif //IMI_MTL_BILLBOARD_H
