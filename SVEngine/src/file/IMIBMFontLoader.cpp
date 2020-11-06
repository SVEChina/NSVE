//
// IMIBMFontLoader.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIBMFontLoader.h"
#include "IMIFileMgr.h"
#include "../base/IMIDataChunk.h"
#include "../mtl/IMITexMgr.h"
#include "../app/IMIInst.h"
#include "../core/IMIBMFont.h"

using namespace imi;

IMIBMFontLoader::IMIBMFontLoader(IMIInstPtr _app)
:IMIFileLoader(_app) {

}

IMIBMFontLoader::~IMIBMFontLoader() {
    
}

bool IMIBMFontLoader::loadData(cptr8 _fontFilePath, IMIBMFontPtr _font) {
    if (!_font) {
        return false;
    }
    _font->m_fntFilePath = _fontFilePath;
    s32 pos = _font->m_fntFilePath.rfind('/');
    _font->m_fntFileName = IMIString::substr(_font->m_fntFilePath.c_str(), pos+1, _font->m_fntFilePath.size()-pos-1);
    // Load the font
    IMIDataChunk tIMIDataChunk;
    bool t_flag = mApp->m_file_sys->loadFileContentStr(&tIMIDataChunk, _fontFilePath);
    if (!t_flag) {
        return false;
    }
    if (tIMIDataChunk.getRealSize() == 0){
        return false;
    }
    c8 str[4] = {0};
    char* t_p = tIMIDataChunk.getPointerChar();
    str[0] = *t_p;t_p++;
    str[1] = *t_p;t_p++;
    str[2] = *t_p;
    if( strcmp(str, "BMF") == 0 ){
        IMIBMFontParseBinaryFormat parseBinaryFormat;
        parseBinaryFormat.parseConfigFile(_font, tIMIDataChunk.getPointerChar(), tIMIDataChunk.getRealSize());
    }else{
        IMIBMFontParseTextFormat parseTextFormat;
        parseTextFormat.parseConfigFile(_font, tIMIDataChunk.getPointerChar(), tIMIDataChunk.getRealSize());
    }
    return true;
}

//parse font binary format
IMIBMFontParseBinaryFormat::IMIBMFontParseBinaryFormat(){
    
}

IMIBMFontParseBinaryFormat::~IMIBMFontParseBinaryFormat(){
    
}

void IMIBMFontParseBinaryFormat::parseConfigFile(IMIBMFontPtr _font, c8 *_pData, u64 _size){
    /* based on http://www.angelcode.com/products/bmfont/doc/file_format.html file format */
    u64 remains = _size;
    _pData += 4; remains -= 4;
    while (remains > 0)
    {
        u8 blockId = _pData[0]; _pData += 1; remains -= 1;
        u32 blockSize = 0; memcpy(&blockSize, _pData, 4);
        _pData += 4; remains -= 4;
        if (blockId == 1){
            _readInfoBlock(_font, _pData, blockSize);
        }else if (blockId == 2){
            _readCommonBlock(_font, _pData, blockSize);
        }else if (blockId == 3){
            _readPagesBlock(_font, _pData, blockSize);
        }else if (blockId == 4){
            _readCharsBlock(_font, _pData, blockSize);
        }else if (blockId == 5) {
            _readKerningPairsBlock(_font, _pData, blockSize);
        }
        _pData += blockSize; remains -= blockSize;
    }
}


void IMIBMFontParseBinaryFormat::_readInfoBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize){
    /*
     fontSize       2   int      0
     bitField       1   bits     2  bit 0: smooth, bit 1: unicode, bit 2: italic, bit 3: bold, bit 4: fixedHeight, bits 5-7: reserved
     charSet        1   uint     3
     stretchH       2   uint     4
     aa             1   uint     6
     paddingUp      1   uint     7
     paddingRight   1   uint     8
     paddingDown    1   uint     9
     paddingLeft    1   uint     10
     spacingHoriz   1   uint     11
     spacingVert    1   uint     12
     outline        1   uint     13 added with version 2
     fontName       n+1 string   14 null terminated string with length n
     */
    u8 outline;
    memcpy(&outline, _pData + 13, 2);
    _font->setFontInfo(outline);
}

void IMIBMFontParseBinaryFormat::_readCommonBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize){
    /*
     lineHeight 2   uint    0
     base       2   uint    2
     scaleW     2   uint    4
     scaleH     2   uint    6
     pages      2   uint    8
     bitField   1   bits    10  bits 0-6: reserved, bit 7: packed
     alphaChnl  1   uint    11
     redChnl    1   uint    12
     greenChnl  1   uint    13
     blueChnl   1   uint    14
     */
    u16 fontHeight;
    u16 base;
    u16 scaleW;
    u16 scaleH;
    u16 pages;
    bool packed;
    memcpy(&fontHeight, _pData, 2);
    memcpy(&base, _pData + 2, 2);
    memcpy(&scaleW, _pData + 4, 2);
    memcpy(&scaleH, _pData + 6, 2);
    memcpy(&pages, _pData + 8, 2);
    memcpy(&packed, _pData + 9, 1);
    _font->setCommonInfo(fontHeight, base, scaleW, scaleH, pages, packed ? true : false);
}

void IMIBMFontParseBinaryFormat::_readPagesBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize){
    /*
     pageNames     p*(n+1)     strings     0     p null terminated strings, each with length n
     */
    cptr8 *value = (cptr8 *)_pData;
    //            assert(std::strlen(value) < blockSize && "Block size should be less then string");
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //            _atlasName = FileUtils::getInstance()->fullPathFromRelativeFile(value, controlFile);
}

void IMIBMFontParseBinaryFormat::_readCharsBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize){
    /*
     id         4   uint    0+c*20  These fields are repeated until all characters have been described
     x          2   uint    4+c*20
     y          2   uint    6+c*20
     width      2   uint    8+c*20
     height     2   uint    10+c*20
     xoffset    2   int     12+c*20
     yoffset    2   int     14+c*20
     xadvance   2   int     16+c*20
     page       1   uint    18+c*20
     chnl       1   uint    19+c*20
     */
    u64 count = _blockSize / 20;
    for (u64 i = 0; i < count; i++){
        u32 charID;
        u16 x;
        u16 y;
        u16 width;
        u16 height;
        s16 xoffset;
        s16 yoffset;
        s16 xadvance;
        u8 page;
        u8 chnl;
        memcpy(&charID, _pData + (i * 20), 4);
        memcpy(&x, _pData + (i * 20) + 4, 2);
        memcpy(&y, _pData + (i * 20) + 6, 2);
        memcpy(&width, _pData + (i * 20) + 8, 2);
        memcpy(&height, _pData + (i * 20) + 10, 2);
        memcpy(&xoffset, _pData + (i * 20) + 12, 2);
        memcpy(&yoffset, _pData + (i * 20) + 14, 2);
        memcpy(&xadvance, _pData + (i * 20) + 16, 2);
        memcpy(&page, _pData + (i * 20) + 18, 1);
        memcpy(&chnl, _pData + (i * 20) + 19, 1);
        _font->addChar(charID, x, y, width, height, xoffset, yoffset, xadvance, page, chnl);
    }
}

void IMIBMFontParseBinaryFormat::_readKerningPairsBlock(IMIBMFontPtr _font, c8 *_pData, u32 _blockSize){
    /*
     first  4   uint    0+c*10     These fields are repeated until all kerning pairs have been described
     second 4   uint    4+c*10
     amount 2   int     8+c*10
     */
    u64 count = _blockSize / 20;
    for (u64 i = 0; i < count; i++)
    {
        s32 first = 0; memcpy(&first, _pData + (i * 10), 4);
        s32 second = 0; memcpy(&second, _pData + (i * 10) + 4, 4);
        s16 amount = 0; memcpy(&amount, _pData + (i * 10) + 8, 2);
        _font->addKerningPair(first, second, amount);
    }
}

//parse font text format
IMIBMFontParseTextFormat::IMIBMFontParseTextFormat(){
    
}

IMIBMFontParseTextFormat::~IMIBMFontParseTextFormat(){
    
}

void IMIBMFontParseTextFormat::parseConfigFile(IMIBMFontPtr _font, void* _data, u64 _size){
    IMIString line;
    //
    char* t_p = (char*)_data;
    char ch = *t_p;
    while( ch != '\0' ){
        // Read until line feed (or EOF)
        line = "";
        line.reserve(256);
        while( ch != '\0' ){
            ch = *t_p;
            t_p++;
            if( ch != '\n' ){
                line += ch;
            }else {
                break;
            }
        }
        // Skip white spaces
        s32 pos = _skipWhiteSpace(line.c_str(), 0);
        // Read token
        s32 pos2 = _findEndOfToken(line.c_str(), pos);
        IMIString token = IMIString::substr(line.c_str(), pos, pos2-pos);
        // Interpret line
        if( token == "info" ){
            _interpretInfo(_font, line.c_str(), pos2);
        }
    
        else if( token == "common" ) {
           _interpretCommon(_font, line.c_str(), pos2);
        }else if( token == "char" ) {
            _interpretChar(_font, line.c_str(), pos2);
        }else if( token == "kerning" ) {
            _interpretKerning(_font, line.c_str(), pos2);
        }else if( token == "page" ) {
            _interpretPage(_font, line.c_str(), pos2);
        }
    }
    // Success
}

s32 IMIBMFontParseTextFormat::_skipWhiteSpace(cptr8 _str, s32 _start){
    u32 n = _start;
    while( n < strlen(_str))
    {
        char ch = _str[n];
        if( ch != ' ' &&
           ch != '\t' &&
           ch != '\r' &&
           ch != '\n' )
            break;
        
        ++n;
    }
    return n;
}
s32 IMIBMFontParseTextFormat::_findEndOfToken(cptr8 _str, s32 _start){
    u32 n = _start;
    if( _str[n] == '"' )
    {
        n++;
        while( n < strlen(_str) )
        {
            char ch = _str[n];
            if( ch == '"' )
            {
                // Include the last quote char in the token
                ++n;
                break;
            }
            ++n;
        }
    }
    else
    {
        while( n < strlen(_str) )
        {
            char ch = _str[n];
            if( ch == ' ' ||
               ch == '\t' ||
               ch == '\r' ||
               ch == '\n' ||
               ch == '=' )
                break;
            
            ++n;
        }
    }
    return n;
}
void IMIBMFontParseTextFormat::_interpretInfo(IMIBMFontPtr _font, cptr8 _str, s32 _start){
    s32 outlineThickness;
    // Read all attributes
    s32 pos, pos2 = _start;
    while( true )
    {
        pos = _skipWhiteSpace(_str, pos2);
        pos2 = _findEndOfToken(_str, pos);
        IMIString token =  IMIString::substr(_str, pos, pos2-pos);
        pos = _skipWhiteSpace(_str, pos2);
        if( pos == strlen(_str) || _str[pos] != '=' ) break;
        pos = _skipWhiteSpace(_str, pos+1);
        pos2 = _findEndOfToken(_str, pos);
        IMIString value = IMIString::substr(_str, pos, pos2-pos);
        if( token == "outline" )
            outlineThickness = (u16)strtol(value.c_str(), 0, 10);
        
        if( pos == strlen(_str) ) break;
    }
    
    _font->setFontInfo(outlineThickness);
}
void IMIBMFontParseTextFormat::_interpretCommon(IMIBMFontPtr _font, cptr8 _str, s32 _start){
    s32 fontHeight;
    s32 base;
    s32 scaleW;
    s32 scaleH;
    s32 pages;
    s32 packed;
    // Read all attributes
    s32 pos, pos2 = _start;
    while( true )
    {
        pos = _skipWhiteSpace(_str, pos2);
        pos2 = _findEndOfToken(_str, pos);
        IMIString token = IMIString::substr(_str, pos, pos2-pos);
        pos = _skipWhiteSpace(_str, pos2);
        if( pos == strlen(_str) || _str[pos] != '=' ) break;
        pos = _skipWhiteSpace(_str, pos+1);
        pos2 = _findEndOfToken(_str, pos);
        IMIString value = IMIString::substr(_str, pos, pos2-pos);
        if( token == "lineHeight" )
            fontHeight = (short)strtol(value.c_str(), 0, 10);
        else if( token == "base" )
            base = (short)strtol(value.c_str(), 0, 10);
        else if( token == "scaleW" )
            scaleW = (short)strtol(value.c_str(), 0, 10);
        else if( token == "scaleH" )
            scaleH = (short)strtol(value.c_str(), 0, 10);
        else if( token == "pages" )
            pages = strtol(value.c_str(), 0, 10);
        else if( token == "packed" )
            packed = strtol(value.c_str(), 0, 10);
        
        if( pos == strlen(_str) ) break;
    }
    
    _font->setCommonInfo(fontHeight, base, scaleW, scaleH, pages, packed ? true : false);
}
void IMIBMFontParseTextFormat::_interpretChar(IMIBMFontPtr _font, cptr8 _str, s32 _start){
    // Read all attributes
    s32 charID = 0;
    s32 x = 0;
    s32 y = 0;
    s32 width = 0;
    s32 height = 0;
    s32 xoffset = 0;
    s32 yoffset = 0;
    s32 xadvance = 0;
    s32 page = 0;
    s32 chnl = 0;
    s32 pos, pos2 = _start;
    while( true )
    {
        pos = _skipWhiteSpace(_str, pos2);
        pos2 = _findEndOfToken(_str, pos);
        IMIString token = IMIString::substr(_str, pos, pos2-pos);
        pos = _skipWhiteSpace(_str, pos2);
        if( pos == strlen(_str) || _str[pos] != '=' ) break;
        pos = _skipWhiteSpace(_str, pos+1);
        pos2 = _findEndOfToken(_str, pos);
        IMIString value = IMIString::substr(_str, pos, pos2-pos);
        if( token == "id" )
            charID = strtol(value.c_str(), 0, 10);
        else if( token == "x" )
            x = strtol(value.c_str(), 0, 10);
        else if( token == "y" )
            y = strtol(value.c_str(), 0, 10);
        else if( token == "width" )
            width = strtol(value.c_str(), 0, 10);
        else if( token == "height" )
            height = strtol(value.c_str(), 0, 10);
        else if( token == "xoffset" )
            xoffset = strtol(value.c_str(), 0, 10);
        else if( token == "yoffset" )
            yoffset = strtol(value.c_str(), 0, 10);
        else if( token == "xadvance" )
            xadvance = strtol(value.c_str(), 0, 10);
        else if( token == "page" )
            page = strtol(value.c_str(), 0, 10);
        else if( token == "chnl" )
            chnl = strtol(value.c_str(), 0, 10);
        
        if( pos == strlen(_str) ) break;
    }
    
    // Store the attributes
    _font->addChar(charID, x, y, width, height, xoffset, yoffset, xadvance, page, chnl);
}
void IMIBMFontParseTextFormat::_interpretKerning(IMIBMFontPtr _font, cptr8 _str, s32 _start){
    // Read the attributes
    s32 first = 0;
    s32 second = 0;
    s32 amount = 0;
    s32 pos, pos2 = _start;
    while( true )
    {
        pos = _skipWhiteSpace(_str, pos2);
        pos2 = _findEndOfToken(_str, pos);
        IMIString token = IMIString::substr(_str, pos, pos2-pos);
        pos = _skipWhiteSpace(_str, pos2);
        if( pos == strlen(_str) || _str[pos] != '=' ) break;
        pos = _skipWhiteSpace(_str, pos+1);
        pos2 = _findEndOfToken(_str, pos);
        IMIString value = IMIString::substr(_str, pos, pos2-pos);
        if( token == "first" )
            first = strtol(value.c_str(), 0, 10);
        else if( token == "second" )
            second = strtol(value.c_str(), 0, 10);
        else if( token == "amount" )
            amount = strtol(value.c_str(), 0, 10);
        
        if( pos == strlen(_str) ) break;
        
    }
    // Store the attributes
    _font->addKerningPair(first, second, amount);
}
void IMIBMFontParseTextFormat::_interpretPage(IMIBMFontPtr _font, cptr8 _str, s32 _start){
    s32 charID = 0;
    IMIString file;
    // Read all attributes
    s32 pos, pos2 = _start;
    while( true ){
        pos = _skipWhiteSpace(_str, pos2);
        pos2 = _findEndOfToken(_str, pos);
        
        IMIString token = IMIString::substr(_str, pos, pos2-pos);
        
        pos = _skipWhiteSpace(_str, pos2);
        if( pos == strlen(_str) || _str[pos] != '=' ) break;
        
        pos = _skipWhiteSpace(_str, pos+1);
        pos2 = _findEndOfToken(_str, pos);
        
        IMIString value = IMIString::substr(_str, pos, pos2-pos);
        
        if( token == "id" ){
            charID = strtol(value.c_str(), 0, 10);
        }else if( token == "file" ) {
            file = IMIString::substr(value.c_str(), 1, value.size()-2);
        }
        if( pos == strlen(_str) )
            break;
    }
    _font->loadPage(charID, file.c_str());
}
