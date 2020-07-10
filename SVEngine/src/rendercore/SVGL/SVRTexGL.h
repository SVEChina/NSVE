//
// SVRTexGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RTEX_GL_H
#define SV_RTEX_GL_H

#include "../SVRRes.h"
#include "../SVRTex.h"
#include "../SVRFbo.h"
#include "../SVRShader.h"
#include "../../base/SVPreDeclare.h"
#include "../../base/SVRect.h"
#include "../../core/SVVertDef.h"
#include "../../base/SVDataChunk.h"

namespace sv {

        //纹理资源
        class SVRTexGL: public SVRTex {
        public:
            SVRTexGL(SVInstPtr _app);

            virtual ~SVRTexGL();

            virtual void create(SVRendererPtr _renderer);

            virtual void destroy(SVRendererPtr _renderer);

            virtual void setTexData(void *_data, s32 _len);

            virtual void commit();  //数据提交到显卡
            
            SVDataSwapPtr m_pData;
        };
        
        class SVRTexGLWithTexID: public SVRTexGL {
        public:
            SVRTexGLWithTexID(SVInstPtr _app, s32 _id);
            
            virtual ~SVRTexGLWithTexID();
            
            virtual void create(SVRendererPtr _renderer);
            
            virtual void destroy(SVRendererPtr _renderer);
            
            virtual void setTexID(u32 _texID);
        };
        
        //PList假纹理
        class SVRTexGLPlist : public SVRTexGL{
        public:
            SVRTexGLPlist(SVInstPtr mApp);

            ~SVRTexGLPlist();

            virtual void refreshParam();

            virtual void apply();

            virtual void apply(void *data);

            void commit();

            SVRect *getSrcRect();

            SVRect *getDstRect();

            void bindTexset(SVRTexGLSetPtr _texset);

            void unbindTexset();

            bool getbLoad();

        public:
            bool rot;    //是否旋转
            bool trim;   //是否旋转
            f32 srcw;   //原有纹理的宽度
            f32 srch;   //原有纹理的高度

        private:
            SVRect m_srcRect; //在原图的尺寸
            SVRect m_dstRect; //在大纹理中的位置
            SVRTexGLSetPtr m_pTexset;
        };
        //
        //PList真纹理
        class SVRTexGLSet : public SVRTexGL {
        public:
            SVRTexGLSet(SVInstPtr mApp);

            ~SVRTexGLSet();
        };

        //
        //iOS纹理
        class SVRTexGLiOS : public SVRTexGL {
        public:
            SVRTexGLiOS(SVInstPtr mApp);

            ~SVRTexGLiOS();

            virtual void create(SVRendererPtr _renderer);

            virtual void destroy(SVRendererPtr _renderer);

            void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate);

            void fetchData(u8* _dstPtr,s32 _w,s32 _h);

        protected:
            s32 m_formate;
#ifdef SV_IOS
            CVOpenGLESTextureCacheRef m_pTexCacheRef;
            CVOpenGLESTextureRef m_pTexRef;
            CVPixelBufferRef m_pPixelBuf;
#endif
        };
//        
//        //////////////////////////////////////////////////////////FBO资源
//        class SVRResGLFBO: public SVRFbo {
//        public:
//            SVRResGLFBO(SVInstPtr _app);
//
//            virtual ~SVRResGLFBO();
//
//            virtual void create(SVRendererPtr _renderer);
//
//            virtual void destroy(SVRendererPtr _renderer);
//
//            virtual void refresh();
//
//            virtual void bind();
//            
//            virtual void clear();
//
//            virtual void unbind();
//
//            inline u32 getFboID(){ return m_fboID; }
//
//            inline u32 getWidth(){ return m_width; }
//
//            inline u32 getHeight(){ return m_height; }
//
//            inline bool hasDepth(){ return m_depth; }
//
//            inline bool hasStencil(){ return m_stencil; }
//
//        protected:
//
//            virtual void _bindColor();
//
//            virtual void _bindDepth();
//
//            u32 m_fboID;
//
//            u32 m_depthID;
//
//            s32 m_lastFboID;
//
//            u32 m_width;
//
//            u32 m_height;
//
//            bool m_depth;
//
//            bool m_stencil;
//
//            bool m_dirty;
//
//        };
//
//        //外部传入的FBO
//        class SVRResGLOutFBO : public SVRResGLFBO {
//        public:
//            SVRResGLOutFBO(SVInstPtr _app,u32 _fboid);
//
//            ~SVRResGLOutFBO();
//
//            virtual void create(SVRendererPtr _renderer);
//
//            virtual void destroy(SVRendererPtr _renderer);
//        };
//
//        //RenderTarget
//        class SVResGLRenderTarget : public SVRResGLFBO {
//        public:
//            SVResGLRenderTarget(SVInstPtr _app,s32 _w, s32 _h,bool _depth,bool _stencil);
//
//            ~SVResGLRenderTarget();
//
//            void create(SVRendererPtr _renderer);
//
//            void destroy(SVRendererPtr _renderer);
//
//            inline int getColorID() { return m_colorID; }
//
//        protected:
//            u32 m_colorID;
//        };
//        
//        //
//        class SVResGLRenderTargetOut : public SVResGLRenderTarget {
//        public:
//            SVResGLRenderTargetOut(SVInstPtr _app,s32 _w, s32 _h,u32 _fboid,u32 _colorID);
//
//            ~SVResGLRenderTargetOut();
//
//            void create(SVRendererPtr _renderer);
//
//            void destroy(SVRendererPtr _renderer);
//        };
//        
//        //
//        class SVResGLRenderTexture : public SVRResGLFBO {
//        public:
//            SVResGLRenderTexture(SVInstPtr _app,SVRTexGLPtr _tex, bool _depth,bool _stencil);
//
//            ~SVResGLRenderTexture();
//
//            void create(SVRendererPtr _renderer);
//
//            void destroy(SVRendererPtr _renderer);
//
//            void setTexture(SVRTexGLPtr _tex);
//
//            void refresh();
//
//        protected:
//            void _bindColor();
//
//            SVRTexGLPtr m_tex;
//        };

}//!namespace sv



//
#endif //SV_RTEX_GL_H
