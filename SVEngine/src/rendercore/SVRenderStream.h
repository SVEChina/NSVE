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
     渲染流 按照材质去分的留
     */
        
    class SVRenderStream : public SVObject {
    public:
        SVRenderStream();
        
        ~SVRenderStream();
        
        void addSVRenderCmd(SVRenderCmdPtr cmd);
        
        void clearSVRenderCmd();
        
        void render();
        
    protected:
        SVLockPtr m_lock;
        typedef SVArray<SVRenderCmdPtr> CMDPOOL;
        CMDPOOL m_cmdArray;
        
        SVRenderTechPtr m_pTech;
    };

    
    
}//!namespace sv


#endif //SV_RENDER_STREAM_H
