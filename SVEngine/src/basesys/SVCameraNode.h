//
// SVCameraNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CAMERANODE_H
#define SV_CAMERANODE_H

#include "SVNode.h"
#include "../event/SVEventProc.h"
#include "../work/SVWorkDeclare.h"

namespace sv {
    
    /*相机节点
     不是节点*/

    class SVCameraNode : public SVEventProc {
    public:
        SVCameraNode(SVInstPtr _app);
        
        ~SVCameraNode();
        
        //初始化
        void init();
        
        //销毁
        void destroy();
        
        //更新
        void update(f32 _dt);
        
        //强制更新
        void updateForce();
        
        //重制默认矩阵
        void resetDefault();
        
        //设置宽高
        void setSize(f32 w, f32 h);
        
        //设置远近裁剪
        void setZ(f32 _near, f32 _far);

        //设置投影
        void setProject();
        
        //设置正交
        void setOrtho();
        
        void setFovy(f32 _fovy);
        
        FVec3 getPosition();
        
        FMat4 projectMat();
        
        FMat4 viewMat();
        
        FMat4 vpMat();
        
        void active() {
            m_active = true;
        }
        
        void unActive() {
            m_active = false;
        }

        inline void setPos(f32 x, f32 y, f32 z) {
            m_pos.x = x;
            m_pos.y = y;
            m_pos.z = z;
        }
        inline void setUp(f32 x, f32 y, f32 z) {
            m_up.x = x;
            m_up.y = y;
            m_up.z = z;
        }
        inline void setTarget(f32 x, f32 y, f32 z) {
            m_target.x = x;
            m_target.y = y;
            m_target.z = z;
        }
    protected:
        void _updateProj();
        
        //位置
        FVec3 m_pos;
        //向上分量
        FVec3 m_up;
        //目标
        FVec3 m_target;
        //距离
        f32 m_distance;
        //
        f32 m_znear;
        f32 m_zfar;
        f32 m_width;
        f32 m_height;
        f32 m_fovy;
        
        //各种矩阵
        FMat4 m_mat_v;      //视矩阵
        FMat4 m_mat_p;      //投影矩阵
        FMat4 m_mat_vp;
        //
        SVLockSpinPtr m_res_lock;
        //
        bool m_dirty;
        bool m_is_ortho;
        bool m_active;
    };
    
}//!namespace sv



#endif //SV_CAMERANODE_H
