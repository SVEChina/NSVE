//
// SVRenderMesh.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERMESH_H
#define SV_RENDERMESH_H

#include "SVRMeshRes.h"
#include "SVRenderDef.h"
#include "../base/SVResDsp.h"
#include "../core/SVVertDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVDataSwap.h"
#include <vector>
#include <map>

namespace sv {

    /*
     逻辑和渲染之间的桥梁，其实就是数据和数据描述
     */
    class SVRenderMesh : public SVGBaseEx { 
    public:
        SVRenderMesh(SVInstPtr _app);
        
        ~SVRenderMesh();
        
        /*
         设置描述
         */
        void setIndexDsp(SVIndexStreamDspPtr _dsp);
        
        void setVertDsp(SVVertStreamDspPtr _dsp);
        
        void setInstanceDsp(SVInstStreamDspPtr _dsp);
        
        /*
         是否使用索引
         */
        bool useIndex();
        
        bool useInstance();
        
        /*
          获取各种描述
         */
        SVIndexStreamDspPtr getIndexDsp();
        
        SVVertStreamDspPtr getStreamDsp();
    
        SVInstStreamDspPtr getInstanceDsp();
        
        SVRMeshDsp* getRMeshDsp();

        /*
         设置数据
         */
        void setIndexData(SVDataSwapPtr _data,s32 _num);
        
        void setVertexData(SVDataSwapPtr _data);
        
        void setVertexData(SVDataSwapPtr _data,s32 _streamnum);
        
        void setInstanceData(SVDataSwapPtr _pdata, u32 _instanceCount);
        
        /*
         //设置渲染模式
         */

        void setDrawMethod(s32 _method);
        
        void setDrawVertNum(s32 _vertexNum);
        
        /*
         内核资源相关
         */
        void bindRes(s32 _instid);
        
        void unbindRes();
        
        SVRMeshResPtr getResBuffer();
        
    protected:
        //BUF描述
        SVIndexStreamDspPtr m_index_dsp;
        SVVertStreamDspPtr m_vert_dsp;
        SVInstStreamDspPtr m_instance_dsp;
        SVRMeshDsp m_rmesh_dsp;
        //
        s32 m_rmesh_id;
    };
    

}//!namespace sv


#endif //SV_RENDERMESH_H
