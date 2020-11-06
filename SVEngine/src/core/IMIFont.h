//
// IMIFont.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FONT_H
#define IMI_FONT_H

#include "../base/IMIObject.h"
#include "../base/IMIGBase.h"
#include "../base/IMIPreDeclare.h"
namespace imi {
    
        class IMIFont : public IMIGBaseEx {
        public:
            enum IMIFONTTEXTENCODING{
                NONE = 0,
                UTF8,
                UTF16
            };
            IMIFont(IMIInstPtr _app);
            
            ~IMIFont();
            
            void init();
            
            void setTextEncoding(IMIFONTTEXTENCODING _encoding);
            
            IMIFONTTEXTENCODING getTextEncoding();
        protected:
            
        protected:
            IMIFONTTEXTENCODING m_encoding;
        };
        
    
}//!namespace imi



#endif //IMI_FONT_H
