//
//  IMIMtlShadowMapping.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/9/13.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_MtlSHADOWMAPPING_H
#define IMI_MtlSHADOWMAPPING_H

#include "IMIMtlCore.h"

namespace imi {
    
    class IMIMtlShadowMapping : public IMIMtlCore  {
    public:
        IMIMtlShadowMapping(IMIInstPtr _app);
        
        IMIMtlShadowMapping(IMIMtlShadowMapping* _mtl);
        
        ~IMIMtlShadowMapping();
        
        void setLightVPMat(f32 *_vp);
        
        virtual IMIMtlCorePtr clone();
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        f32 m_LightVPMat[16];

    };
        
}//!namespace imi


#endif /* IMI_MtlSHADOWMAPPING_H */
