//
// SVRendererGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERERGL_H
#define SV_RENDERERGL_H

#include "../SVRenderer.h"
#include "../../core/SVVertDef.h"

namespace sv {
        
    /*
     GL渲染器
     */
    
    class SVRendererGL : public SVRenderer {
    public:
        SVRendererGL(SVInstPtr _app);
        
        ~SVRendererGL();
        
        SVRendererGLPtr share();
        
        virtual void init(s32 _w,s32 _h);
        
        virtual void init(s32 _w,s32 _h,bool _offline);
        
        virtual void resize(s32 _w,s32 _);
        
    public:
        //创建部分
        SVRTexPtr createResTexture() ;

        //shader
        SVRShaderPtr createResShader() ;

        //buf-vbo 等
        SVRMeshResPtr createResBuf() ;

        //fbo
        SVRFboPtr createResFbo() ;
        
        //处理材质
        bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface);
        
        //处理纹理
        bool processTexture(SVRTexPtr _tex,s32 _chn,s32 _type);
       
        //处理mesh
        bool processMesh(SVRenderMeshPtr _mesh);
        
        //绘制mesh
        void drawMesh(SVRenderMeshPtr _mesh);
        
        u32 m_cur_program;  //当前的program
        
    public:
        //提交unifrom matrix
        virtual void submitUniformMatrix(cptr8 _name,f32* _data);
        //提交unifrom matrix array
        virtual void submitUniformMatrixArray(cptr8 _name,f32* _data,s32 _size);
        //提交unifrom i1
        virtual void submitUniformi(cptr8 _name,s32 _data);
        //提交unifrom i2
        virtual void submitUniformi2(cptr8 _name,s32 _data1,s32 _data2);
        //提交unifrom i3
        virtual void submitUniformi3(cptr8 _name,s32 _data1,s32 _data2,s32 _data3);
        //提交unifrom i4
        virtual void submitUniformi4(cptr8 _name,s32 _data1,s32 _data2,s32 _data3,s32 _data4);
        //提交unifrom f1
        virtual void submitUniformf(cptr8 _name,f32 _data);
        //提交unifrom f2
        virtual void submitUniformf2(cptr8 _name,f32 _data1,f32 _data2);
        //提交unifrom f3
        virtual void submitUniformf3(cptr8 _name,f32 _data1,f32 _data2,f32 _data3);
        //提交unifrom f4
        virtual void submitUniformf4(cptr8 _name,f32 _data1,f32 _data2,f32 _data3,f32 _data4);
        //提交unifrom s32 v1
        virtual void submitUniformi1v(cptr8 _name,s32* _data,s32 _size = 1);
        //提交unifrom s32 v2
        virtual void submitUniformi2v(cptr8 _name,s32* _data,s32 _size = 1);
        //提交unifrom s32 v3
        virtual void submitUniformi3v(cptr8 _name,s32* _data,s32 _size = 1);
        //提交unifrom s32 v4
        virtual void submitUniformi4v(cptr8 _name,s32* _data,s32 _size = 1);
        //提交unifrom f32 v1
        virtual void submitUniformf1v(cptr8 _name,f32* _data,s32 _size = 1);
        //提交unifrom f32 v2
        virtual void submitUniformf2v(cptr8 _name,f32* _data,s32 _size = 1);
        //提交unifrom f32 v3
        virtual void submitUniformf3v(cptr8 _name,f32* _data,s32 _size = 1);
        //提交unifrom f32 v4
        virtual void submitUniformf4v(cptr8 _name,f32* _data,s32 _size = 1);
        //提交线宽
        virtual void submitLineWidth(f32 _width);
        //提交点大小
        virtual void submitPointSize(f32 _size);
        //FBO
        void svBindFrameBuffer(u32 _id);
        //
        void svBindClearColor(u32 _id);
        //颜色缓存
        void svBindColorBuffer(u32 _id);
        //顶点缓存
        void svBindVertexBuffer(u32 _id);
        //索引缓存
        void svBindIndexBuffer(u32 _id);
        //顶点格式更新
        void svUpdateVertexFormate(VFTYPE _vf,s32 _count = 0,s32 _mode = 1);
        //视口
        void svPushViewPort(u32 _x,u32 _y,u32 _w,u32 _h);
        //
        void svPopViewPort();
        //设置清理颜色
        virtual void svClearColor(f32 _r,f32 _g,f32 _b,f32 _a);
        //设置清理掩码
        virtual void svClear(s32 _mask);
    };

}//!namespace sv




//
#endif //SV_RENDERERGL_H
