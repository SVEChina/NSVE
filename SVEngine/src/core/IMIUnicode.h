//
// IMIUnicode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_IMIUNICODE_H
#define IMI_IMIUNICODE_H
#include "../base/IMIBase.h"
namespace imi {

    class IMIUnicode {
    public:
        enum IMIUNICODEBYTEORDER{
            IMI_LITTLE_ENDIAN,
            IMI_BIG_ENDIAN
        };
        // This function will attempt to decode a UTF-8 encoded character in the buffer.
        // If the encoding is invalid, the function returns -1.
        static f32 decodeUTF8(cptr8 _encodedBuffer, u32 *_outCharLength);
        
        // This function will encode the value into the buffer.
        // If the value is invalid, the function returns -1, else the encoded length.
        static f32 encodeUTF8(u32 _value, u8 *_outEncodedBuffer, u32 *_outCharLength);
        
        // This function will attempt to decode a UTF-16 encoded character in the buffer.
        // If the encoding is invalid, the function returns -1.
        static f32 decodeUTF16(cptr8 _encodedBuffer, u32 *_outCharLength, IMIUNICODEBYTEORDER _byteOrder = IMI_LITTLE_ENDIAN);
        
        // This function will encode the value into the buffer.
        // If the value is invalid, the function returns -1, else the encoded length.
        static f32 encodeUTF16(u32 _value, u8 *_outEncodedBuffer, u32 *_outCharLength, IMIUNICODEBYTEORDER _byteOrder = IMI_BIG_ENDIAN);
    };
    
}



#endif //IMI_IMIUNICODE_H
