//
// IMIOpEvent.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPEVENT_H
#define IMI_OPEVENT_H


#include "IMIEvent.h"

namespace imi {
    
    class IMITouchEvent : public IMIEvent {
    public:
        IMITouchEvent();
        s32 x;
        s32 y;
    };
    
    class IMITouchWorldEvent : public IMIEvent {
    public:
        IMITouchWorldEvent();
        f32 x;
        f32 y;
        f32 z;
    };
    //
    class IMIPickEvent : public IMIEvent {
    public:
        IMIPickEvent();
        u32 colorid;
    };
    
    //
    class IMICameraOrenEvent : public IMIEvent {
    public:
        IMICameraOrenEvent();
        f32 yaw;
        f32 pitch;
        f32 roll;
    };
    
    class IMICameraMatrixEvent : public IMIEvent {
    public:
        IMICameraMatrixEvent();
        
        ~IMICameraMatrixEvent();
        
        IMIDataSwapPtr m_matData;
    };
    
    class IMIProjectMatrixEvent : public IMIEvent {
    public:
        IMIProjectMatrixEvent();
        
        ~IMIProjectMatrixEvent();
        
        IMIDataSwapPtr m_matData;
    };

    class IMICameraPosEvent : public IMIEvent {
    public:
        IMICameraPosEvent();
        
        f32 m_px;
        f32 m_py;
        f32 m_pz;
    };

    class IMICameraDirEvent : public IMIEvent {
    public:
        IMICameraDirEvent();
        
        f32 m_dx;
        f32 m_dy;
        f32 m_dz;
    };
    
    class IMIReactEvent : public IMIEvent {
    public:
        IMIReactEvent();
        bool isEqual(IMIEventPtr _event);
        IMIString     m_actAniName;//要切换的spine动画名称
        s32         m_actAniLoop;//要切换的spine动画是否循环播放
    };

    
}//!namespace imi



#endif //IMI_OPEVENT_H
