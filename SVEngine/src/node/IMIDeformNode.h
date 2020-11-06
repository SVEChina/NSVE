//
//  IMIDeformNode.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/4/13.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_DEFORM_NODE_H
#define IMI_DEFORM_NODE_H

#include "IMINode.h"

namespace imi {
    
    class IMIDeformNode : public IMINode {
        public :
        IMIDeformNode(IMIInstPtr _app);
        
        ~IMIDeformNode();
        
        void init();
        
        void destroy();
        
        void update(f32 _dt);
        
        void render();
        
        bool procEvent(IMIEventPtr _event);
        
        void pushDeform(IMIArray<IMIDeformImageMovePtr> _deformArray);
        
    protected:
        typedef IMIArray<IMIDeformImageMovePtr> DEFORMPOOL;
        DEFORMPOOL m_deformPool;
  
    };

}//!namespace imi

#endif /* IMI_DEFORM_NODE_H */
