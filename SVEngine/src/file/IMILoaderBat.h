//
// IMILoaderBat.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BATLOADER_H
#define IMI_BATLOADER_H

#include "IMIFileLoader.h"
#include "../base/IMIArray.h"
#include "../base/IMITable.h"

namespace imi {
    
    //加载普通的明文文件
    class IMILoaderBat : public IMIFileLoader {
    public:
        IMILoaderBat(IMIInstPtr _app);
        
        bool loadFromFile(cptr8 _filename,IMITable& _tbl);
        
    protected:
        IMIArray<IMIString> m_dataCxt;
        
        void _parse();
    };
    
}//!namespace imi



#endif //IMI_BATLOADER_H
