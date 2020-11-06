//
// IMIMtlBeauty.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTLBEAUTY_H
#define IMI_MTLBEAUTY_H

#include "IMIMtlCore.h"

namespace imi {
    
    class IMIMtlBeauty : public IMIMtlCore  {
    public:
        IMIMtlBeauty(IMIInstPtr _app);
        
        IMIMtlBeauty(IMIMtlBeauty* _mtl);
        
        ~IMIMtlBeauty();
        
        virtual IMIMtlCorePtr clone();
        
        void setSmooth(f32 _smooth);
        
        void setBGSize(s32 _width, s32 _height);

    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_lSmoothSize;
        f32 m_lImgW;
        f32 m_lImgH;
    };
        
}//!namespace imi



#endif //IMI_MTLBEAUTY_H
