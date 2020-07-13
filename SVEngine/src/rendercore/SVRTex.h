//
// SVRTex.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SVRTex_h
#define SVRTex_h

#include "SVRRes.h"

namespace sv {
    
        class SVRTex: public SVRRes{
        public:
            SVRTex(SVInstPtr _app);
            
            virtual ~SVRTex();
            
            virtual void create(SVRendererPtr _renderer);
            
            virtual void destroy(SVRendererPtr _renderer);
            
            virtual void setTexData(SVDataSwapPtr _data);
            
            virtual void commit();  //数据提交到显卡
            
        protected:
            SVLockSpinPtr m_texLock;
        };
        
    
}//!namespace sv


#endif /* SVRTex_h */
