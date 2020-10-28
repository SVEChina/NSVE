//
// SVOpCreate.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li，daming Li
//

#ifndef SV_OPERATECREATE_H
#define SV_OPERATECREATE_H


#include "SVOpBase.h"
#include "../rendercore/SVRenderDef.h"
#include "../node/SVNodeDef.h"
#include "../basesys/SVScene.h"
#include "../node/SVSpineNode.h"

namespace sv {
    
    //创建场景OP
    class SVOpCreateScene : public SVOpBase {
    public:
        SVOpCreateScene(SVInstPtr _app, cptr8 name);
        
    protected:
        void _process(f32 dt);
        
        SVString m_scenename;
    };
    
    //删除逻辑场景
    class SVOpDestroyScene : public SVOpBase {
    public:
        SVOpDestroyScene(SVInstPtr _app,cptr8 name);
        
    protected:
        void _process(f32 dt);
        
        SVString m_scenename;
    };
    
    //
    class SVOpCameraControl : public SVOpBase {
    public:
        SVOpCameraControl(SVInstPtr _app, bool bOpen, s32 iResId);
        
        ~SVOpCameraControl();
        
    protected:
        void _process(f32 dt);
        
        bool m_bOpen;
        s32 m_iResId;
    };
    
    //创建天空
    class SVOpCreateSkyDome : public SVOpBase {
    public:
        SVOpCreateSkyDome(SVInstPtr _app, cptr8 pStrPath,s32 resId);
        
        ~SVOpCreateSkyDome();
        
    protected:
        void _process(f32 dt);
        
        SVString m_strPath;
        f32 m_iResId;
    };
    //创建粒子
    class SVOpCreateParticle : public SVOpBase {
    public:
        SVOpCreateParticle(SVInstPtr _app, cptr8 pStrPath);
        
        ~SVOpCreateParticle();
        
    protected:
        void _process(f32 dt);
        
        SVString m_strPath;
    };
    
    //创建特效
    class SVOpCreateEffcet : public SVOpBase {
    public:
        SVOpCreateEffcet(SVInstPtr _app, cptr8 pStrPath);
        
        ~SVOpCreateEffcet();
        
    protected:
        void _process(f32 dt);
        
        SVString m_strPath;
    };
    
    class SVOpTexAttachment: public SVOpBase {
    public:
        SVOpTexAttachment(SVInstPtr _app, cptr8 _strPath, s32 _channel, void * _data, s32 _width, s32 _height);
        
        ~SVOpTexAttachment();
        
    protected:
        void _process(f32 dt);
        
        void * m_data;
        SVString m_strPath;
        s32   m_width;
        s32   m_height;
        s32   m_channel;
    };
    
    //恢复
    class SVOpEngineResume : public SVOpBase {
    public:
        SVOpEngineResume(SVInstPtr _app);
        
        ~SVOpEngineResume();
        
    protected:
        void _process(f32 dt);
    };
    
    //挂起
    class SVOpEngineSuspend : public SVOpBase {
    public:
        SVOpEngineSuspend(SVInstPtr _app);
        
        ~SVOpEngineSuspend();
        
    protected:
        void _process(f32 dt);
    };

    //推送人脸识别点
    class SVOpPushFaceData : public SVOpBase {
    public:
        SVOpPushFaceData(SVInstPtr _app, void *_data);
        
        ~SVOpPushFaceData();
        
    protected:
        void _process(f32 dt);
        
        void *m_data;
    };
    
    //测试操作
    class SVOpCreateTest : public SVOpBase {
    public:
        SVOpCreateTest(SVInstPtr _app);
        
        ~SVOpCreateTest();
        
    protected:
        void _process(f32 dt);
    };
    
    //测试操作
    class SVOpCreateDebugFacePt : public SVOpBase {
    public:
        SVOpCreateDebugFacePt(SVInstPtr _app);
        
        ~SVOpCreateDebugFacePt();
        
    protected:
        void _process(f32 dt);
    };

    class SVOpCreateGameZCMgr : public SVOpBase {
    public:
        SVOpCreateGameZCMgr(SVInstPtr _app);
        
        ~SVOpCreateGameZCMgr();
        
    protected:
        void _process(f32 dt);
    };
}//!namespace sv



#endif //SV_OPERATECREATE_H
