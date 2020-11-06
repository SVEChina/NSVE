//
// IMITransCPU.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_TRANS_CPU_H
#define IMI_TRANS_CPU_H

#include "IMITrans.h"

namespace imi {

        class IMITransCPU : public IMITrans {
        public:
            IMITransCPU(IMIInstPtr _app);
            
            virtual ~IMITransCPU();
            
            void init(s32 _w, s32 _h,f32 _angle,IMI_PIC_FORMATE _picformate,IMI_TEXIN _tt);
            
            void destroy();
            
            void update(f32 dt);
            
            void render();
        };

}//!namespace imi

#endif //IMI_TRANS_CPU_H
