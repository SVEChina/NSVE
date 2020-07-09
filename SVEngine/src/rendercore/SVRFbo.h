//
// SVRFbo.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SVRFbo_h
#define SVRFbo_h

#include "SVRRes.h"

namespace sv {
    
        class SVRFbo: public SVRRes{
        public:
            SVRFbo(SVInstPtr _app);
            
            virtual ~SVRFbo();
            
            virtual void create(SVRendererPtr _renderer) {}
            
            virtual void destroy(SVRendererPtr _renderer) {}
            
            virtual void bind() {}
            
            virtual void unbind() {}
            
        protected:
            SVLockPtr m_texLock;
        };
        
}//!namespace sv


#endif /* SVRFbo_h */
