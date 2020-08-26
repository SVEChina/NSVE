//
// SVDummyNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_DUMMYNODE_H
#define SV_DUMMYNODE_H

#include "SVNode.h"

namespace sv {
    
    //虚拟节点 主要用于 人脸坐标系统
    class SVDummyNode: public SVNode{
    public:
        SVDummyNode(SVInstPtr _app);
    };
    
}//!namespace sv



#endif //SV_DUMMYNODE_H
