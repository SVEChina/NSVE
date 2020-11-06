//
// IMIMtlRGB2YUV.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTL_RGB2YUV_H
#define IMI_MTL_RGB2YUV_H

#include "IMIMtlCore.h"

namespace imi {
    
        
    class IMIMtlRGB2YUV : public IMIMtlCore {
    public:
        IMIMtlRGB2YUV(IMIInstPtr _app, IMI_OUTSTEAMFORMATE formate);
        
        IMIMtlRGB2YUV(IMIMtlRGB2YUV* _mtl);
        
        ~IMIMtlRGB2YUV();
        
        virtual IMIMtlCorePtr clone();
        
        void setTex(f32 _w, f32 _h);
        
        void _submitMtl(IMIRendererPtr _render); 
        
    private:
        s32 m_tex_w;
        s32 m_tex_h;
    };
        
    
}//!namespace imi



#endif //IMI_MTL_RGB2YUV_H
