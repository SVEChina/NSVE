//
// SVRDPState.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RSHADER_H
#define SV_RSHADER_H

#include "SVRRes.h"
#include "../base/SVPreDeclare.h"

/*
 渲染资源 一个dp对应的状态
*/

namespace sv {
    
    // 一个draw primitive对应的状态
    // 模版
    // 混合
    // 透明 等

    class SVRDPState: public SVRRes{
    public:
        SVRDPState(SVInstPtr _app);

        virtual ~SVRDPState();

        virtual void create(SVRendererPtr _renderer){}

        virtual void destroy(SVRendererPtr _renderer){}

        virtual bool active(SVRendererPtr _render){ return false; }
        
        virtual s32 process(SVRendererPtr _renderer) { return -1; }
    };
        
}//!namespace sv


#endif /* SV_RSHADER_H */
