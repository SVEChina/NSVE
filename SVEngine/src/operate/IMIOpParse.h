//
// IMIOpParse.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPERATEPARSE_H
#define IMI_OPERATEPARSE_H

#include "IMIOpBase.h"
#include "../file/IMIParseAnimate.h"
#include "../base/IMIPreDeclare.h"
#include "../mtl/IMIMtlDeclare.h"

//解析 加载资源文件

namespace imi {
    
    class IMIOpParse : public IMIOpBase {
    public:
        IMIOpParse(IMIInstPtr _app, s32 _resid,cptr8 _path);
        
        IMIOpParse(IMIInstPtr _app, s32 _resid,cptr8 _path, s32 _restype);
        
        
    protected:
        void _process(f32 dt);
        
        s32 resid;      //资源ID
        s32 restype;    //资源类型
        IMIString path;
    };
    
    class IMIOperateDelEft : public IMIOpBase {
    public:
        IMIOperateDelEft(IMIInstPtr _app, s32 _resid);
        
    protected:
        void _process(f32 dt);
        
        s32 resid;
        IMIString scenename;
    };
    
    //
    class IMIOpSaveEft : public IMIOpBase {
    public:
        IMIOpSaveEft(IMIInstPtr _app, s32 _resid, cptr8 _path);
        
    protected:
        void _process(f32 dt);
        
        int resid;
        IMIString scenename;
        IMIString path;
    };
    
    //
    class IMIOpFilterEft : public IMIOpBase {
    public:
        IMIOpFilterEft(IMIInstPtr _app, s32 _resType, s32 _resId);
        
    protected:
        void _process(f32 dt);
        
        s32 resId;      //资源ID
        s32 resType;    //资源类型
    };
    
    //生成节点
    class IMIOpGenerate : public IMIOpBase {
    public:
        IMIOpGenerate(IMIInstPtr _app, IMIParseDataPtr _parsedataPtr, s32 _resid,cptr8 _path);
        
    protected:
        void _process(f32 dt);
        
        IMIParseDataPtr mParseDataPtr;
        s32 mResid;
        IMIString mPath;
    };
    
}//!namespace imi



#endif //IMI_OPERATEPARSE_H
