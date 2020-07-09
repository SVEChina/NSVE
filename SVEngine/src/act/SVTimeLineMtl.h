//
//  SVTimeLineMtl.h
//  SVEngine
//
//  Created by 付一洲 on 2018/9/13.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef SV_TIMELINE_MTL_H
#define SV_TIMELINE_MTL_H

#include "SVTimeLine.h"

namespace sv {
    
    
        
        class SVTimeLineMtl : public SVTimeLine {
        public:
            SVTimeLineMtl(SVInstPtr _app,f32 _time,s32 _rate);
            
            ~SVTimeLineMtl();
            
            void initKey();
            
            void enter(SVNodePtr _nodePtr);
            
            void exit(SVNodePtr _nodePtr);
            
            void update(SVNodePtr _nodePtr,f32 _dt);
           
        };
        
    
    
}//!namespace sv


#endif /* SV_TIMELINE_MTL_H */
