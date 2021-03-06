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
    
    struct SVTargetDsp;
    class SVRFbo: public SVRRes {
    public:
        SVRFbo(SVInstPtr _app);

        virtual ~SVRFbo();

        virtual void load(SVRendererPtr _renderer,SVTargetDsp* _logic_dsp) {
            m_fbo_dsp = _logic_dsp;
        }

        virtual void unload() {}
        
        virtual void resize(s32 _width,s32 _height,SVRendererPtr _renderer) {}

        virtual void bind(SVRendererPtr _renderer) {}

        virtual void unbind(SVRendererPtr _renderer) {}

    protected:
        SVLockPtr m_texLock;
        SVTargetDsp* m_fbo_dsp;     //逻辑对象的dsp
    };
        
}//!namespace sv


#endif /* SV_RFBO_H */
