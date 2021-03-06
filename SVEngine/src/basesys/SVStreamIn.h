//
// SVStreamIn.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_STREAMIN_H
#define SV_STREAMIN_H

#include "SVProcess.h"
#include "../node/SVNodeDeclare.h"
#include "../base/SVMap.h"
#include "../mtl/SVMtlDeclare.h"

namespace sv {

    //
    class StreamInCore :public SVGBaseEx {
    public:
        StreamInCore(SVInstPtr _app);
        
        virtual ~StreamInCore();
        
        void init(s32 _w,s32 _h,SV_PIC_FORMATE _informate,f32 _angle,bool _show);
        
        void init(s32 _w,s32 _h,SV_PIC_FORMATE _informate,f32 _angle,bool _show,SV_TEXIN _tex);
        
        void init(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _w,s32 _h,SV_PIC_FORMATE _informate,f32 _angle,bool _show);
        
        void init(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _w,s32 _h,SV_PIC_FORMATE _informate,f32 _angle,bool _show,SV_TEXIN _tex);
        
        void destroy();
        
        void active();
        
        void unactive();
        
        void update(f32 _dt);
        
        void pushData(u8* _srcPtr,s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
        void pushTexture(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
    protected:
        void _updateTrans();
        bool m_useGPU;
        SVTransPtr m_trans;
        SVNodePtr m_showNode;
        SV_TEXIN m_tt;
        SV_PIC_FORMATE m_formate;
        //
        SVTexturePtr m_texResult;
        SVTexturePtr m_tex0;
        SVTexturePtr m_tex1;
        SVTexturePtr m_tex2;
    };
    
    //
    class SVStreamIn : public SVProcess {
    public:
        SVStreamIn(SVInstPtr _app);
        
        ~SVStreamIn();
        
        void createInStream(cptr8 _name,s32 _type,SV_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, bool _show = false);
        
        void createInStream(cptr8 _name,s32 _type,SV_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, SV_TEXIN _tex, bool _show = false);

        void createInTextureStream(cptr8 _name, u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _type,SV_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, bool _show = false);
        
        void destroyInStream(cptr8 _name);
        
        void active(cptr8 _name);
        
        void unactive(cptr8 _name);
        
        void pushStreamData(cptr8 _name,u8* _srcPtr,s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
        void pushTextureStream(cptr8 _name,u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
        void update(f32 _dt);
        
    protected:
        //SV_TEXIN
        typedef SVMap<SVString,StreamInCorePtr> TEXMAP;
        TEXMAP m_TexMap;
        //
        SVLockPtr m_streamLock;
    };
        

}//!namespace sv



#endif //SV_STREAMIN_H
