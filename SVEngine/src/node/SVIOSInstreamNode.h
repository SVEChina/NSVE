//
// SVIOSInstreamNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_IOSINSTREAMNODE_H
#define SV_IOSINSTREAMNODE_H

#include "SVNode.h"

namespace sv {
    
    class SVIOSInstreamNode : public SVNode {
    public:
        SVIOSInstreamNode(SVInstPtr _app);
        
        virtual ~SVIOSInstreamNode();
        
        void init(SV_TEXIN _tt);
        
        void destroy();
        
        void update(f32 dt);
        
        void render();
        
    protected:
        SVMtlCorePtr m_pMtl;
        SV_TEXIN m_tt;
    };

}//!namespace sv


#endif //SV_IOSCAMSTREAMNODE_H
