//
// IMIFontProcess.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FONTMODULE_H
#define IMI_FONTMODULE_H

#include "IMIProcess.h"

#ifdef CONFIG_IS_LOAD_FREETYPE

typedef struct FT_GlyphSlotRec_ *FT_GlyphSlot;
typedef struct FT_LibraryRec_ *FT_Library;
typedef struct FT_FaceRec_ *FT_Face;
typedef struct FT_Bitmap_ FT_Bitmap;
typedef signed int FT_Int;

#endif

namespace imi {
    
    
        
        class IMIFontProcess : public IMIProcess {
        public:
            IMIFontProcess(IMIInstPtr _app);
            
            ~IMIFontProcess();
            
            virtual bool procEvent(IMIEventPtr _event);
            
            void loadDefBMFont();
            
            void loadBMFont(cptr8 _path);
            
            void getAllBMFontNames(IMIArray<IMIString> &_array);
            
            void removeBMFont(cptr8 _name);
            
            IMIBMFontPtr getBMFont(cptr8 _name);
#ifdef CONFIG_IS_LOAD_FREETYPE
            
            FT_Library getFontLib();
            
            FT_Face getFontFace();
            
            s32 getFontPixelSize();
            
        protected:
            FT_Library      m_fontLib;
            FT_Face         m_fontFace;
            s32             m_fontPixelSize;
            s32             m_fontCharSize;
            
#endif
        protected:
            IMILockPtr m_lock;
            IMIArray<IMIBMFontPtr> m_bmFonts;
        };
        
    
    
}//!namespace imi



#endif //IMI_FONTMODULE_H
