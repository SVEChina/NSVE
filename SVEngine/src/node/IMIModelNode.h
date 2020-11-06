//
// IMISkinNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MODEL_NODE_H
#define IMI_MODEL_NODE_H

#include "IMINode.h"

namespace imi {
    
    /*
     normal 3d node
     */

    class IMIModelNode : public IMINode {
    public:
        IMIModelNode(IMIInstPtr _app);
        
        ~IMIModelNode();
        
        void setModel(IMIModelPtr _model);
        
        IMIModelPtr getModel();
        
        void update(f32 _dt);

        void render();
        
    protected:
        IMIModelPtr m_model;
    };

}//!namespace imi



//
#endif //IMI_MODEL_NODE_H


