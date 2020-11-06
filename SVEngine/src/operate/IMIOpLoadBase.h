//
// IMIOpLoadBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPLOADBASE_H
#define IMI_OPLOADBASE_H


#include "IMIOpBase.h"

namespace imi {
    
    //
    class IMIOpLoadBase : public IMIOpBase {
    public:
        IMIOpLoadBase(IMIInstPtr _app);
        ~IMIOpLoadBase();
    };
    
    //回收节点
    class IMIOpRecycleNode : public IMIOpBase {
    public:
        IMIOpRecycleNode(IMIInstPtr _app, IMINodePtr _node);
        
    protected:
        void _process(f32 dt);
        
        IMINodePtr m_node;
    };
    
    //拾取包
    class IMIOpPick : public IMIOpBase {
    public:
        IMIOpPick(IMIInstPtr _app, s32 _x,s32 _y);
        
        ~IMIOpPick();
        
    protected:
        void _process(f32 dt);
        s32 m_ui_x;
        s32 m_ui_y;
    };
    
}//!namespace imi



#endif //IMI_OPLOADBASE_H
