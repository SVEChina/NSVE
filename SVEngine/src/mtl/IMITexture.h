//
// IMITexture.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_TEXTURE_H
#define IMI_TEXTURE_H

#include "IMIMtlDef.h"
#include "../base/IMIResDsp.h"
#include "../rendercore/IMIRTex.h"
#include "../rendercore/IMIRenderDef.h"

namespace imi {
    
    class IMITexture : public IMIGBaseEx {
    public:
        IMITexture(IMIInstPtr _app);
        
        virtual ~IMITexture();
        
        IMITexturePtr share();

        void dispatch();

        void init(IMITextureDsp& _dsp);
        
        void init(IMITextureDsp& _dsp,IMIDataSwapPtr _data);

        void destroy();
        
        void resize(s32 _w,s32 _h);
        
        void setTexData(IMIDataSwapPtr _data);
        
        void setTexCubeData(IMIDataSwapPtr _data,s32 _index);

        void bindRes(s32 _instid);
        
        void unbindRes();
        
        IMIRTexPtr getResTex();
        
        IMIDataSwapPtr getTextureData();
        
        IMIDataSwapPtr getTextureCubeData(s32 _index);
        
        IMITextureDsp* getTextureDsp() { return &m_texture_dsp;}

        void swap(IMITexturePtr _tex);
        
    protected:
        bool _canSwap(IMITexturePtr _tex);
        
        s32 m_tex_pool_id;
        
        IMILockSpinPtr m_lock;
        
        IMITextureDsp m_texture_dsp;
        
    public:
        //纹理名称
        IMIString m_name;
        
        virtual void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate){}
        
        virtual void fetchData(u8* _dstPtr,s32 _w,s32 _h){}
    };
        
}//!namespace imi



#endif //IMI_TEXTURE_H
