//
// IMISpineNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SPINENODE_H
#define IMI_SPINENODE_H

#include "IMINode.h"

struct spAttachment;
struct spSlot;
struct spBone;

//回调
typedef void (*sv_spine_callback)(imi::IMISpineNodePtr _node,void* _obj,s32 _status);

namespace imi {
    
    /*
     2D骨骼动画
     */
    class IMISpineNode : public IMINode {
    public:
        IMISpineNode(IMIInstPtr _app);
        
        ~IMISpineNode();
        
        void update(f32 dt);
        
        void render();
        
        virtual void setAlpha(f32 _alpha);
        
        void setSpine(IMISpinePtr _spine);
        
        IMISpinePtr getSpine();
        
        void clearSpine();
        
        void play(cptr8 _actname);
        
        void addAni(cptr8 _actname);
        
        void pause();
        
        void stop();
        
        void setstate(E_ANISTATE _state);
        
        E_ANISTATE getstate();
        
        cptr8 getCurAniName();
        
        void setCurAniName(cptr8 _name);
        
        void setloop(bool _loop);
        
        bool getloop();
        
        bool isImmediatelyPlay();//是否立即播放
        
        void setSpineCallback(sv_spine_callback _cb,void* _obj);
      
        bool getBonePosition(f32 &px, f32 &py, cptr8 bonename);
        
        bool getBoneScale(f32 &sx, f32 &sy, cptr8 bonename);
        
        bool getBoneRotation(f32 &rotation, cptr8 bonename);
        
        f32 getSlotAlpha(cptr8 bonename);
        
        void setAABBBoxScale(f32 _scale);
        
    protected:
        void _computeAABBBox();
        
        void _spine_start();
        
        void _spine_complete();
        
        void _spine_stop();//spine播完之后spine回调自动触发执行此函数
        
        void _sendAniEvent(cptr8 _eventName);
        
        IMISpinePtr m_spine;
        
        f32 m_aabbBox_scale;
        
        void* m_p_cb_obj;
        
        sv_spine_callback m_spine_callback;
        
        E_ANISTATE m_state;
        
        //序列化属性
        IMIString m_cur_aniname;

        bool m_loop;
        
        bool m_immediatelyPlay;
        
    public:
        //序列化接口
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    };


}//!namespace imi



//
#endif //IMI_SPINENODE_H


