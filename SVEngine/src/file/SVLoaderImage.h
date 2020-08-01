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
class SVLoaderImage : public SVFileLoader{
public:
    SVLoaderImage(SVInstPtr _app);
    
    ~SVLoaderImage();
    
    // info image
    s32 info(SVImage &_image, cptr8 _name);
    
    // load image
    s32 load(SVImage &_image, cptr8 _name);
    s32 load(SVImage &_image, cptr8 _name, s32 _offset);
    s32 load(SVImage &_image, cptru8 _data, s32 _size);
    
    // save image
    s32 save(const SVImage &_image, cptr8 _name, f32 _quality);
};

/*
 SVLoaderImagePNG
*/
#include <png.h>
class SVLoaderImagePNG : public SVFileLoader{
public:
    SVLoaderImagePNG(SVInstPtr _app);
    
    ~SVLoaderImagePNG();
    
    // info image
    s32 info(SVImage &_image, cptr8 _name);

    // load image
    s32 load(SVImage &_image, cptr8 _name);
    s32 load(SVImage &_image, cptru8 _data, s32 _size);

    // save image
    s32 save(const SVImage &_image, cptr8 _name);

private:
    s32 _get_info(png_structp _png_ptr,png_infop png_info_ptr, cptr8 _name, png_uint_32 &_width, png_uint_32 &_height, s32 &_format);

    static void _file_read_function(png_structp _png_ptr, png_bytep _ptr, png_size_t _size);

    void _write_function(png_structp _png_ptr, png_bytep _ptr, png_size_t _size);
    void _flush_function(png_structp _png_ptr);

    struct ImageDataSource {
        cptru8 src;
        s32 offset;
        u64 size;
    };
};

}//!namespace sv




#endif //SV_LOADERIMAGE_H
