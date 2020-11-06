//
// IMIImageUsingMove.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_IMAGEUSINGMOVE_H
#define IMI_IMAGEUSINGMOVE_H

#include "../base/IMIObject.h"
#include "../base/IMIVec2.h"
#include "../rendercore/IMIRenderMesh.h"

namespace imi {
    
    
        
        class IMIImageUsingMove :public IMIObject{
        public:
            IMIImageUsingMove();
            
            ~IMIImageUsingMove();
            
            IMIArray<FVec2> m_controlArray;
            
            IMIArray<FVec2> m_targetArray;
            
            IMIArray<f64>  m_weightArray;
            
            FVec2 MLS(const FVec2& t);
            
            void clearContrl();
            
            void setControl(FVec2 _v);
            
            void setTargetControl(FVec2 _v);
        protected:
             IMILockPtr m_lock;
        };
        
    
    
}//!namespace imi

#endif /* IMI_IMAGEUSINGMOVE_H */
