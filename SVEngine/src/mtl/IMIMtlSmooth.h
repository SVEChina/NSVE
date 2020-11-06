//
//  IMIMtlSmooth.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/3/26.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_MTL_SMOOTH_H
#define IMI_MTL_SMOOTH_H

#include "IMIMtlCore.h"

namespace imi {
    
    class IMIMtlSmooth : public IMIMtlCore {
    public:
        
        IMIMtlSmooth(IMIInstPtr _app , IMIString _name);
        
        IMIMtlSmooth(IMIMtlSmooth *_mtl);
        
        ~IMIMtlSmooth();
        
        virtual IMIMtlCorePtr clone();
        
        
        inline void setSmooth(f32 _smooth){
            m_smooth = _smooth;
        }
        
        inline void setImgWH(f32 _w , f32 _h){
            m_w = _w;
            m_h = _h;
        }
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        
        f32 m_smooth;
        f32 m_w;
        f32 m_h;
    };
    
}//!namespace imi


#endif /* IMI_MTL_SMOOTH_H */
