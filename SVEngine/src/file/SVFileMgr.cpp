//
// SVFileMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFileMgr.h"
#include "../work/SVTdCore.h"
#include "../base/SVDataSwap.h"

using namespace sv;

SVFileMgr::SVFileMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    m_file_lock = MakeSharedPtr<SVLock>();
    m_searchPathPool.push_back("");
}

SVFileMgr::~SVFileMgr() {
    clearRespath();
    m_file_lock = nullptr;
}

//获取搜索路径数目
s32 SVFileMgr::getSearchPathNum() {
    return m_searchPathPool.size();
}

bool SVFileMgr::_hasRespath(cptr8 _path) {
    for (s32 i = 0; i < m_searchPathPool.size(); i++) {
        if (strcmp(m_searchPathPool[i].c_str(), _path) == 0)
            return true;
    }
    return false;
}

void SVFileMgr::addRespath(cptr8 _path) {
    m_file_lock->lock();
    if (!_hasRespath(_path)) {
        m_searchPathPool.push_back(_path);
    }
    m_file_lock->unlock();
}

bool SVFileMgr::delRespath(cptr8 _path) {
    bool t_ret = false;
    m_file_lock->lock();
    SEARCHPATHPOOL::iterator it = m_searchPathPool.begin();
    while (it!=m_searchPathPool.end()) {
        if( (*it) == _path ) {
            m_searchPathPool.erase(it);
            t_ret = true;
            break;
        }
        it++;
    }
    m_file_lock->unlock();
    return t_ret;
}

void SVFileMgr::clearRespath(){
    m_searchPathPool.clear();
}

u64  SVFileMgr::checkFileDataLength(cptr8 _fpath){
    SVString t_fullname = _fpath;
    if ( !t_fullname.empty() ) {
        FILE *fp = fopen(t_fullname.c_str(), "r");
        if (fp) {
            fseek(fp, 0, SEEK_END);
            s64 t_file_len = ftell(fp);
            u64 t_length = (u64)t_file_len;
            fseek(fp, 0, SEEK_SET);
            fclose(fp);
            return t_length;
        }
    }
    return 0;
}

bool SVFileMgr::loadFileContent(SVDataChunk *_datachunk,cptr8 _fname) {    if (!_datachunk)
        return false;
    SVString t_fullname = getFileFullName(_fname);
    SV_LOG_ERROR("SVFileMgr::loadFileContent file name %s\n", t_fullname.c_str());
    if ( !t_fullname.empty() ) {
        return s_loadFileContent(_datachunk,t_fullname.c_str());
    }
    return false;
}

bool SVFileMgr::loadFileContentStr(SVDataChunk *_datachunk,cptr8 _fname) {
    if (!_datachunk)
        return false;
    SVString t_fullname = getFileFullName(_fname);
    if (!t_fullname.empty()) {
        return s_loadFileContentStr(_datachunk,t_fullname.c_str());
    }
    return false;
}

SVString SVFileMgr::getFileFullName(cptr8 _fname) {
    //返回为"" 证明不在SD卡里面
    SVString tFileName = "";
    m_file_lock->lock();
    for (s32 i = 0; i < m_searchPathPool.size(); i++) {
        SVString t_fullpath = m_searchPathPool[i] + _fname;
        FILE *fp = fopen(t_fullpath.c_str(), "r");
        if (fp) {
            fclose(fp);
            tFileName = t_fullpath;
            break;
        }
    }
    m_file_lock->unlock();
    return tFileName;
}

SVString SVFileMgr::getPath(cptr8 _fname) {
//    //返回为"" 证明不在SD卡里面
    SVString tFileName = "";
    SVString tmp = _fname;
    s32 t_pos = tmp.rfind('/');
    if(t_pos>0) {
        tFileName = SVString::substr(tmp.c_str(), 0 , t_pos+1);
    }
    return tFileName;
}



bool SVFileMgr::s_loadFileContent(SVDataChunk *_datachunk, cptr8 _fullname) {
    FILE *fp = fopen(_fullname, "r");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        s64 t_file_len = ftell(fp);
        rewind(fp);
        void* t_buf = malloc((s32)t_file_len);
        fread(t_buf, (s32)t_file_len, 1, fp);
        _datachunk->push(t_buf, (s32)t_file_len);
        free(t_buf);
        fclose(fp);
        return true;
    }
    return false;
}

bool SVFileMgr::s_loadFileContentStr(SVDataChunk *_datachunk, cptr8 _fullname) {
    if (strcmp(_fullname, "") != 0) {
        FILE *fp = fopen(_fullname, "r");
        fseek(fp, 0, SEEK_END);
        s64 t_file_len = ftell(fp);
        rewind(fp);
        c8* t_buf = (c8*)(malloc(t_file_len+1));
        fread(t_buf, t_file_len, 1, fp);
        t_buf[t_file_len] = '\0';
        _datachunk->push(t_buf, s32(t_file_len+1));
        free(t_buf);
        fclose(fp);
        return true;
    }
    return false;
}
