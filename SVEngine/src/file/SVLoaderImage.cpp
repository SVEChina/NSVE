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
SVLoaderImage::~SVLoaderImage() {
    
}

s32 SVLoaderImage::info(SVImage &_image, cptr8 _name) {
    
    _image.clear();
    
    cptr8 ext = strrchr(_name,'.');
    
    if(ext && (!strcmp(ext,".tga") || !strcmp(ext,".TGA")))
        return 0;//SVImageFileTGA::info(image,name);
    if(ext && (!strcmp(ext,".png") || !strcmp(ext,".PNG"))) return 0; //SVImageFilePNG::info(image,name);
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS"))) return 0; //SVImageFileDDS::info(image,name);
    
    return 0;
}

s32 SVLoaderImage::load(SVImage &_image, cptr8 _name) {
    
    _image.clear();
    
    cptr8 ext = strrchr(_name,'.');
    
    if(ext && (!strcmp(ext,".tga") || !strcmp(ext,".TGA"))) return 0; //SVImageFileTGA::load(image,name);
    if(ext && (!strcmp(ext,".jpg") || !strcmp(ext,".JPG"))) return 0;//SVImageFileJPEG::load(image,name);
    if(ext && (!strcmp(ext,".png") || !strcmp(ext,".PNG"))) return 0;//SVImageFilePNG::load(image,name);
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
    if(_size > 3 && _data[0] == 0x89 && _data[1] == 0x50 && _data[2] == 0x4e && _data[3] == 0x47) return 0;// SVImageFilePNG::load(image,data,size);
    
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
 * ImageFilePNG
 *
 \******************************************************************************/
#include <png.h>
/*
 */
//
//class SVLoaderImagePNG {
//
//    SVLoaderImagePNG();
//
//public:
//
//    // info image
//    static int info(SVImage &_image, cptr8 _name);
//
//    // load image
//    static int load(SVImage &_image, cptr8 _name);
//    static int load(SVImage &_image, cptru8 _data, s32 _size);
//
//    // save image
//    static int save(const SVImage &_image, cptr8 _name);
//
//private:
//
//    static int get_info(png_structp png_ptr,png_infop png_info_ptr,const char *name,png_uint_32 &width,png_uint_32 &height,int &format);
//
//    static void file_read_function(png_structp png_ptr,png_bytep ptr,png_size_t size);
//
//    static void data_read_function(png_structp png_ptr,png_bytep ptr,png_size_t size);
//
//    static void write_function(png_structp png_ptr,png_bytep ptr,png_size_t size);
//    static void flush_function(png_structp png_ptr);
//
//    struct DataSource {
//        const unsigned char *src;
//        int offset;
//        int size;
//    };
//};
//
//SVLoaderImagePNG::SVLoaderImagePNG() {
//
//}
//
//void SVLoaderImagePNG::file_read_function(png_structp png_ptr,png_bytep ptr,png_size_t size) {
////    File *file = (File*)png_get_io_ptr(png_ptr);
////    file->read(ptr,sizeof(png_byte),size);
//}
//
//s32 SVLoaderImagePNG::get_info(png_structp png_ptr,png_infop png_info_ptr,cptr8 _name,png_uint_32 &width,png_uint_32 &height,int &format) {
//
//    width = 0;
//    height = 0;
//    format = -1;
//
//    int bit_depth;
//    int color_type;
//    double gamma;
//
//    // set png parameters
//    png_read_info(png_ptr,png_info_ptr);
//    png_get_IHDR(png_ptr,png_info_ptr,&width,&height,&bit_depth,&color_type,0,0,0);
//    if(bit_depth < 8) png_set_expand(png_ptr);
//#ifndef USE_BIG_ENDIAN
//    if(bit_depth == 16) png_set_swap(png_ptr);
//#endif
//    if(color_type == PNG_COLOR_TYPE_PALETTE) png_set_expand(png_ptr);
//    if(png_get_valid(png_ptr,png_info_ptr,PNG_INFO_tRNS)) png_set_expand(png_ptr);
//    if(png_get_gAMA(png_ptr,png_info_ptr,&gamma)) png_set_gamma(png_ptr,2.2,gamma);
//    png_read_update_info(png_ptr,png_info_ptr);
//    png_get_IHDR(png_ptr,png_info_ptr,&width,&height,&bit_depth,&color_type,0,0,0);
//
//    // create image
//    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth == 8) format = Image::FORMAT_R8;
//    else if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA && bit_depth == 8) format = Image::FORMAT_RG8;
//    else if(color_type == PNG_COLOR_TYPE_RGB && bit_depth == 8) format = Image::FORMAT_RGB8;
//    else if(color_type == PNG_COLOR_TYPE_RGB_ALPHA && bit_depth == 8) format = Image::FORMAT_RGBA8;
//    else if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth == 16) format = Image::FORMAT_R16;
//    else if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA && bit_depth == 16) format = Image::FORMAT_RG16;
//    else if(color_type == PNG_COLOR_TYPE_RGB && bit_depth == 16) format = Image::FORMAT_RGB16;
//    else if(color_type == PNG_COLOR_TYPE_RGB_ALPHA && bit_depth == 16) format = Image::FORMAT_RGBA16;
//    else {
//        Log::error("ImageFilePNG::get_info(): unsupported format %d %d in \"%s\" file\n",color_type,bit_depth,name);
//        return 0;
//    }
//
//    return 1;
//}
//
///*
// */
//int ImageFilePNG::info(Image &image,const char *name) {
//
//    File file;
//    if(file.open(name,"rb") == 0) {
//        Log::error("ImageFilePNG::info(): can't open \"%s\" file\n",name);
//        return 0;
//    }
//
//    png_byte sig[8];
//    file.read(sig,sizeof(png_byte),8);
//    if(!png_check_sig(sig,8)) {
//        Log::error("ImageFilePNG::info(): wrong signature in \"%s\" file\n",name);
//        file.close();
//        return 0;
//    }
//
//    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
//    if(png_ptr == NULL) {
//        Log::error("ImageFilePNG::info(): can't create read struct for \"%s\" file\n",name);
//        file.close();
//        return 0;
//    }
//
//    png_infop png_info_ptr = png_create_info_struct(png_ptr);
//    if(png_info_ptr == NULL) {
//        Log::error("ImageFilePNG::info(): can't create info struct for \"%s\" file\n",name);
//        png_destroy_read_struct(&png_ptr,0,0);
//        file.close();
//        return 0;
//    }
//
//    png_set_read_fn(png_ptr,&file,file_read_function);
//    png_set_sig_bytes(png_ptr,8);
//
//    // get info
//    int format;
//    png_uint_32 width;
//    png_uint_32 height;
//    if(get_info(png_ptr,png_info_ptr,name,width,height,format) == 0) {
//        png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
//        file.close();
//        return 0;
//    }
//
//    // create image
//    image.create2D(width,height,format,1,0,0);
//    png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
//
//    file.close();
//
//    return 1;
//}
//
///*
// */
//int ImageFilePNG::load(Image &image,const char *name) {
//
//    File file;
//    if(file.open(name,"rb") == 0) {
//        Log::error("ImageFilePNG::load(): can't open \"%s\" file\n",name);
//        return 0;
//    }
//
//    png_byte sig[8];
//    file.read(sig,sizeof(png_byte),8);
//    if(!png_check_sig(sig,8)) {
//        Log::error("ImageFilePNG::load(): wrong signature in \"%s\" file\n",name);
//        file.close();
//        return 0;
//    }
//
//    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
//    if(png_ptr == NULL) {
//        Log::error("ImageFilePNG::load(): can't create read struct for \"%s\" file\n",name);
//        file.close();
//        return 0;
//    }
//
//    png_infop png_info_ptr = png_create_info_struct(png_ptr);
//    if(png_info_ptr == NULL) {
//        Log::error("ImageFilePNG::load(): can't create info struct for \"%s\" file\n",name);
//        png_destroy_read_struct(&png_ptr,0,0);
//        file.close();
//        return 0;
//    }
//
//    png_set_read_fn(png_ptr,&file,file_read_function);
//    png_set_sig_bytes(png_ptr,8);
//
//    // get info
//    int format;
//    png_uint_32 width;
//    png_uint_32 height;
//    if(get_info(png_ptr,png_info_ptr,name,width,height,format) == 0) {
//        png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
//        file.close();
//        return 0;
//    }
//
//    // create image
//    image.create2D(width,height,format,1,0);
//
//    // read png image
//    unsigned char *data = image.getPixels2D();
//    png_byte **png_rows = new png_byte*[height];
//    int stride = image.getWidth() * image.getPixelSize();
//    for(int i = 0; i < (int)height; i++) {
//        png_rows[i] = (png_byte*)data + stride * i;
//    }
//    png_read_image(png_ptr,png_rows);
//    png_read_end(png_ptr,NULL);
//    png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
//    delete [] png_rows;
//
//    file.close();
//
//    return 1;
//}
//
///*
// */
//void ImageFilePNG::data_read_function(png_structp png_ptr,png_bytep ptr,png_size_t size) {
//    DataSource *source = (DataSource*)png_get_io_ptr(png_ptr);
//    assert(source->offset + (int)size <= source->size && "ImageFilePNG::data_read_function(): wrong data");
//    memcpy(ptr,source->src + source->offset,size);
//    source->offset += (int)size;
//}
//
///*
// */
//int ImageFilePNG::load(Image &image,const unsigned char *src,int size) {
//
//    if(src == NULL || size < 8) {
//        Log::error("ImageFilePNG::load(): wrong source\n");
//        return 0;
//    }
//
//    png_byte sig[8];
//    memcpy(sig,src,8);
//    if(!png_check_sig(sig,8)) {
//        Log::error("ImageFilePNG::load(): wrong signature\n");
//        return 0;
//    }
//
//    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
//    if(png_ptr == NULL) {
//        Log::error("ImageFilePNG::load(): can't create read struct\n");
//        return 0;
//    }
//
//    png_infop png_info_ptr = png_create_info_struct(png_ptr);
//    if(png_info_ptr == NULL) {
//        Log::error("ImageFilePNG::load(): can't create info struct\n");
//        png_destroy_read_struct(&png_ptr,0,0);
//        return 0;
//    }
//
//    DataSource source;
//    source.src = src;
//    source.offset = 8;
//    source.size = size;
//
//    png_set_read_fn(png_ptr,&source,data_read_function);
//    png_set_sig_bytes(png_ptr,8);
//
//    // get info
//    int format;
//    png_uint_32 width;
//    png_uint_32 height;
//    if(get_info(png_ptr,png_info_ptr,"memory",width,height,format) == 0) {
//        png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
//        return 0;
//    }
//
//    // create image
//    image.create2D(width,height,format,1,0);
//
//    // read png image
//    unsigned char *data = image.getPixels2D();
//    png_byte **png_rows = new png_byte*[height];
//    int stride = image.getWidth() * image.getPixelSize();
//    for(int i = 0; i < (int)height; i++) {
//        png_rows[i] = (png_byte*)data + stride * i;
//    }
//    png_read_image(png_ptr,png_rows);
//    png_read_end(png_ptr,NULL);
//    png_destroy_read_struct(&png_ptr,0,&png_info_ptr);
//    delete [] png_rows;
//
//    return 1;
//}
//
///*
// */
//void ImageFilePNG::write_function(png_structp png_ptr,png_bytep ptr,png_size_t size) {
//    File *file = (File*)png_get_io_ptr(png_ptr);
//    file->write(ptr,sizeof(png_byte),size);
//}
//
//void ImageFilePNG::flush_function(png_structp png_ptr) {
//    File *file = (File*)png_get_io_ptr(png_ptr);
//    file->flush();
//}
//
///*
// */
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
