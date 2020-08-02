//
// SVLoaderImage.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVLoaderImage.h"
#include "SVFileMgr.h"
#include "../core/SVImage.h"
#include "../base/SVDataChunk.h"
#include "../mtl/SVTexMgr.h"
#include "../app/SVInst.h"
using namespace sv;
/******************************************************************************\
 *
 * SVLoaderImage
 *
 \******************************************************************************/
SVLoaderImage::SVLoaderImage(SVInstPtr _app)
:SVFileLoader(_app) {
    
}

SVLoaderImage::~SVLoaderImage() {
    
}

s32 SVLoaderImage::info(SVImage &_image, cptr8 _name) {
    
    _image.clear();
    
    cptr8 ext = strrchr(_name,'.');
    
    if(ext && (!strcmp(ext,".tga") || !strcmp(ext,".TGA"))){
        return 0;//SVImageFileTGA::info(image,name);
    }
    if(ext && (!strcmp(ext,".png") || !strcmp(ext,".PNG"))){
        SVLoaderImagePNG loaderPNG(mApp);
        return loaderPNG.info(_image,_name);
    }
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS"))){
       return 0; //SVImageFileDDS::info(image,name);
    }
    return 0;
}

s32 SVLoaderImage::load(SVImage &_image, cptr8 _name) {
    
    _image.clear();
    
    cptr8 ext = strrchr(_name,'.');
    
    if(ext && (!strcmp(ext,".tga") || !strcmp(ext,".TGA"))) return 0; //SVImageFileTGA::load(image,name);
    if(ext && (!strcmp(ext,".jpg") || !strcmp(ext,".JPG"))) return 0;//SVImageFileJPEG::load(image,name);
    if(ext && (!strcmp(ext,".png") || !strcmp(ext,".PNG"))){
        SVLoaderImagePNG loaderPNG(mApp);
        return loaderPNG.load(_image,_name);
    }
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS"))) return 0; //SVImageFileDDS::load(image,name);
    return 0;
}

s32 SVLoaderImage::load(SVImage &_image, cptr8 _name, s32 _offset) {
    
    _image.clear();
    
    cptr8 ext = strrchr(_name,'.');
    
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS"))) return 0;//SVImageFileDDS::load(image,name,offset);
    
    return 0;
}

s32 SVLoaderImage::load(SVImage &_image, cptru8 _data, s32 _size) {
    
    _image.clear();
    
    if(_size > 2 && _data[0] == 0xff && _data[1] == 0xd8) return 0;//SVImageFileJPEG::load(image,data,size);
    if(_size > 3 && _data[0] == 0x89 && _data[1] == 0x50 && _data[2] == 0x4e && _data[3] == 0x47) {
        SVLoaderImagePNG loaderPNG(mApp);
        return loaderPNG.load(_image,_data,_size);
    }
    
    return 0;
}

s32 SVLoaderImage::save(const SVImage &_image, cptr8 _name, f32 _quality) {
    
    if(_image.isLoaded() == 0) {
        return 0;
    }
    
    cptr8 ext = strrchr(_name,'.');
    
    if(ext && (!strcmp(ext,".tga") || !strcmp(ext,".TGA"))) return 0;//SVImageFileTGA::save(image,name);
    if(ext && (!strcmp(ext,".jpg") || !strcmp(ext,".JPG"))) return 0;//SVImageFileJPEG::save(image,name,quality);
    if(ext && (!strcmp(ext,".png") || !strcmp(ext,".PNG"))) return 0;//SVImageFilePNG::save(image,name);
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS"))) return 0;//SVImageFileDDS::save(image,name);
    if(ext && (!strcmp(ext,".psd") || !strcmp(ext,".PSD"))) return 0;//SVImageFilePSD::save(image,name);
    
    return 0;
}

//jpeg tga dds ..


/******************************************************************************\
 *
 * SVLoaderImagePNG
 *
 \******************************************************************************/
/*
 */
SVLoaderImagePNG::SVLoaderImagePNG(SVInstPtr _app)
:SVFileLoader(_app) {
    
}

SVLoaderImagePNG::~SVLoaderImagePNG() {
    
}

//static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length) {
//    ImageDataSource *isource = (ImageDataSource *) png_get_io_ptr(png_ptr);
//    if ((s32) (isource->offset + length) <= isource->size) {
//        memcpy(data, isource->data + isource->offset, length);
//        isource->offset += length;
//    } else {
//        png_error(png_ptr, "pngReaderCallback failed");
//    }
//}

void SVLoaderImagePNG::_file_read_function(png_structp _png_ptr, png_bytep _ptr, png_size_t _size) {
    ImageDataSource *isource = (ImageDataSource *) png_get_io_ptr(_png_ptr);
    if ((s32) (isource->offset + _size) <= isource->size) {
        memcpy(_ptr, isource->src + isource->offset, _size);
        isource->offset += _size;
    } else {
        png_error(_png_ptr, "_file_read_function failed");
    }
}

s32 SVLoaderImagePNG::_get_info(png_structp _png_ptr, png_infop _png_info_ptr, cptr8 _name, png_uint_32 &_width, png_uint_32 &_height, s32 &_format) {
    
    _width = 0;
    _height = 0;
    _format = -1;
    
    s32 bit_depth;
    s32 color_type;
    f64 gamma;
    
    // set png parameters
    png_read_info(_png_ptr, _png_info_ptr);
    png_get_IHDR(_png_ptr, _png_info_ptr, &_width, &_height, &bit_depth, &color_type, 0, 0, 0);
    if(bit_depth < 8) png_set_expand(_png_ptr);
#ifndef USE_BIG_ENDIAN
    if(bit_depth == 16) png_set_swap(_png_ptr);
#endif
    if(color_type == PNG_COLOR_TYPE_PALETTE) png_set_expand(_png_ptr);
    if(png_get_valid(_png_ptr, _png_info_ptr, PNG_INFO_tRNS)) png_set_expand(_png_ptr);
    if(png_get_gAMA(_png_ptr, _png_info_ptr, &gamma)) png_set_gamma(_png_ptr, 2.2, gamma);
    png_read_update_info(_png_ptr, _png_info_ptr);
    png_get_IHDR(_png_ptr, _png_info_ptr, &_width, &_height, &bit_depth, &color_type,0,0,0);
    
    // create image
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth == 8) _format = SV_FORMAT_R8;
    else if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA && bit_depth == 8) _format = SV_FORMAT_RG8;
    else if(color_type == PNG_COLOR_TYPE_RGB && bit_depth == 8) _format = SV_FORMAT_RGB8;
    else if(color_type == PNG_COLOR_TYPE_RGB_ALPHA && bit_depth == 8) _format = SV_FORMAT_RGBA8;
    else if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth == 16) _format = SV_FORMAT_R16;
    else if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA && bit_depth == 16) _format = SV_FORMAT_RG16;
    else if(color_type == PNG_COLOR_TYPE_RGB && bit_depth == 16) _format = SV_FORMAT_RGB16;
    else if(color_type == PNG_COLOR_TYPE_RGB_ALPHA && bit_depth == 16) _format = SV_FORMAT_RGBA16;
    else {
        return 0;
    }
    
    return 1;
}

s32 SVLoaderImagePNG::info(SVImage &_image, cptr8 _name) {
    
    SVDataChunk t_dataChunk;
    bool t_flag = mApp->m_pFileMgr->loadFileContent(&t_dataChunk, _name);
    if (!t_flag) {
        return 0;
    }
    
    png_byte sig[8];
    c8 *png_stream = t_dataChunk.getPointerChar();
    u64 png_streamSize = t_dataChunk.getRealSize();
    c8 *t_p = png_stream;
    s32 t_i = 0;
    while (t_i<8) {
        sig[t_i] = *t_p;
        t_i++;
        t_p++;
    }
    if(!png_check_sig(sig,8)) {
        return 0;
    }
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
    if(png_ptr == NULL) {
        return 0;
    }
    
    png_infop png_info_ptr = png_create_info_struct(png_ptr);
    if(png_info_ptr == NULL) {
        png_destroy_read_struct(&png_ptr,0,0);
        return 0;
    }
    // set the read call back function
    ImageDataSource t_dataSource;
    t_dataSource.src = (u8 *)png_stream;
    t_dataSource.size = png_streamSize;
    t_dataSource.offset = 0;
    
    png_set_read_fn(png_ptr, &t_dataSource, _file_read_function);
    png_set_sig_bytes(png_ptr, 8);
    
    // get info
    s32 format;
    png_uint_32 width;
    png_uint_32 height;
    if(_get_info(png_ptr,png_info_ptr,_name,width,height,format) == 0) {
        png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
        return 0;
    }
    
    // create image
    _image.create2D(width,height,format);
    png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
    return 1;
}

s32 SVLoaderImagePNG::load(SVImage &_image, cptr8 _name) {
    
    SVDataChunk t_dataChunk;
    bool t_flag = mApp->m_pFileMgr->loadFileContent(&t_dataChunk, _name);
    if (!t_flag) {
        return 0;
    }
    
    png_byte sig[8];
    c8 *png_stream = t_dataChunk.getPointerChar();
    u64 png_streamSize = t_dataChunk.getRealSize();
    c8 *t_p = png_stream;
    s32 t_i = 0;
    while (t_i<8) {
        sig[t_i] = *t_p;
        t_i++;
        t_p++;
    }
    if(!png_check_sig(sig,8)) {
        return 0;
    }
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
    if(png_ptr == NULL) {
        return 0;
    }
    
    png_infop png_info_ptr = png_create_info_struct(png_ptr);
    if(png_info_ptr == NULL) {
        png_destroy_read_struct(&png_ptr,0,0);
        return 0;
    }
    
    // set the read call back function
    ImageDataSource t_dataSource;
    t_dataSource.src = (u8 *)png_stream;
    t_dataSource.size = png_streamSize;
    t_dataSource.offset = 0;
    
    png_set_read_fn(png_ptr, &t_dataSource, _file_read_function);
    png_set_sig_bytes(png_ptr, 8);
    
    // get info
    s32 format;
    png_uint_32 width;
    png_uint_32 height;
    if(_get_info(png_ptr,png_info_ptr,_name,width,height,format) == 0) {
        png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
        return 0;
    }
    
    // create image
    _image.create2D(width,height,format);
    
    // read png image
    u8 *data = _image.getPixels2D();
    png_byte **png_rows = new png_byte*[height];
    s32 stride = _image.getWidth() * _image.getPixelSize();
    for(s32 i = 0; i < (s32)height; i++) {
        png_rows[i] = (png_byte*)data + stride * i;
    }
    png_read_image(png_ptr,png_rows);
    png_read_end(png_ptr,NULL);
    png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
    delete [] png_rows;
    return 1;
}

s32 SVLoaderImagePNG::load(SVImage &_image, cptru8 _src, s32 _size) {
    
    if(_src == NULL || _size < 8) {
        return 0;
    }
    
    png_byte sig[8];
    memcpy(sig,_src,8);
    if(!png_check_sig(sig,8)) {
        return 0;
    }
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
    if(png_ptr == NULL) {
        return 0;
    }
    
    png_infop png_info_ptr = png_create_info_struct(png_ptr);
    if(png_info_ptr == NULL) {
        png_destroy_read_struct(&png_ptr,0,0);
        return 0;
    }
    
    ImageDataSource source;
    source.src = _src;
    source.offset = 8;
    source.size = _size;
    
    png_set_read_fn(png_ptr,&source,_file_read_function);
    png_set_sig_bytes(png_ptr,8);
    
    // get info
    int format;
    png_uint_32 width;
    png_uint_32 height;
    if(_get_info(png_ptr,png_info_ptr,"memory",width,height,format) == 0) {
        png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
        return 0;
    }
    
    // create image
    _image.create2D(width,height,format);
    
    // read png image
    u8 *data = _image.getPixels2D();
    png_byte **png_rows = new png_byte*[height];
    s32 stride = _image.getWidth() * _image.getPixelSize();
    for(s32 i = 0; i < (s32)height; i++) {
        png_rows[i] = (png_byte*)data + stride * i;
    }
    png_read_image(png_ptr,png_rows);
    png_read_end(png_ptr,NULL);
    png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
    delete [] png_rows;
    
    return 1;
}

/*
 */
//void ImageFilePNG::write_function(png_structp png_ptr,png_bytep ptr,png_size_t size) {
//    File *file = (File*)png_get_io_ptr(png_ptr);
//    file->write(ptr,sizeof(png_byte),size);
//}

//void ImageFilePNG::flush_function(png_structp png_ptr) {
//    File *file = (File*)png_get_io_ptr(png_ptr);
//    file->flush();
//}

/*
 */
//int ImageFilePNG::save(const Image &image,const char *name) {
//
//    if(image.getType() != Image::IMAGE_2D) {
//        Log::error("ImageFilePNG::save(): bad image type %s\n",image.getTypeName());
//        return 0;
//    }
//
//    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,0,0,0);
//    if(png_ptr == NULL) {
//        Log::error("ImageFilePNG::save(): can't create write struct for \"%s\" file\n",name);
//        return 0;
//    }
//
//    png_infop png_info_ptr = png_create_info_struct(png_ptr);
//    if(png_info_ptr == NULL) {
//        Log::error("ImageFilePNG::save(): can't create info struct for \"%s\" file\n",name);
//        png_destroy_write_struct(&png_ptr,0);
//        return 0;
//    }
//
//    // select format
//    if(image.getFormat() == Image::FORMAT_R8) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),8,PNG_COLOR_TYPE_GRAY,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else if(image.getFormat() == Image::FORMAT_RG8) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),8,PNG_COLOR_TYPE_GRAY_ALPHA,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else if(image.getFormat() == Image::FORMAT_RGB8) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),8,PNG_COLOR_TYPE_RGB,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else if(image.getFormat() == Image::FORMAT_RGBA8) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),8,PNG_COLOR_TYPE_RGB_ALPHA,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else if(image.getFormat() == Image::FORMAT_R16) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),16,PNG_COLOR_TYPE_GRAY,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else if(image.getFormat() == Image::FORMAT_RG16) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),16,PNG_COLOR_TYPE_GRAY_ALPHA,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else if(image.getFormat() == Image::FORMAT_RGB16) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),16,PNG_COLOR_TYPE_RGB,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else if(image.getFormat() == Image::FORMAT_RGBA16) png_set_IHDR(png_ptr,png_info_ptr,image.getWidth(),image.getHeight(),16,PNG_COLOR_TYPE_RGB_ALPHA,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
//    else {
//        Log::error("ImageFilePNG::save(): can't save %s format into the \"%s\" file\n",image.getFormatName(),name);
//        png_destroy_write_struct(&png_ptr,&png_info_ptr);
//        return 0;
//    }
//
//    File file;
//    if(file.open(name,"wb") == 0) {
//        Log::error("ImageFilePNG::save(): can't create \"%s\" file\n",name);
//        return 0;
//    }
//
//    // set png parameters
//    png_set_write_fn(png_ptr,&file,write_function,flush_function);
//    png_write_info(png_ptr,png_info_ptr);
//#ifndef USE_BIG_ENDIAN
//    if(image.isUShortFormat()) png_set_swap(png_ptr);
//#endif
//
//    // write png image
//    png_byte **png_rows = new png_byte*[image.getHeight()];
//    const unsigned char *data = image.getPixels2D();
//    int stride = image.getWidth() * image.getPixelSize();
//    for(int i = 0; i < image.getHeight(); i++) {
//        png_rows[i] = (png_byte*)data + stride * i;
//    }
//    png_write_image(png_ptr,png_rows);
//    png_write_end(png_ptr,png_info_ptr);
//    png_destroy_write_struct(&png_ptr,&png_info_ptr);
//    delete [] png_rows;
//
//    file.close();
//
//    return 1;
//}
//
