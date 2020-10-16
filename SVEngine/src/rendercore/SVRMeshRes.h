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
        
        virtual void create(SVRendererPtr _renderer,
                            SVBufferDspPtr _indexdsp,
                            SVBufferDspPtr _streamdsp,
                            SVBufferDspPtr _instdsp,
                            SVRMeshDsp* _SVRMeshDsp);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        virtual s32 process(SVRendererPtr _renderer);
        
        virtual void draw(SVRendererPtr _renderer);
        
        void setInstData(SVDataSwapPtr _data);
        
        void setIndexData(SVDataSwapPtr _data);
        
        void setVertData(SVDataSwapPtr _data,s32 _chn);
        
    protected:
        //同步描述
        SVBufferDspPtr m_index_dsp;
        SVBufferDspPtr m_vert_dsp;
        SVBufferDspPtr m_instance_dsp;
        SVRMeshDsp* m_rmesh_dsp;
        
        SVLockSpinPtr m_data_lock;
        
        SVDataSwapPtr m_index;
        
        SVDataSwapPtr m_inst;
        //
        struct InVertDataUp {
            s32 _chn;
            SVDataSwapPtr _data;
        };
        std::vector<InVertDataUp> m_verts;
    };
        
}//!namespace sv


#endif /* SV_RMESH_RES_h */
