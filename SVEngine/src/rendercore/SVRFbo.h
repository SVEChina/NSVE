//
// SVRFbo.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RFBO_H
#define SV_RFBO_H

#include "SVRRes.h"

namespace sv {
    
    class SVRFbo: public SVRRes{
    public:
        SVRFbo(SVInstPtr _app);

        virtual ~SVRFbo();

        virtual void create(SVRendererPtr _renderer) {}

        virtual void destroy(SVRendererPtr _renderer) {}
        
        virtual void resize(s32 _width,s32 _height,SVRendererPtr _renderer) {}

        virtual void bind(SVRendererPtr _renderer) {}

        virtual void unbind(SVRendererPtr _renderer) {}

    protected:
        SVLockPtr m_texLock;
        s32 m_width;
        s32 m_height;
        s32 m_target_num;
        bool m_use_depth;
        bool m_use_stencil;
    };
        
}//!namespace sv


#endif /* SV_RFBO_H */
