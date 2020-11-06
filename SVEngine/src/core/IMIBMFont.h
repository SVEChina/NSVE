//
// IMIBMFont.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BMFONT_H
#define IMI_BMFONT_H

#include "IMIFont.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../base/IMIMap.h"
#include "../base/IMISet.h"

namespace imi {
    
    
        
        class IMIBMFont : public IMIFont {
        public:
            typedef struct _IMIBMFontCharInfo {
                u32 charID;
                u16 x;
                u16 y;
                u16 width;
                u16 height;
                s16 xOffset;
                s16 yOffset;
                s16 xAdvance;
                u16 page;
                u16 chnl;
                IMIArray<s32> kerningPairs;
            } IMIBMFONTCHARINFO;
            
            typedef struct _IMIBMFontPadding {
                s32 left;
                s32 top;
                s32 right;
                s32 bottom;
            } IMIBMFONTPADDING;
            
            static IMIBMFontPtr creatFnt(cptr8 _filePath, IMIInstPtr _app);
            
            IMIBMFont(IMIInstPtr _app);
            
            ~IMIBMFont();
            
            void init();
            
            f32 getTextWidth(cptr8 _text, f32 _fontSize);
            
            f32 getTextHeight(cptr8 _text, f32 _fontSize);
            
            s32 getTextLength(cptr8 _text);
            
            s32 getTextChar(cptr8 _text, s32 _pos, s32 *_nextPos = 0);
            
            IMIBMFONTCHARINFO getChar(s32 _charID);
            ////
            void setFontInfo(s32 _outlineThickness);
            
            void setCommonInfo(s32 _fontHeight, s32 _base, s32 _scaleW, s32 _scaleH, s32 _pages, bool _isPacked);
            
            void addChar(s32 _charID, s32 _x, s32 _y, s32 _w, s32 _h, s32 _xoffset, s32 _yoffset, s32 _xadvance, s32 _page, s32 _chnl);
            
            void addKerningPair(s32 _first, s32 _second, s32 _amount);
            
            void loadPage(s32 _pageID, cptr8 _pageFile);
            
        public:
            IMIMap<u32, IMITexturePtr> m_textures;
            
            s16 m_base;// y of base line
            
            s16 m_fontScaleW;
            
            s16 m_fontScaleH;
            
            s16 m_pages;
            
            IMIString m_fntFilePath;
            
            IMIString m_fntFileName;
            
            bool m_enableMipMap;
            
        protected:
            s32 _getTextLength(cptr8 _text);
            f32 _adjustForKerningPairs(s32 _first, s32 _second, f32 _fontSize);
            s32 _findTextChar(cptr8 _text, s32 _start, s32 _length, s32 _ch);
            
        protected:
            IMIMap<u32, IMIBMFONTCHARINFO> m_charsMap;
            IMIBMFONTCHARINFO m_defChar;
            s32 m_outlineThickness;
            bool m_hasOutline;
            s32 m_fontHeight;// total height of the font
        };
        
    
    
}//!namespace imi



#endif //IMI_BMFONT_H
