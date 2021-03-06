//
// SVEventDef
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_EVENTDEF_H
#define SV_EVENTDEF_H

#include "SVEventDeclare.h"

namespace sv {

    //
    typedef void (*proc_sys_event)(SVObjectPtr sender,SVEventPtr _event);

    //
    enum SV_EVENT_TYPE {
        EVN_T_NONE,
        EVN_T_SYS_BEGIN,
        EVN_T_SYS_INIT_RENDERER,
        EVN_T_SYS_END,
        EVN_T_TOUCH_BEGIN,//1
        EVN_T_TOUCH_MOVE, //2
        EVN_T_TOUCH_LONGPRESS,//3
        EVN_T_TOUCH_END,//4
        EVN_T_TOUCH_CANCEL,//5
        EVN_T_TOUCH_WORLD_BEGIN,//1
        EVN_T_TOUCH_WORLD_MOVE, //2
        EVN_T_TOUCH_WORLD_LONGPRESS,//3
        EVN_T_TOUCH_WORLD_END,//4
        EVN_T_TOUCH_WORLD_CANCEL,//5
        EVN_T_CAMERA_OREN,
        EVN_T_DEVICE_ACCELEROMETER,
        EVN_T_CAMERA_MATRIX,
        EVN_T_PROJECT_MATRIX,
        EVN_T_CAMERA_POSITION,
        EVN_T_CAMERA_DIRECTION,
        EVN_T_ANCHOR_AR,
        EVN_T_ANCHORPOINT_AR,
        EVN_T_PICK_COLOR,
        EVN_T_PICK_NODE_CHANGE,
        EVN_T_PICK_GET_NODE,
        EVN_T_PICK_GET_UI,
        EVN_T_PICK_GET_NOTHING,
        EVN_T_ANIMATE,
        EVN_T_LINK,
        EVN_T_FACESHAPE,
        EVN_T_REDPACKEG_READY,
        EVN_T_REDPACKEG_READY1,
        EVN_T_REDPACKEG_READY2,
        EVN_T_REDPACKEG_CANDYDOWN,
        EVN_T_REDPACKEG_EXPLOSION,
        EVN_T_BOOM_DROP,
        EVN_T_BOOM_EXPLOSION,
        EVN_T_BOOM_EXPLOSION_END,
        EVN_T_REDPACKEG_SHOWGOLD,
        EVN_T_REDPACKEG_GOLDEND,
        EVN_T_REDPACKEG_TOUCH,
        EVN_T_REDPACKEG_COLLECTMONEY,
        EVN_T_EFFECT_MUSIC_LOAD,
        EVN_T_EFFECT_MUSIC_PLAY,
        EVN_T_DICE_RESULT,
        EVN_T_HAS_WHOLE_FACE,
        EVN_T_NO_WHOLE_FACE,
        EVN_T_TIMEOUT,
        EVN_T_PARSE,
        EVN_T_VIDEO_CTRL,
        EVN_T_VIDEO_STATE,
        EVN_T_EXPRESSION_LEFTEYECLOSE,
        EVN_T_EXPRESSION_RIGHTEYECLOSE,
        EVN_T_EXPRESSION_MOUTHOPEN,
        EVN_T_EXPRESSION_MOUTHCLOSE,
        EVN_T_EXPRESSION_HEADTURNLEFT,
        EVN_T_EXPRESSION_HEADTURNRIGHT,
        EVN_T_EXPRESSION_HEADRAISE,
        EVN_T_EXPRESSION_HEADBOW,//低头
        EVN_T_TEX_LOAD_FINISH,
        EVN_T_SAVE_BEGIN,
        EVN_T_SAVE_END,
        EVN_T_MAX = 100
    };
    
    //
    enum TOUCH_ACTION_TYPE {
        TOUCH_ACTION_DOWN,
        TOUCH_ACTION_MOVE,
        TOUCH_ACTION_UP
    };
    
    //
    enum VIDEOCTRL {
        VIDEO_CTRL_NONE,
        VIDEO_CTRL_PLAY,
        VIDEO_CTRL_PAUSE,
        VIDEO_CTRL_STOP,
        VIDEO_CTRL_RESET,
        VIDEO_CTRL_PREVIEW
    };
    
    //
    enum VIDEOSTATE {
        VIDEO_STATE_NONE,
        VIDEO_STATE_LOADBEIGN,
        VIDEO_STATE_LOADEND,
        VIDEO_STATE_PLAYBEGIN,      //视频渲染开始
        VIDEO_STATE_PLAYEND,        //视频渲染完毕
        VIDEO_STATE_SAVEBEGIN,
        VIDEO_STATE_SAVEEND,
        VIDEO_STATE_TMPLATE_LOADOVER    //模板加载完毕
    };

}

#endif //SV_EVENTDEF_H
