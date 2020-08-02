//
// SVRenderStream.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDER_STREAM_H
#define SV_RENDER_STREAM_H

#include "../base/SVObject.h"
#include "../work/SVWorkDeclare.h"
#include "SVRenderDeclare.h"
#include <vector>

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
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        void setValid() { m_valid = true; }
        
        bool isValid() { return m_valid; }
        
    protected:
        SVLockSpinPtr m_lock;
        //数据流
        typedef std::vector<SVRenderCmdPtr> CMDPOOL;
        CMDPOOL m_cmdArray;
        //
        bool m_valid;
    };

    
    
}//!namespace sv


#endif //SV_RENDER_STREAM_H
