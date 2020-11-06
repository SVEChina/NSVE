//
// IMIEvent.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_EVENT_H
#define IMI_EVENT_H

#include "../base/IMIObject.h"
#include "IMIEventDef.h"
#include "../node/IMINodeDeclare.h"
#include "../rendercore/IMIRenderDeclare.h"

namespace imi {

    class IMIEvent : public IMIObject {
    public:
        IMIEvent();
        
        IMIEvent(IMI_EVENT_TYPE _type);
        
        virtual ~IMIEvent();
        
        virtual bool isEqual(IMIEventPtr _event);
        
        //是否为系统消息
        bool isSys() {
            if( (eventType>=EVN_T_SYS_BEGIN) && (eventType<=EVN_T_SYS_END)) {
                return true;
            }
            return false;
        }
        
        IMI_EVENT_TYPE eventType;      //消息类型
        IMIString eventName;          //消息名称
    };

    //渲染器初始化消息
    class IMIvtRenderInit : public IMIEvent {
    public:
        IMIvtRenderInit(IMIRendererPtr _obj);
        
        ~IMIvtRenderInit();
        
        IMIRendererPtr m_renderer;
    };
    
    //回收事件
    class IMIvtRecycle : public IMIEvent {
    public:
        IMIvtRecycle();
        
        IMIObjectPtr m_obj;
    };
    
    //
    class IMIPersonEvent : public IMIEvent {
    public:
        IMIPersonEvent();
        
        ~IMIPersonEvent();
        
        bool isEqual(IMIEventPtr _event);
        
        s32 personID;         //关联人物
    };
    
    //
    class IMIFaceShapeEvent : public IMIEvent {
    public:
        IMIFaceShapeEvent();
        
        ~IMIFaceShapeEvent();
        
        s32 m_faceSmooth;
        s32 m_eyeSmooth;
    };
    
    class IMIAnimateEvent : public IMIPersonEvent {
    public:
        IMIAnimateEvent();
        
        bool isEqual(IMIEventPtr _event);
        
        s32 resid;
        s32 uid;
        IMIString m_AnimateName;
    };
    
    class IMIParseEvent : public IMIEvent {
    public:
        IMIParseEvent();
        
        ~IMIParseEvent();
        
        bool isloadEffect;
        s32 resid;
        IMIString screenName;
    };
    
    //
    class IMIPickGetEvent : public IMIEvent {
    public:
        IMIPickGetEvent(IMINodePtr _node);
        
        ~IMIPickGetEvent();
        
        IMINodePtr m_pNode;
    };
    class IMIPickGetUIEvent : public IMIEvent {
    public:
        IMIPickGetUIEvent(IMINodePtr _node);
       
        ~IMIPickGetUIEvent();
       
        IMINodePtr m_pNode;
    };
    //
    class IMIPickGetNothingEvent : public IMIEvent {
    public:
        IMIPickGetNothingEvent();
        
        ~IMIPickGetNothingEvent();
        
        f32 m_px;
        
        f32 m_py;
    };
    //
    class IMIPickLoseEvent : public IMIEvent {
    public:
        IMIPickLoseEvent(IMINodePtr _node);
        
        ~IMIPickLoseEvent();
        
        IMINodePtr m_pNode;
    };
    
    //
    class IMIPickChangeEvent : public IMIEvent {
    public:
        IMIPickChangeEvent(IMINodePtr _getnode,IMINodePtr _losenode);
        
        ~IMIPickChangeEvent();
        
        IMINodePtr m_pLastNode;
        IMINodePtr m_pNewNode;
    };
    
    class IMIRedPacketEvent : public IMIEvent {
    public:
        IMIRedPacketEvent();
        
        ~IMIRedPacketEvent();
    };
    //
    class IMIffectMusicEvent : public IMIEvent {
    public:
        IMIffectMusicEvent();
        
        ~IMIffectMusicEvent();
        
        IMIString path;
    };
    
    class IMIEventPersonExpression : public IMIEvent {
    public:
        IMIEventPersonExpression();
        
        ~IMIEventPersonExpression();
        
        s32 m_personID;
    };
    
}//!namespace imi


#endif //IMI_EVENT_H
