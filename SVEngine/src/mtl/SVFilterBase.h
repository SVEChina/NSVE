//
//  SVFilterBase.hpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef SV_FILTER_BASE_H
#define SV_FILTER_BASE_H

#include "../base/SVGBase.h"
#include "SVMtlDef.h"
#include "SVMtlDeclare.h"
#include "SVMtlLib.h"
#include "SVMtlCore.h"
#include "SVSurface.h"
#include "SVTexMgr.h"
#include "../node/SVNodeDeclare.h"
#include "../rendercore/SVRenderDef.h"

namespace sv {
    
    //滤镜基类

    class SVFilterBase : public SVGBaseEx {
    public:
        SVFilterBase(SVInstPtr _app);

        virtual ~SVFilterBase();

        virtual bool create();

        virtual void destroy();

        virtual void update(f32 _dt);
        
        //设置目标Target
        sv_inline void setTarget(SV_TEXIN _intex){ m_target_tex = _intex; }
        
        //设置预处理
        sv_inline void setPreProcess() { m_is_pre = true; }
        
        //设置后处理
        sv_inline void setPostProcess() { m_is_pre = false; }
        
        sv_inline void setName(cptr8 _name) {
            m_name = _name;
        }

        sv_inline cptr8 getName(){
            return m_name.c_str();
        }
        
        //获取surface，设置参数
        SVSurfacePtr getSurface() { return m_surface; }

    protected:
        SVString m_name;
        bool m_is_pre;
        SV_TEXIN m_target_tex;
        SV_TEXIN m_target_tex_help;
        SVSurfacePtr m_surface;
        SVMtlCorePtr m_mtl;
        
    public:
        //序列化
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);

        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    };
    
}//!namespace sv


#endif /* SV_FILTER_BASE_H */
