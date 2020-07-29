//
// SVCameraNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CAMERANODE_H
#define SV_CAMERANODE_H

#include "SVNode.h"

namespace sv {
    
    /*相机节点
     不是节点*/

    class SVCameraNode : public SVEventProc {
    public:
        SVCameraNode(SVInstPtr _app);
        
        ~SVCameraNode();
        
        void init();
        
        void destroy();
        
        //更新
        void update(f32 _dt);
        
        //重制默认矩阵
        void resetDefault();
        
        //重制
        virtual void resetSize(f32 w, f32 h);

        void setZ(f32 _near, f32 _far);
        
        f32 *getProjectMat();
        
        f32 *getCameraMat();
        
        f32 *getVPMat();
        
        FVec3& getPosition();
        
        FMat4& getProjectMatObj();
        
        FMat4& getViewMatObj();
        
        FMat4& getVPMatObj();

        virtual void updateViewProj();

        //
        void setProject();
        
        void setOrtho();
        
    protected:
        //马上更新
        void _updateForce();

        //
        FVec3 m_pos;
        //
        f32 m_znear;
        f32 m_zfar;
        f32 m_width;
        f32 m_height;
        f32 m_fovy;
        //各种矩阵
        FMat4 m_mat_v;      //视矩阵
        FMat4 m_mat_p;      //投影矩阵
        FMat4 m_mat_vp;     //乘积
        //
        SVLockPtr m_resLock;
        //
        bool m_dirty;
        bool m_is_ortho;
    };
    

    
    
}//!namespace sv



#endif //SV_CAMERANODE_H
