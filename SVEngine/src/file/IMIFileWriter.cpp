//
// IMIFileWriter.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFileWriter.h"

using namespace imi;

IMIFileWriter::IMIFileWriter(IMIInstPtr _app)
:IMIGBaseEx(_app)
,m_fp(nullptr){
}

IMIFileWriter::~IMIFileWriter() {
    destroyFileHandle();
}

void IMIFileWriter::setPath(cptr8 _path){
    m_path = _path;
}

void* IMIFileWriter::createFileHandle(cptr8 _filename){
    IMIString t_fullname = m_path + _filename;
    m_fp = fopen(_filename, "wb");
    return m_fp;
}

void IMIFileWriter::destroyFileHandle(){
    if(m_fp){
        fclose(m_fp);
        m_fp = nullptr;
    }
}

bool IMIFileWriter::write(void* data,s32 len,s32 count) {
    if(!m_fp)
        return false;
    u64 t_len = fwrite(data,len,count, m_fp);
    if(t_len>0)
        return true;
    return false;
}
