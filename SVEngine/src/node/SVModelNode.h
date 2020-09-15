//
// SVSkinNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MODEL_NODE_H
#define SV_MODEL_NODE_H

#include "SVNode.h"

namespace sv {
    
    /*
     normal 3d node
     */

    class SVModelNode : public SVNode {
    public:
        SVModelNode(SVInstPtr _app);
        
        ~SVModelNode();
        
        void update(f32 dt);

        void render();
        
        void setModel(SVModelPtr _model);
        
        SVModelPtr getModel();
        
    protected:
        SVModelPtr m_model;
    };

}//!namespace sv



//
#endif //SV_MODEL_NODE_H


