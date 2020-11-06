//
// IMIEventVideo.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_EVENTVIDEO_H
#define IMI_EVENTVIDEO_H


#include "IMIEvent.h"

namespace imi {
    
    class IMIEventVideo : public IMIEvent {
    public:
        IMIString videoname;
    };
    
    //视频控制
    class IMIEventVideoCtrl : public IMIEventVideo {
    public:
        IMIEventVideoCtrl();
        
        VIDEOCTRL ctrlmode;
    };
    
    //
    class IMIEventVideoStatus : public IMIEventVideo {
    public:
        IMIEventVideoStatus();
        
        VIDEOSTATE state;
    };
    
    //保存开始
    class IMIEventMixBegin : public IMIEventVideo {
    public:
        IMIEventMixBegin();
    };
    
    //保存结束
    class IMIEventMixEnd : public IMIEventVideo {
    public:
        IMIEventMixEnd();
    };

    
}//!namespace imi


#endif //IMI_EVENTVIDEO_H
