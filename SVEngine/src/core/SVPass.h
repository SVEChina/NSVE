//
// SVPass.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PASS_H
#define SV_PASS_H

#include "../base/SVGBase.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include <vector>
#include <string>

namespace sv {
    
    //屏幕空间处理

    class SVPass :public SVGBaseEx {
    public:
        SVPass(SVInstPtr _inst);

        ~SVPass();

        SVSurfacePtr getSurface() {
            return m_surface;
        }
        
        void setMtl(cptr8 _name) {
            m_mtl_name = _name;
        }
        
        void update(f32 _dt);

    protected:
        SVSurfacePtr m_surface;
        //材质名称
        std::string m_mtl_name;
        //目标target
        s32 m_target;
    };

};//!namespace sv

#endif /* SV_PASS_H */
