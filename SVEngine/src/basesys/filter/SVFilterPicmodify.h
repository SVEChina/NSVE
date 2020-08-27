//
// SVFilterPicmodify.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_BASEDONFILTER_H
#define SV_BASEDONFILTER_H

#include "SVFilterBase.h"
#include "../../mtl/SVMtlDeclare.h"
#include "../../node/SVNodeDeclare.h"

namespace sv {
    
    /*
        图片修正
     */

    class SVFilterPicmodify : public SVFilterBase {
    public:
        SVFilterPicmodify(SVInstPtr _app);
        
        ~SVFilterPicmodify();
        
        virtual  bool create();

        virtual  void destroy();

        virtual  void update(f32 _dt);

        FtParamPic m_param;
    };
    
}//!namespace sv


#endif /* SV_BASEDONFILTER_H */
