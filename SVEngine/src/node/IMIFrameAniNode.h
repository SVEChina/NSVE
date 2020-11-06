//
// IMIFrameAniNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FRAMEANI_NODE_H
#define IMI_FRAMEANI_NODE_H

#include "IMINode.h"
#include "../base/IMIMap.h"
//回调
typedef void (*sv_frameani_callback)(imi::IMIFrameAniNodePtr _node,void* _obj,s32 _status);

namespace imi {
    
    /*
     帧动画节点
     */

    class IMIFrameAniNode : public IMINode {
    private:
        struct FrameTex {
            IMITexturePtr m_pTex;
            IMIString m_pTexName;
            s32 m_index;
        };
        
    public:
        IMIFrameAniNode(IMIInstPtr _app);
        
        ~IMIFrameAniNode();
        
        //
        void setSize(f32 _w,f32 _h);
        
        f32 getWidth();

        f32 getHeight();
        
        //更新
        virtual void update(f32 dt);

        //渲染
        virtual void render();
        
        //播放控制
        void play();
        
        void pause();
        
        void stop();
        
        void pushFrame(cptr8 _texname);
        
        void clearFrame();

        void setCallback(sv_frameani_callback _cb,void* _obj);
        
        void setTexPrename(cptr8 _prename);
        
        cptr8 getTexPrename();
        
        void setTotalTime(f32 _time);
        
        f32  getTotlaTime();
        
        void setFrameCount(s32 _count);
        
        s32  getFrameCount();
        
        void setLoop(bool _loop);
        
        bool getLoop();
        //序列化接口
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    protected:
        void _complete();
        IMITexturePtr _selectTex(f32 _time);
        
        void _preload();    //预加载
        
        void _unload();     //卸载
        
        typedef IMIArray<FrameTex> FRAMEPOOL;
        FRAMEPOOL m_framePool;
        
        E_ANISTATE m_state;
        f32 m_accTime;
        f32 m_totalTime;
        f32 m_frameRate;
        f32 m_width;
        f32 m_height;
        s32 m_framecount;
        IMIString m_texprename;
        bool m_loop;
        bool m_preloadframe;        //预加载的帧数
        
        s32 m_curFrame; //当前帧
        s32 m_aimFrame; //目标帧
        s32 m_preFrame; //预先帧
        
        IMITexturePtr m_pActTex;
        IMIRenderMeshPtr m_pMesh;
        
        void* m_p_cb_obj;
        
        sv_frameani_callback m_frameani_callback;
    };

}//!namespace imi

//
#endif //IMI_FRAMEANI_NODE_H


