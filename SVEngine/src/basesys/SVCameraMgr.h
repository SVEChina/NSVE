//
// SVCameraMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CAMERAMGR_H
#define SV_CAMERAMGR_H

#include "../basesys/SVSysBase.h"
#include "../work/SVWorkDeclare.h"
#include <map>

namespace sv {

    class SVCameraMgr : public SVSysBase {
    public:
        SVCameraMgr(SVInstPtr _app);
        
        ~SVCameraMgr();
        
        void init();
        
        void destroy();

        void update(f32 dt);
        
        void resize(f32 _w,f32 _h);
        
        SVCameraNodePtr createCamera(s32 _cameraID);
        
        void destroyCamera(s32 _cameraID);
        
        SVCameraNodePtr getCamera(s32 _cameraID);
        
        //设置相机绑定
        void bindCamera(SVINTEX _targetID,s32 _cameraID);
        
        //解开相机绑定
        void unbindCamera(SVINTEX _targetID);
        
        //
        SVCameraNodePtr getMainCamera();
        
    protected:
        SVLockSpinPtr m_lock;
        
        //主相机
        SVCameraNodePtr m_main_camera;
        
        //相机
        typedef std::map<s32 ,SVCameraNodePtr> CAMERAPOOL;
        CAMERAPOOL m_camera_pool;
    };
    
}//!namespace




#endif //SV_CAMERAMGR_H
