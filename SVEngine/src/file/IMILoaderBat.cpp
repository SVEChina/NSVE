//
// IMILoaderBat.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMILoaderBat.h"
#include "../app/IMIInst.h"
#include "../base/IMIDataChunk.h"
#include "IMIFileMgr.h"

using namespace imi;

IMILoaderBat::IMILoaderBat(IMIInstPtr _app)
:IMIFileLoader(_app) {
    m_dataCxt.clear();
}

bool IMILoaderBat::loadFromFile(cptr8 _filename,IMITable& _tbl) {
    IMIDataChunk tIMIDataChunk;
    bool t_flag = mApp->m_file_sys->loadFileContent(&tIMIDataChunk, _filename);
    if (t_flag) {
        IMIStringArray t_str_array;
        t_str_array.setData(tIMIDataChunk.getPointerChar(),'&');
        for(s32 i=0;i<t_str_array.size();i++) {
            IMIString t_line_value = t_str_array[i];
            if(i == 0) {
                _tbl.setHead(t_line_value.c_str());
            }else{
                _tbl.pushCxt(t_line_value.c_str());
            }
        }
    }
    return true;
}

void IMILoaderBat::_parse() {
    s32 t_len = m_dataCxt.size();
    for(s32 i=0;i<t_len;i++) {
        IMIStringArray t_str_array;
        t_str_array.setData(m_dataCxt[i],',');
        for(s32 j=0;j<t_str_array.size();j++) {
            IMIString t_str = t_str_array[j];
        }
    }
}
