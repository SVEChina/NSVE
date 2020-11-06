//
// IMITable.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef __IMI_TABLE_H__
#define __IMI_TABLE_H__

#include "../base/IMIGBase.h"
#include "imistr.h"
#include "IMIArray.h"
#include "IMIMap.h"

/*
    表
 */
namespace imi {
    
    class IMITableCell {
    public:
        IMITableCell();
        
        IMITableCell &operator=(const IMITableCell &s);
        
        void setValue(cptr8 _value);
        
        void setValue(f32 _value);
        
        void setValue(s32 _value);
        
        cptr8 getStrValue(){ return m_str_value.c_str(); }
        
        s32 getIMIalue() { return m_s_value; }
        
        f32 getFValue() { return m_f_value; }
        
        IMIString m_str_value;
        f32 m_f_value;
        s32 m_s_value;
    };

    //
    class IMITableLine {
    public:
        IMITableLine();

        ~IMITableLine();
        
        IMITableLine &operator=(const IMITableLine &s);
        
        cptr8 getStrValue(s32 _index);
        
        IMIArray<IMITableCell> m_cells;  //表头
    };

    //
    class IMITable{
    public:
        IMITable();

        ~IMITable();
        
        void reset();
        
        void setHead(cptr8 _head);
        
        void pushCxt(cptr8 _value);
        
        void removeCxt(s32 _key);
        
        void clearCxt();
        
        //获取内容
        s32 getCtxNum();
        
        IMIString getCtx(s32 _index,cptr8 _name);
        
        f32 getCtxF(s32 _index,cptr8 _name);
        
        s32 getCtxI(s32 _index,cptr8 _name);
        
    private:
        bool _hasHead;
        IMIArray<IMIString> m_tblHead;  //表头
        IMIArray<IMITableLine> m_tblCtx;  //内容
    };
        
}//!namespace imi

#endif /* __IMI_TABLE_H__ */
