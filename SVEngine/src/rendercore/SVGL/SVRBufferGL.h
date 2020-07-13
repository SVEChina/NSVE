//
// SVRBufferGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RBUFFER_GL_H
#define SV_RBUFFER_GL_H

#include "../SVRBuffer.h"
#include "SVRenderDef.h"
#include "../base/SVPreDeclare.h"
#include "../../core/SVVertDef.h"
#include <vector>

namespace sv {

    /*
     render mesh gl
     */
    #define MAX_VERTEX_STEAM_NUM 8

    class SVRBufferGL : public SVRBuffer {
    public:
        SVRBufferGL(SVInstPtr _app);
        
        ~SVRBufferGL();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        virtual s32 process(SVRendererPtr _renderer);
        
    protected:
        //渲染属性
        DRAWMETHOD m_draw_method;
        s32 m_draw_num;
        //数据属性
        u32 m_indexID;
        //vbo
        u32 m_bufID[MAX_VERTEX_STEAM_NUM];
        s32 m_bufnum;
        //instance
        u32 m_instanceID;
        s32 m_instacne_count;
        //
        std::vector<VFTYPE> m_ver_dsp;
    };
    

}//!namespace sv


#endif //SV_RBUFFER_GL_H
