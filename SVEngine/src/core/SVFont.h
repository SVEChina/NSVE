//
// SVFont.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FONT_H
#define SV_FONT_H

#include "../base/SVObject.h"
#include "../base/SVGBase.h"
#include "../base/SVPreDeclare.h"
namespace sv {
    
        class SVFont : public SVGBaseEx {
        public:
            enum SVFONTTEXTENCODING{
                NONE = 0,
                UTF8,
                UTF16
            };
            SVFont(SVInstPtr _app);
            
            ~SVFont();
            
            void init();
            
            void setTextEncoding(SVFONTTEXTENCODING _encoding);
            
            SVFONTTEXTENCODING getTextEncoding();
        protected:
            
        protected:
            SVFONTTEXTENCODING m_encoding;
        };
        
    
}//!namespace sv



#endif //SV_FONT_H
