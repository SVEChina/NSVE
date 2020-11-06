//
// IMIDummyNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_DUMMYNODE_H
#define IMI_DUMMYNODE_H

#include "IMINode.h"

namespace imi {
    
    //虚拟节点 主要用于 人脸坐标系统
    class IMIDummyNode: public IMINode{
    public:
        IMIDummyNode(IMIInstPtr _app);
    };
    
}//!namespace imi



#endif //IMI_DUMMYNODE_H
