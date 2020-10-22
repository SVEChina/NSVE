//
// SVFileMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FILEMGR_H
#define SV_FILEMGR_H

#include "../base/SVGBase.h"
#include "../base/SVDataChunk.h"
#include <vector>

//文件路径管理器 增加搜索路径相关
namespace sv {
    
    class SVFileMgr : public SVGBaseEx {
    public:
        SVFileMgr(SVInstPtr _app);
        
        ~SVFileMgr();
        
        //获取搜索路径数目
        s32 getSearchPathNum();
        
        //设置c++搜索路径
        void addRespath(cptr8 _path);
        
        bool delRespath(cptr8 _path);
        
        void clearRespath();
        
        //获取文件全名 包含路径
        SVString getFileFullName(cptr8 _fname);
        
        SVString getPath(cptr8 _fname);
        
        bool loadFileContent(SVDataChunk *_datachunk, cptr8 _fname);
        
        bool loadFileContentStr(SVDataChunk *_datachunk, cptr8 _fname);
        
        bool exist(cptr8 _fname);
        
        u64 checkFileDataLength(cptr8 _fpath);
        
    protected:
        typedef std::vector<SVString> SEARCHPATHPOOL;
        SEARCHPATHPOOL m_searchPathPool;
        
        SVLockPtr m_file_lock;
        
        bool _hasRespath(cptr8 _path);
        
    public:
        static bool s_loadFileContent(SVDataChunk *_datachunk, cptr8 _fullname);
        
        static bool s_loadFileContentStr(SVDataChunk *_datachunk, cptr8 _fullname);
    };
    
}//!namespace sv



#endif //SV_FILEMGR_H
