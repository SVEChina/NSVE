//
// IMIParseMain.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEMAIN_H
#define IMI_PARSEMAIN_H

#include "../base/IMIGBase.h"
#include "IMIParseDef.h"
#include "../base/IMIMap.h"

namespace imi {
    
    
        
        class IMIParseMain : public IMIGBaseEx {
        public:
            IMIParseMain(IMIInstPtr _app);
            
            virtual ~IMIParseMain();
            
            IMIModuleBasePtr parse(cptr8 _path, s32 resid);

        protected:
            void _registDictionary(cptr8 _type, prase_content_fun fun);
            
            void _unregistDictionary(cptr8 _type);
            
            bool _hasRegist(cptr8 _type );
            
            IMINodePtr _callTypeParse(cptr8 _type, RAPIDJSON_NAMESPACE::Value &item, s32 resid, cptr8 _path);
            
        protected:
            typedef IMIMap<IMIString, prase_content_fun> PARSEPOOL;
            PARSEPOOL parse_dictionary;
            IMIInstPtr m_app;
        };

        
    
    
}//!namespace imi



#endif //IMI_PARSEMAIN_H
