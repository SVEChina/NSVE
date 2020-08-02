//
// SVImage.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_IMAGE_H
#define SV_IMAGE_H

#include "../base/SVGBase.h"
#include "../base/SVPreDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include <string>

namespace sv {
    
    class SVImage : public SVGBaseEx {
    public:
        struct Pixeli{
            s32 r,g,b,a;
        };
        
        struct Pixelf{
            f32 r,g,b,a;
        };
        
        struct Pixel{
            Pixeli i;
            Pixelf f;
        };
        
        SVImage(SVInstPtr _app);
        
        SVImage(SVInstPtr _app, cptr8 _filename);
        
        virtual ~SVImage();
        
        s32 load(cptr8 _filename);
        
        //clear image
        void clear();
        
        // create image
        s32 create2D(s32 _width, s32 _height, s32 _format);
        
        s32 create3D(s32 _width, s32 _height, s32 _depth, s32 _format, bool _allocate = true);
        
        s32 getSize() const;
        
        s32 getWidth() const;
        
        s32 getHeight() const;
        
        s32 getDepth() const;
        
        s32 getPixelSize() const;
        
        s32 isRawFormat() const;
        
        s32 isUCharFormat() const;
        
        s32 isHalfFormat() const;
        
        s32 isFloatFormat() const;
        
        s32 isCombinedFormat() const;

        s32 isCompressedFormat() const;
        
        s32 isZCompressedFormat() const;
        
        // loaded flag
        s32 isLoaded() const;
        
        // image type
        s32 getType() const;
        cptr8 getTypeName() const;
        
        // image format
        s32 getFormat() const;
        cptr8 getFormatName() const;

        // 2D pixels
        void set2D(s32 _x, s32 _y, const Pixel &_p);
        void set2D(s32 _x, s32 _y, s32 _r, s32 _g = 0, s32 _b = 0, s32 _a = 0);
        Pixel get2D(s32 _x, s32 _y) const;
        Pixel get2D(f32 _x, f32 _y) const;
        
        s32 get2Di(f32 _x, f32 _y, s32 _index) const;
        // 3D pixels
        void set3D(s32 _x, s32 _y, s32 _z, const Pixel &_p);
        void set3D(s32 _x, s32 _y, s32 _z, s32 _r, s32 _g = 0, s32 _b = 0, s32 _a = 0);
        Pixel get3D(s32 _x, s32 _y, s32 _z) const;
        Pixel get3D(f32 _x, f32 _y, f32 _z) const;
        
        void setPixels(u8 *pixels, s32 _size);
        
        u8 *getPixels();
        u8 *getPixels2D();
        u8 *getPixels3D();
        
        cptr8 getPixels() const;
        cptr8 getPixels2D() const;
        cptr8 getPixels3D() const;
        
        SVTexturePtr toTexture();
        
    private:
        // pixels
        void _set(u32 _x, u32 _y, u32 _offset, const Pixel &_p);
        void _get(u32 _x, u32 _y, u32 _offset, Pixel &_p) const;
        void _get(u32 _x, u32 _y, u32 _offset, Pixel &_p00, Pixel &_p10, Pixel &_p01, Pixel &_p11) const;
        void _geti(u32 _x, u32 _y, u32 _offset, s32 _index, s32 &_p00, s32 &_p10, s32 &_p01, s32 &_p11) const;
        void _set(u32 _x, u32 _y, u32 _z, u32 _offset, const Pixel &_p);
        void _get(u32 _x, u32 _y, u32 _z, u32 _offset, Pixel &_p) const;
        void _get(u32 _x, u32 _y, u32 _z, u32 _offset, Pixel &_p00, Pixel &_p10, Pixel &_p01, Pixel &_p11) const;
        void _interpolate(f32 _x, f32 _y, const Pixel &_p00, const Pixel &_p10, const Pixel &_p01, const Pixel &_p11, Pixel &_p) const;
        
        std::string m_img_name;
        
        c8 m_type;                  // image type
        c8 m_format;                // image format
        
        s32 m_width;                // image size
        s32 m_height;
        s32 m_depth;
        SVDataSwapPtr m_pData;
    };
    
    
    
}//!namespace sv



#endif //SV_IMAGE_H
