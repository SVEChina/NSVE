//
// SVRDPStateMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RDPSTATE_METAL_H
#define SV_RDPSTATE_METAL_H

#include "../SVRDPState.h"
#include "SVRenderDeclare.h"
#import <Metal/Metal.h>

namespace sv {

    /*
     render tech metal
     */

    class SVRDPStateMetal : public SVRDPState {
    public:
        SVRDPStateMetal(SVInstPtr _app);
        
        ~SVRDPStateMetal();
        
        void create(SVRendererPtr _renderer);
               
        void destroy(SVRendererPtr _renderer);

        bool active(SVRendererPtr _render);

    };


}//!namespace sv


#endif //SV_RDPSTATE_METAL_H
