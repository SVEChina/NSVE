//
// SVRFbo.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RFBO_H
#define SV_RFBO_H

#include "SVRRes.h"
#include "../base/SVColor.h"

namespace sv {
    
    class SVRFbo: public SVRRes {
    public:
        SVRFbo(SVInstPtr _app);

        virtual ~SVRFbo();

        virtual void create(SVRendererPtr _renderer) {}

        virtual void destroy(SVRendererPtr _renderer) {}
        
        virtual void load() {}
        
        virtual void unload() {}
        
        virtual void resize(s32 _width,s32 _height,SVRendererPtr _renderer) {}

        virtual void bind(SVRendererPtr _renderer) {}

        virtual void unbind(SVRendererPtr _renderer) {}
        
        sv_inline void setClearColor(u32 _argb){ m_color_value.setColorARGB(_argb); }
        
        sv_inline void setClearDepth(f32 _depth){ m_depth_value = _depth; }
        
        sv_inline void setClearStencil(s32 _stencil){ m_stencil_value = _stencil; }

    protected:
        SVLockPtr m_texLock;
        s32 m_width;
        s32 m_height;
        s32 m_target_num;
        bool m_use_depth;
        bool m_use_stencil;
        //值
        SVColor m_color_value;
        f32 m_depth_value;
        s32 m_stencil_value;
    };
        
}//!namespace sv


#endif /* SV_RFBO_H */
