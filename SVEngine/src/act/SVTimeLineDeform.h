//
//  SVTimeLineDeform.h
//  SVEngine
//
//  Created by 付一洲 on 2018/9/13.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef SV_TIMELINE_DEFORM_H
#define SV_TIMELINE_DEFORM_H

#include "SVTimeLine.h"

namespace sv {
    
    
        
        class SVTimeLineDeform : public SVTimeLine {
        public:
            SVTimeLineDeform(SVInstPtr _app,f32 _time,s32 _rate);
            
            ~SVTimeLineDeform();
            
            void initKey();
            
            void enter(SVNodePtr _nodePtr);
            
            void exit(SVNodePtr _nodePtr);
            
        protected:
            void _execkey(SVNodePtr _nodePtr,f32 _dt);
            
        };
        
    
    
}//!namespace sv


#endif /* SV_TIMELINE_DEFORM_H */
