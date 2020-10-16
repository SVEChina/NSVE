//
// SVTexture.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TEXTURE_H
#define SV_TEXTURE_H

#include "SVMtlDef.h"
#include "../rendercore/SVRTex.h"
#include "../rendercore/SVRenderDef.h"

namespace sv {
    
    class SVTexture : public SVGBaseEx {
    public:
        SVTexture(SVInstPtr _app);
        
        virtual ~SVTexture();
        
        void init(SVTextureDsp& _dsp);
        
        void init(SVTextureDsp& _dsp,SVDataSwapPtr _data);

        void destroy();
        
        void resize(s32 _w,s32 _h);
        
        void setTexData(SVDataSwapPtr _data);
        
        void setTexCubeData(SVDataSwapPtr _data,s32 _index);

        void bindRes(SVRTexPtr _res);
        
        void unbindRes();
        
        SVRTexPtr getResTex();
        
        SVDataSwapPtr getTextureData();
        
        SVDataSwapPtr getTextureCubeData(s32 _index);
        
        SVTextureDsp* getTextureDsp() { return &m_texture_dsp;}

        //
        void swap(SVTexturePtr _tex);
        
    protected:
        s32 m_tex_pool_id;
        
        SVLockSpinPtr m_lock;
        
        SVTextureDsp m_texture_dsp;
        
    public:
        //纹理名称
        SVString m_name;
        
        virtual void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate){}
        
        virtual void fetchData(u8* _dstPtr,s32 _w,s32 _h){}
    };
        
}//!namespace sv



#endif //SV_TEXTURE_H
