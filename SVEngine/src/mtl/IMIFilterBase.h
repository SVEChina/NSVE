//
//  IMIFilterBase.hpp
//  IMIngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef IMI_FILTER_BASE_H
#define IMI_FILTER_BASE_H

#include "../base/IMIGBase.h"
#include "IMIMtlDef.h"
#include "IMIMtlDeclare.h"
#include "IMIMtlLib.h"
#include "IMIMtlCore.h"
#include "IMISurface.h"
#include "IMITexMgr.h"
#include "../node/IMINodeDeclare.h"
#include "../rendercore/IMIRenderDef.h"

namespace imi {
    
    //滤镜基类

    class IMIFilterBase : public IMIGBaseEx {
    public:
        IMIFilterBase(IMIInstPtr _app);

        virtual ~IMIFilterBase();

        virtual bool create();

        virtual void destroy();

        virtual void update(f32 _dt);
        
        //设置使用的target
        sv_inline void setTargetUse(IMI_TEXIN _intex){ m_target_use = _intex; }
        
        //设置Target序列
        sv_inline void setTargetQuene(IMI_TEXIN _intex){ m_target_quene = _intex; }
        
        //设置交换Target
        sv_inline void setTargetSwap(IMI_TEXIN _intex){ m_target_swap = _intex; }
        
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
        
        void setMtl(cptr8 _name);
        
        IMIMtlCorePtr getMtl() {
            return m_mtl;
        }
        
        //获取surface，设置参数
        IMISurfacePtr getSurface() { return m_surface; }

    protected:
        IMIString m_name;
        bool m_is_pre;
        IMI_TEXIN m_target_quene;
        IMI_TEXIN m_target_use;
        IMI_TEXIN m_target_swap;
        IMISurfacePtr m_surface;
        IMIMtlCorePtr m_mtl;
        
    public:
        //序列化
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);

        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    };
    
}//!namespace imi


#endif /* IMI_FILTER_BASE_H */
