//
// SVFilterShinning.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FILTERSHINNING_H
#define SV_FILTERSHINNING_H

#include "SVFilterBase.h"

namespace sv {
    
    class SVFilterShinning : public SVFilterBase {
    public:
        SVFilterShinning(SVInstPtr _app);
        
        ~SVFilterShinning();
        
        virtual bool create();
        
        virtual void destroy();
        
        virtual void update(f32 dt);
        
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);

    };
    
}//!namespace sv


#endif /* SV_FILTERSHINNING_H */
