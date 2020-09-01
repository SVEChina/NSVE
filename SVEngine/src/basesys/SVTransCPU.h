//
// SVTransCPU.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TRANS_CPU_H
#define SV_TRANS_CPU_H

#include "SVTrans.h"

namespace sv {

        class SVTransCPU : public SVTrans {
        public:
            SVTransCPU(SVInstPtr _app);
            
            virtual ~SVTransCPU();
            
            void init(s32 _w, s32 _h,f32 _angle,SV_PIC_FORMATE _picformate,SV_TEXIN _tt);
            
            void destroy();
            
            void update(f32 dt);
            
            void render();
        };

}//!namespace sv

#endif //SV_TRANS_CPU_H
