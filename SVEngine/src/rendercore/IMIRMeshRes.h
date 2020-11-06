//
// IMIRMeshRes.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RMESH_RES_h
#define IMI_RMESH_RES_h

#include "IMIRRes.h"
#include "../base/IMIPreDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "../core/IMIVertDef.h"
#include <vector>

namespace imi {
        
    //1.AOS模式  混合流
    //2.SOA模式  拆分流
    struct IMIRMeshDsp;
    class IMIRMeshRes: public IMIRRes{
    public:
        IMIRMeshRes(IMIInstPtr _app);
        
        virtual ~IMIRMeshRes();
        
        virtual void load(IMIRendererPtr _renderer,
                          IMIIndexStreamDspPtr _indexdsp,
                          IMIVertStreamDspPtr _streamdsp,
                          IMIInstStreamDspPtr _instdsp,
                          IMIRMeshDsp* _IMIRMeshDsp);
        
        virtual void unload();
        
        virtual s32 process(IMIRendererPtr _renderer);
        
        virtual void draw(IMIRendererPtr _renderer);
        
        void setInstData(IMIDataSwapPtr _data);
        
        void setIndexData(IMIDataSwapPtr _data);
        
        void setVertData(IMIDataSwapPtr _data,s32 _chn);
        
    protected:
        //同步描述
        IMIIndexStreamDspPtr m_index_dsp;
        IMIVertStreamDspPtr m_vert_dsp;
        IMIInstStreamDspPtr m_instance_dsp;
        IMIRMeshDsp* m_rmesh_dsp;
        IMILockSpinPtr m_data_lock;
    };
        
}//!namespace imi


#endif /* IMI_RMESH_RES_h */
