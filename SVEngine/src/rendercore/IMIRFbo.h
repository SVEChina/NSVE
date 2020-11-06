//
// IMIRFbo.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RFBO_H
#define IMI_RFBO_H

#include "IMIRRes.h"
#include "../base/IMIColor.h"

namespace imi {
    
    struct IMITargetDsp;
    class IMIRFbo: public IMIRRes {
    public:
        IMIRFbo(IMIInstPtr _app);

        virtual ~IMIRFbo();

        virtual void load(IMIRendererPtr _renderer,IMITargetDsp* _logic_dsp) {
            m_fbo_dsp = _logic_dsp;
        }

        virtual void unload() {}
        
        virtual void resize(s32 _width,s32 _height,IMIRendererPtr _renderer) {}

        virtual void bind(IMIRendererPtr _renderer) {}

        virtual void unbind(IMIRendererPtr _renderer) {}

    protected:
        IMILockPtr m_texLock;
        IMITargetDsp* m_fbo_dsp;     //逻辑对象的dsp
    };
        
}//!namespace imi


#endif /* IMI_RFBO_H */
