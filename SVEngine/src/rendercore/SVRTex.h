//
// SVRTex.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SVRTex_h
#define SVRTex_h

#include "SVRRes.h"

namespace sv {
    
    struct SVTextureDsp;
    class SVRTex: public SVRRes{
    public:
        SVRTex(SVInstPtr _app);
        
        virtual ~SVRTex();
        
        virtual void create(SVRendererPtr _renderer,SVTextureDsp* _tex_dsp);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        virtual void resize();
        
        virtual void setTexData(SVDataSwapPtr _data);
        
        virtual void setTexCubeData(SVDataSwapPtr _data,s32 _index);
        
        //数据提交到显卡
        virtual void commit();
        
        //交换纹理
        virtual void swap(SVRTexPtr _rtex);
        
    protected:
        SVLockSpinPtr m_texLock;
        s32 m_msaa;
        SVTextureDsp* m_texture_dsp;
    };
        
}//!namespace sv


#endif /* SVRTex_h */
