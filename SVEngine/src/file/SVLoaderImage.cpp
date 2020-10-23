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

#define STB_IMAGE_IMPLEMENTATION
#include "../third/lib_stb_image/stb_image.h"

using namespace sv;

s32 SVLoaderImage::check(cptr8 _name) {
    cptr8 ext = strrchr(_name,'.');
    if(ext && (!strcmp(ext,".tga") || !strcmp(ext,".TGA")))
        return 1;
    if(ext && (!strcmp(ext,".jpg") || !strcmp(ext,".JPG")))
        return 1;
    if(ext && (!strcmp(ext,".png") || !strcmp(ext,".PNG")))
        return 1;
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS")))
        return 0;
    if(ext && (!strcmp(ext,".psd") || !strcmp(ext,".PSD")))
        return 0;
    return 0;
}

s32 SVLoaderImage::load(SVInstPtr _app,SVImagePtr _image, cptr8 _name) {
    StbRef _stbRef;
    SVString t_fname = _app->m_file_sys->getFileFullName(_name);
    if( check(t_fname) == 0 ) {
        //可能会走压缩纹理
        return 0;
    }
    FILE *f = stbi__fopen(t_fname.c_str(), "rb");
    if (f) {
        if (stbi_is_16_bit_from_file(f) == 1) {
            _stbRef.bit = 16;
            _stbRef.data = stbi_load_from_file_16(
                    f,
                    &_stbRef.width,
                    &_stbRef.height,
                    &_stbRef.channels,
                    0
            );
        } else {
            _stbRef.bit = 8;
            _stbRef.data = stbi_load_from_file(
                    f,
                    &_stbRef.width,
                    &_stbRef.height,
                    &_stbRef.channels,
                    0
            );
        }
        fclose(f);
        if (_stbRef.data) {
            _stbRef.dataLen = _stbRef.width * _stbRef.height * _stbRef.channels * (_stbRef.bit/8);
            _image->fill(&_stbRef);
            free(_stbRef.data);
            return 1;
        }
        return 1;
    }
    return 0;
}

s32 SVLoaderImage::load(SVInstPtr _app,SVImagePtr _image, cptr8 _name, s32 _offset) {
    //_image.clear();
    cptr8 ext = strrchr(_name,'.');
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS")))
        return 0;//SVImageFileDDS::load(image,name,offset);
    return 0;
}

s32 SVLoaderImage::load(SVInstPtr _app,SVImagePtr _image, cptru8 _data, s32 _size) {
    //_image.clear();
    if(_size > 2 && _data[0] == 0xff && _data[1] == 0xd8) return 0;//SVImageFileJPEG::load(image,data,size);
    if(_size > 3 && _data[0] == 0x89 && _data[1] == 0x50 && _data[2] == 0x4e && _data[3] == 0x47) {
//        SVLoaderImagePNG loaderPNG(mApp);
//        return loaderPNG.load(_image,_data,_size);
        return 0;
    }
    
    return 0;
}

s32 SVLoaderImage::save(SVInstPtr _app,const SVImagePtr _image, cptr8 _name, f32 _quality) {
//    if(_image.isLoaded() == 0) {
//        return 0;
//    }
    cptr8 ext = strrchr(_name,'.');
    
    if(ext && (!strcmp(ext,".tga") || !strcmp(ext,".TGA"))) return 0;//SVImageFileTGA::save(image,name);
    if(ext && (!strcmp(ext,".jpg") || !strcmp(ext,".JPG"))) return 0;//SVImageFileJPEG::save(image,name,quality);
    if(ext && (!strcmp(ext,".png") || !strcmp(ext,".PNG"))) return 0;//SVImageFilePNG::save(image,name);
    if(ext && (!strcmp(ext,".dds") || !strcmp(ext,".DDS"))) return 0;//SVImageFileDDS::save(image,name);
    if(ext && (!strcmp(ext,".psd") || !strcmp(ext,".PSD"))) return 0;//SVImageFilePSD::save(image,name);
    
    return 0;
}
