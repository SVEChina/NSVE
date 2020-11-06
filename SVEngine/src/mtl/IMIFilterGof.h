//
//  IMIFilterGof.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/3/27.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_FILTER_GOF_H
#define IMI_FILTER_GOF_H

#include "IMIFilterBase.h"

namespace imi {

    class IMIFilterGof : public IMIFilterBase {
    public:
        IMIFilterGof(IMIInstPtr _app);
        
        ~IMIFilterGof();
        
        virtual bool create();
        
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


#endif /* IMI_FILTER_GOF_H */
