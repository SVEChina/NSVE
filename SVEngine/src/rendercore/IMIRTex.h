//
// IMIRTex.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMIRTex_h
#define IMIRTex_h

#include "IMIRRes.h"

namespace imi {
    
    struct IMITextureDsp;
    class IMIRTex: public IMIRRes{
    public:
        IMIRTex(IMIInstPtr _app);
        
        virtual ~IMIRTex();
        
        virtual void load(IMIRendererPtr _renderer,IMITextureDsp* _tex_dsp);
        
        virtual void unload();
        
        virtual void resize();
        
        virtual void setTexData(IMIDataSwapPtr _data);
        
        virtual void setTexCubeData(IMIDataSwapPtr _data,s32 _index);
        
        virtual void commit(); //数据提交到显卡
        
    protected:
        IMILockSpinPtr m_texLock;
        s32 m_msaa;
        IMITextureDsp* m_texture_dsp;
    };
        
}//!namespace imi


#endif /* IMIRTex_h */
