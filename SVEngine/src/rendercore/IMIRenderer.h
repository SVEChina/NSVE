//
// IMIRenderer.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERER_BASE_H
#define IMI_RENDERER_BASE_H

#include "IMIRenderDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "../base/IMIGBase.h"
#include "../base/IMIMat4.h"
#include "../base/IMIArray.h"
#include "../base/IMIStack.h"
#include "../base/IMIObjectPool.h"
#include "../core/IMIVertDef.h"

#include <list>
#include <vector>
#include <map>

//渲染器封装的是算法，不应该带有数据，带有对象是合理的

namespace imi {

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

    class IMIRenderer: public IMIGBaseEx {
    public:
        IMIRenderer(IMIInstPtr _app);
        
        virtual ~IMIRenderer();
        
        //初始化
        virtual void init();
        
        //销毁
        virtual void destroy();
        
        //重置大小
        virtual void resize(s32 _w,s32 _h);
        
        virtual void info(){};
        
        //创建纹理资源
        virtual IMIRTexPtr createResTexture() { return nullptr; }
        
        //创建shader资源
        virtual IMIRShaderPtr createResShader() { return nullptr; }
        
        //创建buf资源
        virtual IMIRMeshResPtr createResBuf() { return nullptr; }
        
        //创建fbo资源
        virtual IMIRFboPtr createResFbo() { return nullptr; }
        
        //获取纹理资源
        virtual IMIRTexPtr getResTexture(s32 _uid) const { return nullptr; }
        
        //获取shader资源
        virtual IMIRShaderPtr getResShader(s32 _uid) const { return nullptr; }
        
        //获取buf资源
        virtual IMIRMeshResPtr getResBuf(s32 _uid) const { return nullptr; }
        
        //获取fbo资源
        virtual IMIRFboPtr getResFbo(s32 _uid) const { return nullptr; }
        
        //获取纹理资源
        virtual void destroyResTexture(s32 _uid) {}
        
        //获取shader资源
        virtual void destroyResShader(s32 _uid) {}
        
        //获取buf资源
        virtual void destroyResBuf(s32 _uid) {}
        
        //获取fbo资源
        virtual void destroyResFbo(s32 _uid) {}
        
        //获取内置Taget
        virtual IMIRTargetPtr getTarget(IMI_TEXIN _texid);
        
        //获取内部纹理
        virtual IMITexturePtr getInTexture(IMI_TEXIN _texid);
        
        //交换纹理
        void swapInTexture(IMI_TEXIN _tex1,IMI_TEXIN _tex2);
        
        //设置当前target
        virtual void setCurTarget(IMIRTargetPtr _target);
        
        virtual void bindTarget(s32 _poolid) {}
        
        virtual void unbindTarget(s32 _poolid) {}
    
        //处理材质
        virtual bool processMtl(IMIMtlCorePtr _mtl,IMISurfacePtr _surface){ return false; }
        
        //处理纹理
        virtual bool processTexture(IMIRTexPtr _tex,s32 _chn,s32 _type) { return false; }
        
        //处理mesh
        virtual bool processMesh(IMIRenderMeshPtr _mesh){ return false; }
        
        //绘制mesh
        virtual void drawMesh(IMIRenderMeshPtr _mesh){ }
        
        //绘制屏幕
        virtual void drawScreen(IMI_TEXIN _texid) { }
        
        //绘制人脸
        virtual void debugMesh2d(IMIRenderMeshPtr _mesh) { }
        
        virtual void debugMesh3d(IMIRenderMeshPtr _mesh) {}

    protected:
        //状态
        //当前的target
        IMIRTargetPtr m_cur_target;
        
        //资源锁
        IMILockSpinPtr m_res_lock;
    };
    
}//!namespace imi

//
#endif //IMI_RENDERER_BASE_H
