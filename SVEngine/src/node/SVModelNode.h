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
        
        void setModel(SVModelPtr _model);
        
        SVModelPtr getModel();
        
        void update(f32 _dt);

        void render();
        
    protected:
        SVModelPtr m_model;
    };

}//!namespace sv



//
#endif //SV_MODEL_NODE_H


