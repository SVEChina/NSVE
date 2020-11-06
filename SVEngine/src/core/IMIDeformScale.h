//
//  IMIDeformScale.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/5/9.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_DEFORM_SCALE_H

#include "../base/IMIObject.h"
#include "../base/IMIVec3.h"
#include "../rendercore/IMIRenderMesh.h"

namespace imi {
    
    
        
        class IMIDeformScale :public IMIObject{
            
            public:
            
            IMIDeformScale();
            
            ~IMIDeformScale();
            
            void setSmooth(f32 _smooth);
            
            void pushCtl(f32 x , f32 y, f32 z);
            
            void clearCtl();
            
            FVec2 getScalePostion(const FVec2& _t);
            
            protected:
            f32 m_smooth;
            IMIArray<FVec3> m_controlArray;
            IMILockPtr m_lock;
        };
        
    
    
}//!namespace imi

#endif /* IMI_DEFORM_SCALE_H */
