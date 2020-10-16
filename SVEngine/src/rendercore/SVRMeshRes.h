//
// SVRMeshRes.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_RES_h
#define SV_RMESH_RES_h

#include "SVRRes.h"
#include "../base/SVPreDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "../core/SVVertDef.h"
#include <vector>

namespace sv {
        
    //1.AOS模式  混合流
    //2.SOA模式  拆分流
    struct SVRMeshDsp;
    class SVRMeshRes: public SVRRes{
    public:
        SVRMeshRes(SVInstPtr _app);
        
        virtual ~SVRMeshRes();
        
        virtual void load(SVRendererPtr _renderer,
                          SVIndexStreamDspPtr _indexdsp,
                          SVVertStreamDspPtr _streamdsp,
                          SVInstStreamDspPtr _instdsp,
                          SVRMeshDsp* _SVRMeshDsp);
        
        virtual void unload();
        
        virtual s32 process(SVRendererPtr _renderer);
        
        virtual void draw(SVRendererPtr _renderer);
        
        void setInstData(SVDataSwapPtr _data);
        
        void setIndexData(SVDataSwapPtr _data);
        
        void setVertData(SVDataSwapPtr _data,s32 _chn);
        
    protected:
        //同步描述
        SVIndexStreamDspPtr m_index_dsp;
        SVVertStreamDspPtr m_vert_dsp;
        SVInstStreamDspPtr m_instance_dsp;
        SVRMeshDsp* m_rmesh_dsp;
        SVLockSpinPtr m_data_lock;
    };
        
}//!namespace sv


#endif /* SV_RMESH_RES_h */
