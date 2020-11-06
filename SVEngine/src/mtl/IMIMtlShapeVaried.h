//
// IMIMtlShapeVaried.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTLSHAPEVARIED_H
#define IMI_MTLSHAPEVARIED_H

#include "IMIMtlCore.h"

namespace imi {
    
    class IMIMtlFaceShapeVaried : public IMIMtlCore {
    public:
        IMIMtlFaceShapeVaried(IMIInstPtr _app);
        
        IMIMtlFaceShapeVaried(IMIMtlFaceShapeVaried *_mtl);
        
        ~IMIMtlFaceShapeVaried();
        
        virtual IMIMtlCorePtr clone();
        
        virtual void update(f32 dt);
        
    protected:
        void _submitMtl(IMIRendererPtr _render);

        f32 m_startPoint[48];
        f32 m_endPoint[48];
        f32 m_actionType[24];
        f32 m_intensity[24];
        f32 m_radius[24];
        s32 m_RealStep[1];
        f32 m_outlinePoints[212];
        f32 m_eyesDistance;
        f32 m_inversedEyesDistance;
        f32 m_g_intensity[14];
        f32 m_surfaceWidth;
        f32 m_surfaceHeight;
        f32 m_inv_surfaceWidth;
        f32 m_inv_surfaceHeight;
    };
        
}//!namespace imi

#endif /* IMI_MTLSHAPEVARIED_H */
