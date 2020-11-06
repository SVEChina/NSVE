//
// IMIPass.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PASS_H
#define IMI_PASS_H

#include "../base/IMIGBase.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include <vector>
#include <string>

namespace imi {
    
    //屏幕空间处理
    class IMIPass :public IMIGBaseEx {
    public:
        IMIPass(IMIInstPtr _inst);

        ~IMIPass();
        
        void bindTarget(IMIRTargetPtr _target);
        
        void unbindTarget();

        IMISurfacePtr getSurface() {
            return m_surface;
        }
        
        void setMtl(cptr8 _name) {
            m_mtl_name = _name;
        }
        
        void update(f32 _dt);

    protected:
        IMISurfacePtr m_surface;
        //材质名称
        std::string m_mtl_name;
        //目标target
        IMIRTargetPtr m_target;
    };

};//!namespace imi

#endif /* IMI_PASS_H */
