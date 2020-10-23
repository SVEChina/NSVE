//
// SVLoaderGLTFEX.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_LOADER_GLTF_EX_H
#define SV_LOADER_GLTF_EX_H

#include "SVFileLoader.h"
#include "../base/SVPreDeclare.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../node/SVNodeDeclare.h"
#include "../base/SVMap.h"
#include "../base/SVArray.h"
#include "../base/svstr.h"
#include "../base/SVMat4.h"
#include "../base/SVDataSwap.h"

namespace sv {
    
    class SVLoaderGLTF : public SVGBaseEx{
    public:
        SVLoaderGLTF(SVInstPtr _app);
        
        ~SVLoaderGLTF();
        
        bool loadFromFile(cptr8 _filename);
    };
    

}//!namespace sv




#endif //SV_LOADER_GLTF_EX_H
