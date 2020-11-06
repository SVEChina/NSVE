//
// IMILoaderImage.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_LOADERIMAGE_H
#define IMI_LOADERIMAGE_H

#include "IMIFileLoader.h"

namespace imi {

    class IMILoaderImage {
    public:
        static s32 check(cptr8 _name);
        
        // load image
        static s32 load(IMIInstPtr _app,IMIImagePtr _image, cptr8 _name);
        
        static s32 load(IMIInstPtr _app,IMIImagePtr _image, cptr8 _name, s32 _offset);
        
        static s32 load(IMIInstPtr _app,IMIImagePtr _image, cptru8 _data, s32 _size);
        
        // save image
        static s32 save(IMIInstPtr _app,IMIImagePtr _image, cptr8 _name, f32 _quality);
    };

}//!namespace imi




#endif //IMI_LOADERIMAGE_H
