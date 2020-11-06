//
// IMICameraNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_CAMERANODE_H
#define IMI_CAMERANODE_H

#include "IMINode.h"
#include "../event/IMIEventProc.h"
#include "../work/IMIWorkDeclare.h"

namespace imi {
    
    /*相机节点
     不是节点*/

    class IMICameraNode : public IMIEventProc {
    public:
        IMICameraNode(IMIInstPtr _app);
        
        ~IMICameraNode();
        
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
        IMILockSpinPtr m_res_lock;
        //
        bool m_dirty;
        bool m_is_ortho;
        bool m_active;
    };
    
}//!namespace imi



#endif //IMI_CAMERANODE_H
