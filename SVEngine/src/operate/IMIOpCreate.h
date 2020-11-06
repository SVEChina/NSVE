//
// IMIOpCreate.h
// IMIngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li，daming Li
//

#ifndef IMI_OPERATECREATE_H
#define IMI_OPERATECREATE_H


#include "IMIOpBase.h"
#include "../rendercore/IMIRenderDef.h"
#include "../node/IMINodeDef.h"
#include "../basesys/IMIScene.h"
#include "../node/IMISpineNode.h"

namespace imi {
    
    //创建场景OP
    class IMIOpCreateScene : public IMIOpBase {
    public:
        IMIOpCreateScene(IMIInstPtr _app, cptr8 name);
        
    protected:
        void _process(f32 dt);
        
        IMIString m_scenename;
    };
    
    //删除逻辑场景
    class IMIOpDestroyScene : public IMIOpBase {
    public:
        IMIOpDestroyScene(IMIInstPtr _app,cptr8 name);
        
    protected:
        void _process(f32 dt);
        
        IMIString m_scenename;
    };
    
    //
    class IMIOpCameraControl : public IMIOpBase {
    public:
        IMIOpCameraControl(IMIInstPtr _app, bool bOpen, s32 iResId);
        
        ~IMIOpCameraControl();
        
    protected:
        void _process(f32 dt);
        
        bool m_bOpen;
        s32 m_iResId;
    };
    
    //创建天空
    class IMIOpCreateSkyDome : public IMIOpBase {
    public:
        IMIOpCreateSkyDome(IMIInstPtr _app, cptr8 pStrPath,s32 resId);
        
        ~IMIOpCreateSkyDome();
        
    protected:
        void _process(f32 dt);
        
        IMIString m_strPath;
        f32 m_iResId;
    };
    //创建粒子
    class IMIOpCreateParticle : public IMIOpBase {
    public:
        IMIOpCreateParticle(IMIInstPtr _app, cptr8 pStrPath);
        
        ~IMIOpCreateParticle();
        
    protected:
        void _process(f32 dt);
        
        IMIString m_strPath;
    };
    
    //创建特效
    class IMIOpCreateEffcet : public IMIOpBase {
    public:
        IMIOpCreateEffcet(IMIInstPtr _app, cptr8 pStrPath);
        
        ~IMIOpCreateEffcet();
        
    protected:
        void _process(f32 dt);
        
        IMIString m_strPath;
    };
    
    class IMIOpTexAttachment: public IMIOpBase {
    public:
        IMIOpTexAttachment(IMIInstPtr _app, cptr8 _strPath, s32 _channel, void * _data, s32 _width, s32 _height);
        
        ~IMIOpTexAttachment();
        
    protected:
        void _process(f32 dt);
        
        void * m_data;
        IMIString m_strPath;
        s32   m_width;
        s32   m_height;
        s32   m_channel;
    };
    
    //恢复
    class IMIOpEngineResume : public IMIOpBase {
    public:
        IMIOpEngineResume(IMIInstPtr _app);
        
        ~IMIOpEngineResume();
        
    protected:
        void _process(f32 dt);
    };
    
    //挂起
    class IMIOpEngineSuspend : public IMIOpBase {
    public:
        IMIOpEngineSuspend(IMIInstPtr _app);
        
        ~IMIOpEngineSuspend();
        
    protected:
        void _process(f32 dt);
    };

    //推送人脸识别点
    class IMIOpPushFaceData : public IMIOpBase {
    public:
        IMIOpPushFaceData(IMIInstPtr _app, void *_data);
        
        ~IMIOpPushFaceData();
        
    protected:
        void _process(f32 dt);
        
        void *m_data;
    };
    
    //测试操作
    class IMIOpCreateTest : public IMIOpBase {
    public:
        IMIOpCreateTest(IMIInstPtr _app);
        
        ~IMIOpCreateTest();
        
    protected:
        void _process(f32 dt);
    };
    
    //测试操作
    class IMIOpCreateDebugFacePt : public IMIOpBase {
    public:
        IMIOpCreateDebugFacePt(IMIInstPtr _app);
        
        ~IMIOpCreateDebugFacePt();
        
    protected:
        void _process(f32 dt);
    };

    class IMIOpCreateGameZCMgr : public IMIOpBase {
    public:
        IMIOpCreateGameZCMgr(IMIInstPtr _app);
        
        ~IMIOpCreateGameZCMgr();
        
    protected:
        void _process(f32 dt);
    };
}//!namespace imi



#endif //IMI_OPERATECREATE_H
