//
// SVLoaderImage.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_LOADERIMAGE_H
#define SV_LOADERIMAGE_H

#include "SVFileLoader.h"

namespace sv {

    class SVLoaderImage {
    public:
        static s32 check(cptr8 _name);
        
        // load image
        static s32 load(SVInstPtr _app,SVImagePtr _image, cptr8 _name);
        
        static s32 load(SVInstPtr _app,SVImagePtr _image, cptr8 _name, s32 _offset);
        
        static s32 load(SVInstPtr _app,SVImagePtr _image, cptru8 _data, s32 _size);
        
        // save image
        static s32 save(SVInstPtr _app,SVImagePtr _image, cptr8 _name, f32 _quality);
    };

}//!namespace sv




#endif //SV_LOADERIMAGE_H
