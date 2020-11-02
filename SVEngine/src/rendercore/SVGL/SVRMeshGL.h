//
// SVRMeshGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_GL_H
#define SV_RMESH_GL_H

#include "../SVRMeshRes.h"
#include "SVRenderDef.h"
#include "../base/SVPreDeclare.h"
#include "../../core/SVVertDef.h"
#include <vector>

namespace sv {

    /*
     render mesh gl
     */
    #define MAX_VERTEX_STEAM_NUM 8

    class SVRMeshGL : public SVRMeshRes {
    public:
        SVRMeshGL(SVInstPtr _app);
        
        ~SVRMeshGL();
        
        void load(SVRendererPtr _renderer,
                  SVIndexStreamDspPtr _indexdsp,
                  SVVertStreamDspPtr _streamdsp,
                  SVInstStreamDspPtr _instdsp,
                  SVRMeshDsp* _SVRMeshDsp);

        void unload();

        s32 process(SVRendererPtr _renderer);

        void draw(SVRendererPtr _renderer);
        
    protected:
        //数据属性
        u32 m_indexID;
        //vbo
        u32 m_bufID[MAX_VERTEX_STEAM_NUM];
        //instance
        u32 m_instanceID;
    };
    

}//!namespace sv


#endif //SV_RMESH_GL_H
