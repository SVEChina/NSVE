//
// IMIFilterPicmodify.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BASEDONFILTER_H
#define IMI_BASEDONFILTER_H

#include "IMIFilterBase.h"

namespace imi {
    
    /*
        图片修正
     */

    class IMIFilterPicmodify : public IMIFilterBase {
    public:
        IMIFilterPicmodify(IMIInstPtr _app);
        
        ~IMIFilterPicmodify();
        
        virtual  bool create();

        virtual  void destroy();

        virtual  void update(f32 _dt);

        FtParamPic m_param;
    };
    
}//!namespace imi


#endif /* IMI_BASEDONFILTER_H */
