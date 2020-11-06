//
//  IMIFilterBlur.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/4/27.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_FILTER_BLUR_H
#define IMI_FILTER_BLUR_H

#include "IMIFilterBase.h"

namespace imi {
    
    class IMIFilterBlur : public IMIFilterBase {
    public:
        IMIFilterBlur(IMIInstPtr _app);
        
        ~IMIFilterBlur();
        
        virtual bool create(IMI_TEXIN _inType,IMI_TEXIN _outType);
        
        virtual void destroy();
        
        virtual void update(f32 dt);
        
        inline void setSmooth(f32 smooth){
            m_smooth = smooth;
        }
        
        
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
    protected:
        f32 m_smooth;
        IMIMtlSmoothPtr m_lkMtl01;
        IMIMtlSmoothPtr m_lkMtl02;
    };
        
}//!namespace imi

#endif /* IMI_FILTER_BLUR_H */
