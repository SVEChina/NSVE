//
//  IMIParseLUTFilter.h
//  IMIngine
//
//  Created by 徐子昱 on 2018/10/23.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef IMI_PARSELUTFILTER_H
#define IMI_PARSELUTFILTER_H

#include "../file/IMIParseData.h"

namespace imi {
    
    class IMIParseLUTFilter : public IMIParseData {
    public:
        static IMIFilterBasePtr parseLUT(IMIInstPtr _app,cptr8 _path, s32 resid);
    };

}//!namespace imi


#endif /* IMI_PARSELUTFILTER_H */
