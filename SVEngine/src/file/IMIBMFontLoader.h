//
// IMIBMFontLoader.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BMFONTLOADER_H
#define IMI_BMFONTLOADER_H

#include "IMIFileLoader.h"
namespace imi {
    class IMIBMFontLoader : public IMIFileLoader {
    public:
        IMIBMFontLoader(IMIInstPtr _app);
        
        ~IMIBMFontLoader();
        
        bool loadData(cptr8 _fontFilePath, IMIBMFontPtr _font);
    private:
        u32  _parseCharacterDefinition(IMIBMFontPtr _font, cptr8 line);
        void _parseInfoArguments(cptr8 line);
        void _parseCommonArguments(cptr8 line);
        void _parseImageFileName(cptr8 line, cptr8 fntFile);
        void _parseKerningEntry(cptr8 line);
        void _purgeKerningDictionary();
        void _purgeFontDefDictionary();
    };
    
    //
    class IMIBMFontParseBinaryFormat {
    public:
        IMIBMFontParseBinaryFormat();
        
        ~IMIBMFontParseBinaryFormat();
        
        void parseConfigFile(IMIBMFontPtr _font, c8 *_pData, u64 _size);
    private:
        void _readInfoBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize);
        void _readCommonBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize);
        void _readPagesBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize);
        void _readCharsBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize);
        void _readKerningPairsBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize);
    };
    //
    class IMIBMFontParseTextFormat {
    public:
        IMIBMFontParseTextFormat();
        
        ~IMIBMFontParseTextFormat();
        
        void parseConfigFile(IMIBMFontPtr _font, void* _data, u64 _size);
    private:
        s32 _skipWhiteSpace(cptr8 _str, s32 _start);
        s32 _findEndOfToken(cptr8 _str, s32 _start);
        void _interpretInfo(IMIBMFontPtr _font, cptr8 _str, s32 _start);
        void _interpretCommon(IMIBMFontPtr _font, cptr8 _str, s32 _start);
        void _interpretChar(IMIBMFontPtr _font, cptr8 _str, s32 _start);
        void _interpretKerning(IMIBMFontPtr _font, cptr8 _str, s32 _start);
        void _interpretPage(IMIBMFontPtr _font, cptr8 _str, s32 _start);
    };
    
}//!namespace imi




#endif //IMI_BMFONTLOADER_H
