//
//  SVFilterCommon.hpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef SV_FILTER_COMMON_H
#define SV_FILTER_COMMON_H

#include "SVFilterBase.h"

namespace sv {
    
    //公共滤镜，可以替换纹理

    class SVFilterCommon : public SVFilterBase {
    public:
        SVFilterCommon(SVInstPtr _app);

        virtual ~SVFilterCommon();

        virtual bool create();

        virtual void destroy();

        virtual void update(f32 _dt);
        
        //设置材质
        sv_inline void setMtl(cptr8 _name) { m_mtl_name = _name; }

    protected:
        SVString m_mtl_name;
        
    public:
        //序列化
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);

        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    };
    
}//!namespace sv


#endif /* SV_FILTER_COMMON_H */
