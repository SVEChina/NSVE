//
// IMIInst.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_INST_H
#define IMI_INST_H

#include "../base/IMIIDPool.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../env/IMIEnvDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../basesys/IMIConfig.h"
#include "IMIGlobalMgr.h"
#include "IMIGlobalParam.h"

namespace imi {
    
    /*
     不用单例的原因，是有些需求，需要启动两个引擎
     */

    LUA_REG_DECLARE(IMIInst);

    class IMIInst : public IMIObject {
    public:
        friend class IMICtxBase;
        friend class std::shared_ptr<IMICtxBase> ;
#ifdef IMI_IOS
        friend class IMICtxIOSGLES;
        friend class std::shared_ptr<IMICtxIOSGLES> ;
        friend class IMICtxIOSMetal;
        friend class std::shared_ptr<IMICtxIOSMetal> ;
#endif

#ifdef IMI_OSX
        friend class IMICtxOSXGL;
        friend class std::shared_ptr<IMICtxOSXGL> ;
        friend class IMICtxOSXMetal;
        friend class std::shared_ptr<IMICtxOSXMetal> ;
#endif
        
#ifdef IMI_ANDRIOD
#endif
        //
        static IMIInstPtr makeCreate();
        //
        IMIInst();
        //
        virtual ~IMIInst();
        //
        IMIInstPtr share();
        
        //初始化IMI(与渲染器无关)
        void init(bool async = false);
        
        //销毁IMI(与渲染器无关)
        void destroy();
        
        //创建环境
        IMICtxBasePtr createEnv(IMI_R_ENV _type);
        
        //销毁环境
        void destroyEnv();
        
        //重置大小
        void resize(s32 _w,s32 _h);

        //设置渲染路径
        void setRenderPath(s32 _rpath);
        
        //增加资源路径
        void addRespath(cptr8 _path);
        
        //清理资源路径
        void clearRespath();
        
        //更新引擎
        void updateIMI(f32 _dt);
        
        //渲染引擎
        void renderIMI();
        
        //清楚缓存
        void clearCache();
        
        //开始IMI
        void start();
        
        //停止IMI
        void stop();
        
        //挂起IMI
        void suspend();
        
        //唤醒IMI
        void resume();
        
        void test();
        
        void inputFrame(u8 *_frameData, s32 _width, s32 _height);
        
        void inputKeyData(u8 *_keyData);
        
        //获取引擎状态
        inline IMI_STATE getState() { return m_sv_st; }
        
    public:
        //唯一ID池
        IMIIDPool m_IDPool;
        //文件部分
        IMIFileMgrPtr m_file_sys;
        //材质库
        IMIMtlLibPtr m_mtl_lib;
        //渲染部分
        IMIRenderMgrPtr m_render_mgr;
        //配置部分
        IMIConfig m_config;
        //脚本系统-lua
        IMILuaSysPtr m_lua_sys;
        //事件系统
        IMIEventMgrPtr m_event_sys;
        //资源管理
        IMIResMgrPtr m_res_mgr;
        //AR背景
        IMIARBackgroundMgrPtr m_ar_mgr;
        //全局对象
        IMIGlobalMgrPtr m_global_mgr;
        //全局参数
        IMIGlobalParam m_global_param;
        //渲染器 renderer
        IMIRendererPtr m_renderer;
        //渲染路径
        IMIRenderPathPtr m_render_path;
        //渲染环境
        IMICtxBasePtr m_ctx;
        //状态
        IMI_STATE m_sv_st;
        //渲染器内核
        IMI_R_ENV m_rcore;
        //
        bool m_async;
        
    public:
        IMIEventMgrPtr getEventMgr();
        IMIBasicSysPtr getBasicSys();
        IMICameraMgrPtr getCameraMgr();
        IMISceneMgrPtr getSceneMgr();
        IMIAniMgrPtr getAniMgr();
        IMILightSysPtr getLightSys();
        IMIModuleSysPtr getModuleSys();
        IMIShaderMgrPtr getShaderMgr();
        IMITexMgrPtr getTexMgr();
        IMIRTargetMgrPtr getTargetMgr();
        IMIMtlLibPtr getMtlLib();
        IMIRenderMgrPtr getRenderMgr();
        IMIRenderPathPtr getRenderPath();
        IMIDetectMgrPtr getDetectMgr();
        IMIDeformMgrPtr getDeformMgr();
        IMIComDataPtr getComData();
        IMIModelMgrPtr getModelMgr();
        IMIPhysicsWorldMgrPtr getPhysicsWorldMgr();
        IMIRendererPtr getRenderer();
        IMIARBackgroundMgrPtr getARBGMgr();
        
    protected:
        
        void _initRenderer(IMIRendererPtr _renderer);
    };
    
}//!namespace imi



#endif //IMI_INST_H
