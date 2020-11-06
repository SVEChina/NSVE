//
// IMIRGBToneCurveFilter.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#ifndef IMI_RGBTONECURVEFILTER_H
#define IMI_RGBTONECURVEFILTER_H

#include "../mtl/IMIMtlDeclare.h"
#include "../node/IMINodeDeclare.h"
#include "IMIFilterBase.h"

namespace imi {

    class IMIRGBToneCurveFilter : public IMIFilterBase {
    public:
        IMIRGBToneCurveFilter(IMIInstPtr _app);

        ~IMIRGBToneCurveFilter();

        virtual bool create();

        virtual void destroy();

        virtual void update(f32 dt);

        IMIMtlCorePtr m_mtl_rgba;

        IMIMtlCorePtr m_mtl_back;

        IMITexturePtr texrgb;
    };
        
}//!namespace imi

#endif /* IMI_RGBTONECURVEFILTER_H */
