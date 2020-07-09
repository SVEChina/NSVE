//
// SVRenderStream.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDER_STREAM_H
#define SV_RENDER_STREAM_H

#include "../base/SVObject.h"
#include "SVRenderDeclare.h"

namespace sv {
    
    /*
     只是一个命令流而已，就这么简单，批量处理命令的流
     */

    class SVRenderStream : public SVObject {
    public:
        SVRenderStream();
        
        ~SVRenderStream();
        
        void addRenderCmd(SVRenderCmdPtr cmd);
        
        void clearRenderCmd();
        
        void render(SVRendererPtr _renderer);
        
    protected:
        SVLockPtr m_lock;
        //数据流
        typedef SVArray<SVRenderCmdPtr> CMDPOOL;
        CMDPOOL m_cmdArray;
    };

    
    
}//!namespace sv


#endif //SV_RENDER_STREAM_H
