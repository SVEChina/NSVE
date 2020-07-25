//
// SVRDPStateGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_DPSTATE_GL_H
#define SV_DPSTATE_GL_H

#include "../SVRDPState.h"
#include "../SVRenderDeclare.h"

namespace sv {

    /*
     render dpstate gl
     */

    class SVRDPStateGL : public SVRDPState {
    public:
        SVRDPStateGL(SVInstPtr _app);
        
        ~SVRDPStateGL();
    };


}//!namespace sv


#endif //SV_DPSTATE_GL_H
