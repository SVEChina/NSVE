//
// IMIColor.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
// copy from irr

#ifndef IMI_COLOR_H
#define IMI_COLOR_H

//#include <math.h>
#include "IMIDef.h"

namespace imi {

    class IMIColor {
    public:
        IMIColor();
        
        IMIColor(f32 r, f32 g, f32 b, f32 a);
        
        void operator=(IMIColor& _color);
        
        void setColor(f32 r, f32 g, f32 b, f32 a);
        
        void setColorARGB(u32 color);
        
        u32 getColorARGB();
        
        f32 r;
        f32 g;
        f32 b;
        f32 a;
        
        static u32 transRgbaToID(u8 r, u8 g, u8 b, u8 a);
    };
    
}//!namespace imi


#endif //IMI_COLOR_H
