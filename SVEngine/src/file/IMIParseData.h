//
// IMIParseData.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEDATA_H
#define IMI_PARSEDATA_H

#include "../base/IMIGBase.h"
#include "../node/IMINodeDef.h"

namespace imi {
    
    
        
        class IMIParseData : public IMIGBaseEx {
        public:
            IMIParseData(IMIInstPtr _app);
            
            ~IMIParseData();
            
        public:
            IMIString version;
            IMIString name;
            IMIString type;
            IMIString subType;
            IMIString resourceType;
            s32 personid;
            s32 loop;
            
            virtual void generate(s32 resid);
            
            virtual void generate(s32 resid, cptr8 path);
            
            void suspend();
            
        protected:
            void _addNode(IMINodePtr _node);
            
            void _clearNode();
            
            IMIArray<IMINodePtr> m_Nodes;
        };
        
    
    
}//!namespace imi



//
#endif //IMI_PARSEDATA_H
