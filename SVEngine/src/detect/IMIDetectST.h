//
// IMIDetectST.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_DETECTST_H
#define IMI_DETECTST_H

#include "IMIDetectBase.h"

#define ST_POINT_NUM 106

namespace imi {
    
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
    
    class IMIDetectST : public IMIDetectBase {
    public:
        IMIDetectST(IMIInstPtr _app);
        
        ~IMIDetectST();
       
        void pushData(void *_faceData);
        
        PERSON_STDATA *getData(s32 _personid);

        PERSON_STDATA stData[SUPPORT_MAX_PERSON_NUM];
    protected:
        void _parseData(void *data);
    };

}//!namespace imi



#endif //IMI_DETECTST_H
