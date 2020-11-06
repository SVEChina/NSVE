//
// IMISkinNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MORPHNODE_H
#define IMI_MORPHNODE_H

#include "IMINode.h"
#include "../base/IMIMap.h"


namespace imi {
    
    //morph动画节点
    
    class IMIMorphNode : public IMINode {
    public:
        IMIMorphNode(IMIInstPtr _app);
        
        ~IMIMorphNode();
    };
        
}//!namespace imi

//
#endif //IMI_MORPHNODE_H


