//
// IMITable.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMITable.h"

using namespace imi;

IMITableCell::IMITableCell() {
    m_str_value = "";
    m_f_value = 0.0f;
    m_s_value = 0;
};

IMITableCell& IMITableCell::operator=(const IMITableCell &s) {
    m_str_value = s.m_str_value;
    m_f_value = s.m_f_value;
    m_s_value = s.m_s_value;
    return *this;
}

void IMITableCell::setValue(cptr8 _value) {
    m_str_value = _value;
}

void IMITableCell::setValue(f32 _value) {
    m_f_value = _value;
}

void IMITableCell::setValue(s32 _value) {
    m_s_value = _value;
}

//
IMITableLine::IMITableLine() {
}

//IMITableLine::IMITableLine(s32 _num) {
//    m_cells.allocate(_num);
//}

IMITableLine::~IMITableLine() {
    m_cells.destroy();
}

IMITableLine &IMITableLine::operator=(const IMITableLine &s) {
    m_cells.destroy();
    for(s32 i=0;i<s.m_cells.size();i++) {
        m_cells.append(s.m_cells[i]);
    }
    return *this;
}

cptr8 IMITableLine::getStrValue(s32 _index) {
    if(_index<m_cells.size() ) {
        return m_cells[_index].getStrValue();
    }
    return nullptr;
}
//

IMITable::IMITable(){
    _hasHead = false;
}

IMITable::~IMITable() {
    //卸载内容
    clearCxt();
    //卸载头
    m_tblHead.clear();
}

void IMITable::reset() {
    //
    _hasHead = false;
    //卸载内容
    clearCxt();
    //卸载头
    m_tblHead.clear();
}

void IMITable::setHead(cptr8 _head) {
    if(!_hasHead) {
        _hasHead = true;
        IMIStringArray t_tbl_head;
        t_tbl_head.setData(_head,'#');
        for(s32 i=0;i<t_tbl_head.size();i++) {
            IMIString t_str = t_tbl_head[i];
            m_tblHead.append(t_str);
        }
    }
}

void IMITable::pushCxt(cptr8 _value) {
    if(!_hasHead)
        return;
    IMIStringArray t_tbl_cxt;
    t_tbl_cxt.setData(_value,'#');
    if(t_tbl_cxt.size() == m_tblHead.size() ) {
        IMITableLine t_line;
        for(s32 i=0;i<t_tbl_cxt.size();i++){
            IMITableCell t_cell;
            t_cell.setValue( t_tbl_cxt[i]);
            t_line.m_cells.append(t_cell);
        }
        m_tblCtx.append(t_line);
    }
}

void IMITable::removeCxt(s32 _key) {
    if(!_hasHead)
        return;
}

void IMITable::clearCxt() {
    if(!_hasHead)
        return;
    m_tblCtx.destroy();
}

s32 IMITable::getCtxNum() {
    return m_tblCtx.size();
}

IMIString IMITable::getCtx(s32 _index,cptr8 _name) {
    if(_index>=m_tblCtx.size())
        return "nil";
    if(!_hasHead)
        return "nil";
    s32 t_index = -1;
    for(s32 i=0;i<m_tblHead.size();i++) {
        if(m_tblHead[i] == _name) {
            t_index = i;
            break;
        }
    }
    //
    if(t_index!=-1) {
        return m_tblCtx[_index].getStrValue(t_index);
    }
    return "nil";
}

f32 IMITable::getCtxF(s32 _index,cptr8 _name) {
    IMIString t_value = getCtx(_index,_name);
    if(t_value!="nil") {
        return IMIString::atof(t_value.c_str());
    }
    return 0.0f;
}

s32 IMITable::getCtxI(s32 _index,cptr8 _name) {
    IMIString t_value = getCtx(_index,_name);
    if(t_value!="nil") {
        return IMIString::atoi(t_value.c_str());
    }
    return 1;
}
