//
// SVLoaderImage.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_LOADERIMAGE_H
#define SV_LOADERIMAGE_H

#include "SVFileLoader.h"
/*
 */

class SVImage;
/*
 */
namespace sv {
class SVLoaderImage {
public:
    virtual ~SVLoaderImage();
    
    // info image
    static int info(SVImage &_image, cptr8 _name);
    
    // load image
    static int load(SVImage &_image, cptr8 _name);
    static int load(SVImage &_image, cptr8 _name, s32 _offset);
    static int load(SVImage &_image, cptru8 _data, s32 _size);
    
    // save image
    static int save(const SVImage &_image, cptr8 _name, f32 _quality);
};

}//!namespace sv




#endif //SV_LOADERIMAGE_H
