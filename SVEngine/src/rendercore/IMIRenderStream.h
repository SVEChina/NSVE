//
// IMIRenderStream.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDER_STREAM_H
#define IMI_RENDER_STREAM_H

#include "../base/IMIObject.h"
#include "../work/IMIWorkDeclare.h"
#include "IMIRenderDeclare.h"
#include <vector>

namespace imi {
    
    /*
     只是一个命令流而已，就这么简单，批量处理命令的流
     */

    class IMIRenderStream : public IMIObject {
    public:
        IMIRenderStream();
        
        ~IMIRenderStream();
        
        void addRenderCmd(IMIRenderCmdPtr cmd);
        
        void clearRenderCmd();
        
        void render(IMIRendererPtr _renderer,IMIRTargetPtr _target);
        
        void setValid(bool _valid) { m_valid = _valid; }
        
        bool isValid() { return m_valid; }
        
    protected:
        IMILockSpinPtr m_lock;
        //数据流
        typedef std::vector<IMIRenderCmdPtr> CMDPOOL;
        CMDPOOL m_cmdArray;
        //
        bool m_valid;
    };

}//!namespace imi


#endif //IMI_RENDER_STREAM_H
