//
// IMILightSys.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_LIGHTSYS_H
#define IMI_LIGHTSYS_H

#include "../basesys/IMISysBase.h"
#include "../base/IMIVec3.h"

namespace imi {
    
    class IMILightSys : public IMISysBase {
    public:
        IMILightSys(IMIInstPtr _app);
        
        ~IMILightSys();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
        IMICameraNodePtr getCamera();
        
    public:
        FVec3 m_g_ambient;      //全局环境光
        FVec3 m_g_diffuse;      //全局漫反射
        FVec3 m_g_specular;     //全局高光
        FVec3 m_g_direction;    //光向
        f32 m_g_diffuse_sc;     //满反射颜色缩放值
        IMICameraNodePtr m_pLightCamera;
    };

}//!namespace imi


#endif //IMI_LIGHTSYS_H
