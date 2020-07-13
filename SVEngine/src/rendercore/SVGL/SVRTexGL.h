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

            virtual void setTexData(SVDataSwapPtr _data);

            virtual void commit();  //数据提交到显卡
            
            SVDataSwapPtr m_pData;
            
            u32 m_res_id;
        };
//        //PList假纹理
//        class SVRTexGLPlist : public SVRTexGL{
//        public:
//            SVRTexGLPlist(SVInstPtr mApp);
//
//            ~SVRTexGLPlist();
//
//            virtual void refreshParam();
//
//            virtual void apply();
//
//            virtual void apply(void *data);
//
//            void commit();
//
//            SVRect *getSrcRect();
//
//            SVRect *getDstRect();
//
//            void bindTexset(SVRTexGLSetPtr _texset);
//
//            void unbindTexset();
//
//            bool getbLoad();
//
//        public:
//            bool rot;    //是否旋转
//            bool trim;   //是否旋转
//            f32 srcw;   //原有纹理的宽度
//            f32 srch;   //原有纹理的高度
//
//        private:
//            SVRect m_srcRect; //在原图的尺寸
//            SVRect m_dstRect; //在大纹理中的位置
//            SVRTexGLSetPtr m_pTexset;
//        };

//        //
//        //iOS纹理
//        class SVRTexGLiOS : public SVRTexGL {
//        public:
//            SVRTexGLiOS(SVInstPtr mApp);
//
//            ~SVRTexGLiOS();
//
//            virtual void create(SVRendererPtr _renderer);
//
//            virtual void destroy(SVRendererPtr _renderer);
//
//            void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate);
//
//            void fetchData(u8* _dstPtr,s32 _w,s32 _h);
//
//        protected:
//            s32 m_formate;
//#ifdef SV_IOS
//            CVOpenGLESTextureCacheRef m_pTexCacheRef;
//            CVOpenGLESTextureRef m_pTexRef;
//            CVPixelBufferRef m_pPixelBuf;
//#endif
//        };


}//!namespace sv



//
#endif //SV_RTEX_GL_H
