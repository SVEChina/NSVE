//
//  IMIMtlGradientMap.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/3/22.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_MTL_GRADIENTMAP_H
#define IMI_MTL_GRADIENTMAP_H

#include "IMIMtlCore.h"

namespace imi {
    
    class IMIMtlGradientMap : public IMIMtlCore  {
    public:
        IMIMtlGradientMap(IMIInstPtr _app);
        
        IMIMtlGradientMap(IMIMtlGradientMap* _mtl);
        
        ~IMIMtlGradientMap();
        
        virtual IMIMtlCorePtr clone();
        
        void setSmooth(f32 _smooth);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_lSmoothSize;
    };
    
}//!namespace imi

#endif /* IMI_MTL_GRADIENTMAP_H */
