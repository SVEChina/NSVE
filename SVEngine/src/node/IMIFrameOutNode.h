//
// IMIFrameOutNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FRAMEOUTNODE_H
#define IMI_FRAMEOUTNODE_H

#include "IMINode.h"
#include "../rendercore/IMIRenderDef.h"
#include "../base/IMIPreDeclare.h"

//数据输出节点
//所谓的数据输出 其实就是 fbo

namespace imi {

    class IMIFrameOutNode : public IMINode {
    public:
        IMIFrameOutNode(IMIInstPtr _app);
        
        virtual ~IMIFrameOutNode();
        
        virtual void create(s32 _width,s32 _height);
        
        virtual void destroy();
        
        virtual void update(f32 _dt);
        
        virtual void render();
        
        virtual void lockData();
        
        virtual void unlockData();
        
        virtual void* getData();
        
    protected:
        void* m_pData;
    };

}//!namespace imi



#endif //IMI_FRAMEOUTNODE_H
