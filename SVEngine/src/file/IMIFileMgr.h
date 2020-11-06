//
// IMIFileMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FILEMGR_H
#define IMI_FILEMGR_H

#include "../base/IMIGBase.h"
#include "../base/IMIDataChunk.h"
#include <vector>

//文件路径管理器 增加搜索路径相关
namespace imi {
    
    class IMIFileMgr : public IMIGBaseEx {
    public:
        IMIFileMgr(IMIInstPtr _app);
        
        ~IMIFileMgr();
        
        //获取搜索路径数目
        s32 getSearchPathNum();
        
        //设置c++搜索路径
        void addRespath(cptr8 _path);
        
        bool delRespath(cptr8 _path);
        
        void clearRespath();
        
        //获取文件全名 包含路径
        IMIString getFileFullName(cptr8 _fname);
        
        IMIString getPath(cptr8 _fname);
        
        bool loadFileContent(IMIDataChunk *_datachunk, cptr8 _fname);
        
        bool loadFileContentStr(IMIDataChunk *_datachunk, cptr8 _fname);
        
        bool exist(cptr8 _fname);
        
        u64 checkFileDataLength(cptr8 _fpath);
        
    protected:
        typedef std::vector<IMIString> SEARCHPATHPOOL;
        SEARCHPATHPOOL m_searchPathPool;
        
        IMILockPtr m_file_lock;
        
        bool _hasRespath(cptr8 _path);
        
    public:
        static bool s_loadFileContent(IMIDataChunk *_datachunk, cptr8 _fullname);
        
        static bool s_loadFileContentStr(IMIDataChunk *_datachunk, cptr8 _fullname);
    };
    
}//!namespace imi



#endif //IMI_FILEMGR_H
