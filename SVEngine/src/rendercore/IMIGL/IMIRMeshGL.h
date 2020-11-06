//
// IMIRMeshGL.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RMESH_GL_H
#define IMI_RMESH_GL_H

#include "../IMIRMeshRes.h"
#include "IMIRenderDef.h"
#include "../base/IMIPreDeclare.h"
#include "../../core/IMIVertDef.h"
#include <vector>

namespace imi {

    /*
     render mesh gl
     */
    #define MAX_VERTEX_STEAM_NUM 8

    class IMIRMeshGL : public IMIRMeshRes {
    public:
        IMIRMeshGL(IMIInstPtr _app);
        
        ~IMIRMeshGL();
        
        void load(IMIRendererPtr _renderer,
                  IMIIndexStreamDspPtr _indexdsp,
                  IMIVertStreamDspPtr _streamdsp,
                  IMIInstStreamDspPtr _instdsp,
                  IMIRMeshDsp* _IMIRMeshDsp);

        void unload();

        s32 process(IMIRendererPtr _renderer);

        void draw(IMIRendererPtr _renderer);
        
    protected:
        //数据属性
        u32 m_indexID;
        //vbo
        u32 m_bufID[MAX_VERTEX_STEAM_NUM];
        //instance
        u32 m_instanceID;
    };
    

}//!namespace imi


#endif //IMI_RMESH_GL_H
