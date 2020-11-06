//
// IMIFileWriter.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FILEWRITER_H
#define IMI_FILEWRITER_H

#include "../base/IMIObject.h"
#include "../base/IMIGBase.h"
#include <stdio.h>

namespace imi {
    
    class IMIFileWriter: public IMIGBaseEx {
    public:
        IMIFileWriter(IMIInstPtr _app);
        
        ~IMIFileWriter();
        
        void setPath(cptr8 _path);
        
        void* createFileHandle(cptr8 _filename);
        
        void destroyFileHandle();
        
        bool write(void* data,s32 len,s32 count);
        
    protected:
        FILE* m_fp;
        IMIString m_path;
    };

    
}//!namespace imi



#endif //IMI_FILEWRITER_H
