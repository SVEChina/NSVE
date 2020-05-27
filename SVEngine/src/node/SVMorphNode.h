//
// SVSkinNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MORPHNODE_H
#define SV_MORPHNODE_H

#include "SVNode.h"
#include "../base/SVMap.h"


namespace sv {
    
    //morph动画节点
    
    class SVMorphNode : public SVNode {
    public:
        SVMorphNode(SVInst *_app);
        
        ~SVMorphNode();
    };
        
}//!namespace sv

//
#endif //SV_MORPHNODE_H


