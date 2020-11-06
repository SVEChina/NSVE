//
// IMITransGPU.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_TRANS_GPU_H
#define IMI_TRANS_GPU_H

#include "IMITrans.h"
#include "../mtl/IMIMtlDef.h"
#include "../node/IMINodeDeclare.h"

namespace imi {

    class IMITransGPU : public IMITrans {
    public:
        IMITransGPU(IMIInstPtr _app,
                   IMITexturePtr _t0,
                   IMITexturePtr _t1,
                   IMITexturePtr _t2,
                   IMITexturePtr _tOut);
        
        virtual ~IMITransGPU();
        
        void init(s32 _w, s32 _h,f32 _angle,IMI_PIC_FORMATE _formate,IMI_TEXIN _tt);
        
        void destroy();
        
        void update(f32 dt);
        
        void render();
        
        void setAngle(f32 _angle);
        
    protected:
        IMITexturePtr m_tex0;
        IMITexturePtr m_tex1;
        IMITexturePtr m_tex2;
        IMITexturePtr m_texOut;
        f32 m_angle;
        IMIMtlCorePtr m_pMtl;

        void createPass(s32 _w, s32 _h, f32 _angle, IMI_TEXIN _tt);
    };
        
}//!namespace imi

#endif //IMI_TRANS_GPU_H
