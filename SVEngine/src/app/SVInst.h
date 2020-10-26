//
// SVInst.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_INST_H
#define SV_INST_H

#include "../base/SVIDPool.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../env/SVEnvDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../basesys/SVConfig.h"
#include "SVGlobalMgr.h"
#include "SVGlobalParam.h"

namespace sv {
    
    /*
     不用单例的原因，是有些需求，需要启动两个引擎
     */

    LUA_REG_DECLARE(SVInst);

    class SVInst : public SVObject {
    public:
        friend class SVCtxBase;
        friend class std::shared_ptr<SVCtxBase> ;
#ifdef SV_IOS
        friend class SVCtxIOSGLES;
        friend class std::shared_ptr<SVCtxIOSGLES> ;
        friend class SVCtxIOSMetal;
        friend class std::shared_ptr<SVCtxIOSMetal> ;
#endif

#ifdef SV_OSX
        friend class SVCtxOSXGL;
        friend class std::shared_ptr<SVCtxOSXGL> ;
        friend class SVCtxOSXMetal;
        friend class std::shared_ptr<SVCtxOSXMetal> ;
#endif
        
#ifdef SV_ANDRIOD
#endif
        //
        static SVInstPtr makeCreate();
        //
        SVInst();
        //
        virtual ~SVInst();
        //
        SVInstPtr share();
        
        //初始化SV(与渲染器无关)
        void init(bool async = false);
        
        //销毁SV(与渲染器无关)
        void destroy();
        
        //创建环境
        SVCtxBasePtr createEnv(SV_R_ENV _type);
        
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
        void updateSVE(f32 _dt);
        
        //渲染引擎
        void renderSVE();
        
        //清楚缓存
        void clearCache();
        
        //开始SV
        void start();
        
        //停止SV
        void stop();
        
        //挂起SV
        void suspend();
        
        //唤醒SV
        void resume();
        
        void test();
        
        void inputFrame(u8 *_frameData, s32 _width, s32 _height);
        
        void inputKeyData(u8 *_keyData);
        
        //获取引擎状态
        inline SV_STATE getState() { return m_sv_st; }
        
    public:
        //唯一ID池
        SVIDPool m_IDPool;
        //文件部分
        SVFileMgrPtr m_file_sys;
        //材质库
        SVMtlLibPtr m_mtl_lib;
        //渲染部分
        SVRenderMgrPtr m_render_mgr;
        //配置部分
        SVConfig m_config;
        //脚本系统-lua
        SVLuaSysPtr m_lua_sys;
        //事件系统
        SVEventMgrPtr m_event_sys;
        //资源管理
        SVResMgrPtr m_res_mgr;
        //AR背景
        SVARBackgroundMgrPtr m_ar_mgr;
        //全局对象
        SVGlobalMgrPtr m_global_mgr;
        //全局参数
        SVGlobalParam m_global_param;
        //渲染器 renderer
        SVRendererPtr m_renderer;
        //渲染环境
        SVCtxBasePtr m_ctx;
        //状态
        SV_STATE m_sv_st;
        //渲染器内核
        SV_R_ENV m_rcore;
        //
        bool m_async;
        
    public:
        SVEventMgrPtr getEventMgr();
        SVBasicSysPtr getBasicSys();
        SVCameraMgrPtr getCameraMgr();
        SVSceneMgrPtr getSceneMgr();
        SVAniMgrPtr getAniMgr();
        SVLightSysPtr getLightSys();
        SVModuleSysPtr getModuleSys();
        SVShaderMgrPtr getShaderMgr();
        SVTexMgrPtr getTexMgr();
        SVRTargetMgrPtr getTargetMgr();
        SVMtlLibPtr getMtlLib();
        SVRenderMgrPtr getRenderMgr();
        SVDetectMgrPtr getDetectMgr();
        SVDeformMgrPtr getDeformMgr();
        SVComDataPtr getComData();
        SVModelMgrPtr getModelMgr();
        SVPhysicsWorldMgrPtr getPhysicsWorldMgr();
        SVRendererPtr getRenderer();
        SVARBackgroundMgrPtr getARBGMgr();
        
    protected:
        
        void _initRenderer(SVRendererPtr _renderer);
    };
    
}//!namespace sv



#endif //SV_INST_H
