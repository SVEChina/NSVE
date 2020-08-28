//
//  SVFilterLUT.hpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef SV_LOOKUPFILTER_H
#define SV_LOOKUPFILTER_H

#include "SVFilterBase.h"

namespace sv {
    
    // LUT滤镜
    
    class SVFilterLUT : public SVFilterBase {
    public:
        SVFilterLUT(SVInstPtr _app);
        
        ~SVFilterLUT();
        
        virtual bool create();
        
        virtual void destroy();
        
        virtual void update(f32 _dt);
        
        void setLUTTex(SVTexturePtr _looktex);
        
        SVTexturePtr getLUTTex();
        
    protected:
        SVTexturePtr m_texLUT;
        
        bool m_dirtyLUT;
        
    public:
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                                    RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    };

}//!namespace sv


#endif /* SV_LOOKUPFILTER_H */
