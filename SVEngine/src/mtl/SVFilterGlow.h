//
//  SVFilterGlow.h
//  SVEngine
//
//  Created by 徐子昱 on 2019/4/22.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef SV_FILTER_GLOW_H
#define SV_FILTER_GLOW_H

#include "SVFilterBase.h"

namespace sv {

    class SVFilterGlow : public SVFilterBase {
    public:
        SVFilterGlow(SVInstPtr _app);
        
        ~SVFilterGlow();
        
        virtual bool create(SV_TEXIN _inType,SV_TEXIN _outType);
        
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
        SVMtlSmoothPtr m_mtl_smooth;
    };

}//!namespace sv


#endif /* SV_FILTER_GLOW_H */
