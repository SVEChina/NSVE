//
// IMIRenderMesh.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDERMESH_H
#define IMI_RENDERMESH_H

#include "IMIRMeshRes.h"
#include "IMIRenderDef.h"
#include "../base/IMIResDsp.h"
#include "../core/IMIVertDef.h"
#include "../mtl/IMIShaderMgr.h"
#include "../base/IMIPreDeclare.h"
#include "../base/IMIDataSwap.h"
#include <vector>
#include <map>

namespace imi {

    /*
     逻辑和渲染之间的桥梁，其实就是数据和数据描述
     */
    class IMIRenderMesh : public IMIGBaseEx { 
    public:
        IMIRenderMesh(IMIInstPtr _app);
        
        ~IMIRenderMesh();
        
        IMIRenderMeshPtr share();
        
        /*
         设置描述
         */
        void setIndexDsp(IMIIndexStreamDspPtr _dsp);
        
        void setVertDsp(IMIVertStreamDspPtr _dsp);
        
        void setInstanceDsp(IMIInstStreamDspPtr _dsp);
        
        void dispatch();
        
        /*
         是否使用索引
         */
        bool useIndex();
        
        bool useInstance();
        
        /*
          获取各种描述
         */
        IMIIndexStreamDspPtr getIndexDsp();
        
        IMIVertStreamDspPtr getStreamDsp();
    
        IMIInstStreamDspPtr getInstanceDsp();
        
        IMIRMeshDsp* getRMeshDsp();

        /*
         设置数据
         */
        void setIndexData(IMIDataSwapPtr _data,s32 _num);
        
        void setVertexData(IMIDataSwapPtr _data);
        
        void setVertexData(IMIDataSwapPtr _data,s32 _streamnum);
        
        void setInstanceData(IMIDataSwapPtr _pdata, u32 _instanceCount);
        
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
        
        IMIRMeshResPtr getResBuffer();
        
    protected:
        //BUF描述
        IMIIndexStreamDspPtr m_index_dsp;
        IMIVertStreamDspPtr m_vert_dsp;
        IMIInstStreamDspPtr m_instance_dsp;
        IMIRMeshDsp m_rmesh_dsp;
        //
        s32 m_rmesh_id;
    };
    

}//!namespace imi


#endif //IMI_RENDERMESH_H
