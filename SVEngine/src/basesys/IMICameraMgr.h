//
// IMICameraMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_CAMERAMGR_H
#define IMI_CAMERAMGR_H

#include "../basesys/IMISysBase.h"
#include "../work/IMIWorkDeclare.h"
#include <map>

namespace imi {

    class IMICameraMgr : public IMISysBase {
    public:
        IMICameraMgr(IMIInstPtr _app);
        
        ~IMICameraMgr();
        
        void init();
        
        void destroy();

        void update(f32 _dt);
        
        void resize(f32 _w,f32 _h);
        
        IMICameraNodePtr createCamera(s32 _cameraID);
        
        void destroyCamera(s32 _cameraID);
        
        IMICameraNodePtr getCamera(s32 _cameraID);
        
        //设置相机绑定
        void bindCamera(IMI_TEXIN _targetID,s32 _cameraID);
        
        //解开相机绑定
        void unbindCamera(IMI_TEXIN _targetID);
        
        //获取主相机
        IMICameraNodePtr getMainCamera();
        
    protected:
        IMILockSpinPtr m_lock;
        
        //主相机
        IMICameraNodePtr m_main_camera;
        
        //相机
        typedef std::map<s32 ,IMICameraNodePtr> CAMERAPOOL;
        CAMERAPOOL m_camera_pool;
    };
    
}//!namespace




#endif //IMI_CAMERAMGR_H
