//
//  IMIFilterGlow.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/4/22.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_FILTER_GLOW_H
#define IMI_FILTER_GLOW_H

#include "IMIFilterBase.h"

namespace imi {

    class IMIFilterGlow : public IMIFilterBase {
    public:
        IMIFilterGlow(IMIInstPtr _app);
        
        ~IMIFilterGlow();
        
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
        IMIMtlSmoothPtr m_mtl_smooth;
    };

}//!namespace imi


#endif /* IMI_FILTER_GLOW_H */
