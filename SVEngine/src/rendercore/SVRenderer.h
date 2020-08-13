//
// SVRenderer.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERER_BASE_H
#define SV_RENDERER_BASE_H

#include "SVRenderDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "../base/SVGBase.h"
#include "../base/SVMat4.h"
#include "../base/SVArray.h"
#include "../base/SVStack.h"
#include "../core/SVVertDef.h"

//渲染器封装的是算法

namespace sv {

    //
    struct VPParam{
        u32 m_x;
        u32 m_y;
        u32 m_width;
        u32 m_height;
    };

    /*
     渲染内核
     1.渲染资源的创建与销毁
     2.渲染命令的统计（读，写流）
     3.渲染优化（材质排序，批次合并）
     4.渲染状态管理
     5.渲染
     */
    
    class SVRenderer: public SVGBaseEx {
    public:
        SVRenderer(SVInstPtr _app);
        
        ~SVRenderer();
        //初始化
        virtual void init(s32 _w,s32 _h);
        
        //销毁
        virtual void destroy();
        
        //重置大小
        virtual void resize(s32 _w,s32 _h);
        
        //创建资源接口
        //纹理
        virtual SVRTexPtr createResTexture() { return nullptr; }
        
        //shader
        virtual SVRShaderPtr createResShader() { return nullptr; }
        
        //buf-vbo 等
        virtual SVRMeshResPtr createResBuf() { return nullptr; }
        
        //fbo
        virtual SVRFboPtr createResFbo() { return nullptr; }
        
        //create-target
        virtual SVRTargetPtr createTarget(SVINTEX _texid){ return nullptr; }
        
        //增加渲染内核资源
        void addRes(SVRResPtr _res);
        
        //移除渲染内核资源
        void removeRes(SVRResPtr _res);
        
        //清理渲染内核资源
        void clearRes();
        
        virtual void setCurTarget(SVRTargetPtr _target);
    
        //处理材质
        virtual bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface){ return false; }
        
        //处理纹理
        virtual bool processTexture(SVRTexPtr _tex,s32 _chn,s32 _type) { return false; }
        
        //处理mesh
        virtual bool processMesh(SVRenderMeshPtr _mesh){ return false; }
        
        //绘制mesh
        virtual void drawMesh(SVRenderMeshPtr _mesh){ }
        
        //
        virtual void drawScreen(SVINTEX _texid) { }
        
        //自动回收
        virtual void removeUnuseRes();
        
        //获取渲染状态
        SVRenderStatePtr getState();
        
        //重置状态
        void resetState();

    protected:
        //当前的target
        SVRTargetPtr m_cur_target;
        
        //渲染内核资源,起到资源统计和管理的作用
        typedef SVArray<SVRResPtr> ROBJLIST;
        ROBJLIST m_robjList;
        
        //资源锁
        SVLockSpinPtr m_resLock;
        
        //渲染状态
        SVRenderStatePtr m_pRState;
        
        //渲染VP
        SVStack<VPParam,10> m_vpStack;  //viewport堆栈
        
        //inner size
        s32 m_inWidth;
        s32 m_inHeight;
        s32 m_outWidth;
        s32 m_outHeight;
        
    public:
        //提交线宽
        virtual void submitLineWidth(f32 _width){}
        
        //提交点大小
        virtual void submitPointSize(f32 _size){}
        
        //绑定FBO
        virtual void svBindFrameBuffer(u32 _id){}
        
        //清理颜色
        virtual void svBindClearColor(u32 _id){}
        
        //颜色缓存
        virtual void svBindColorBuffer(u32 _id){}
        
        //顶点缓存
        virtual void svBindVertexBuffer(u32 _id){}
        
        //索引缓存
        virtual void svBindIndexBuffer(u32 _id){}

        //视口
        virtual void svPushViewPort(u32 _x,u32 _y,u32 _w,u32 _h);
        
        //退出视口
        virtual void svPopViewPort();
    };
    
}//!namespace sv

//
#endif //SV_RENDERER_BASE_H
