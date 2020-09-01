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

    class SVInst : public SVObject {
    public:
        //
        static SVInstPtr makeCreate();
        //
        SVInst();
        //
        virtual ~SVInst();
        //
        SVInstPtr share();
        //初始化SV
        void init();
        //销毁SV
        void destroy();
        //重置大小
        void resize(s32 _w,s32 _h);
        //创建环境
        SVCtxBasePtr createEnv(SV_R_ENV _type);
        //销毁渲染器
        void destroyEnv();
        //设置渲染器
        void setRenderer(SVRendererPtr _renderer);
        //设置渲染路径
        void setRenderPath(s32 _rpath);
        //开始SV
        void start();
        //停止SV
        void stop();
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
        //挂起SV
        void svSuspend();
        //唤醒SV
        void svResume();
        //设置时间状态
        void setTimeState(SV_ENG_TIMESTATE _mode);
        //获取时间状态
        SV_ENG_TIMESTATE getTimeState();
        //获取引擎状态
        inline SV_STATE getState() { return m_svst; }
        
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
        //全局对象
        SVGlobalMgrPtr m_pGlobalMgr;
        //全局参数
        SVGlobalParam m_global_param;
        //渲染器 renderer
        SVRendererPtr m_renderer;
        //渲染环境
        SVCtxBasePtr m_ctx;
        //
        SV_STATE m_svst;
        //渲染器内核
        SV_R_ENV m_rcore;
        //
        SV_ENG_TIMESTATE m_engTimeState;
        
    public:
        SVEventMgrPtr getEventMgr();
        SVBasicSysPtr getBasicSys();
        SVCameraMgrPtr getCameraMgr();
        SVSceneMgrPtr getSceneMgr();
        SVLightSysPtr getLightSys();
        SVModuleSysPtr getModuleSys();
        SVShaderMgrPtr getShaderMgr();
        SVTexMgrPtr getTexMgr();
        SVMtlLibPtr getMtlLib();
        SVRenderMgrPtr getRenderMgr();
        SVDetectMgrPtr getDetectMgr();
        SVDeformMgrPtr getDeformMgr();
        SVComDataPtr getComData();
        SVModelMgrPtr getModelMgr();
        SVPhysicsWorldMgrPtr getPhysicsWorldMgr();
        SVRendererPtr getRenderer();
    };
    
}//!namespace sv



#endif //SV_INST_H
