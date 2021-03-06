//
// SVDetectST.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_DETECTST_H
#define SV_DETECTST_H

#include "SVDetectBase.h"

#define ST_POINT_NUM 106

namespace sv {
    
    struct ST_PT {
        f32 x;
        f32 y;
    };
    struct PERSON_STDATA {
        bool has;
        f32 yaw;
        f32 pitch;
        f32 roll;
        s32 recttop;
        s32 rectbottom;
        s32 rectright;
        s32 rectleft;
        ST_PT pointdata[ST_POINT_NUM];
    };
    
    class SVDetectST : public SVDetectBase {
    public:
        SVDetectST(SVInstPtr _app);
        
        ~SVDetectST();
       
        void pushData(void *_faceData);
        
        PERSON_STDATA *getData(s32 _personid);

        PERSON_STDATA stData[SUPPORT_MAX_PERSON_NUM];
    protected:
        void _parseData(void *data);
    };

}//!namespace sv



#endif //SV_DETECTST_H
