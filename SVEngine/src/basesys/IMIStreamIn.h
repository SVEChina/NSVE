//
// IMIStreamIn.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_STREAMIN_H
#define IMI_STREAMIN_H

#include "IMIProcess.h"
#include "../node/IMINodeDeclare.h"
#include "../base/IMIMap.h"
#include "../mtl/IMIMtlDeclare.h"

namespace imi {

    //
    class StreamInCore :public IMIGBaseEx {
    public:
        StreamInCore(IMIInstPtr _app);
        
        virtual ~StreamInCore();
        
        void init(s32 _w,s32 _h,IMI_PIC_FORMATE _informate,f32 _angle,bool _show);
        
        void init(s32 _w,s32 _h,IMI_PIC_FORMATE _informate,f32 _angle,bool _show,IMI_TEXIN _tex);
        
        void init(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _w,s32 _h,IMI_PIC_FORMATE _informate,f32 _angle,bool _show);
        
        void init(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _w,s32 _h,IMI_PIC_FORMATE _informate,f32 _angle,bool _show,IMI_TEXIN _tex);
        
        void destroy();
        
        void active();
        
        void unactive();
        
        void update(f32 _dt);
        
        void pushData(u8* _srcPtr,s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
        void pushTexture(u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
    protected:
        void _updateTrans();
        bool m_useGPU;
        IMITransPtr m_trans;
        IMINodePtr m_showNode;
        IMI_TEXIN m_tt;
        IMI_PIC_FORMATE m_formate;
        //
        IMITexturePtr m_texResult;
        IMITexturePtr m_tex0;
        IMITexturePtr m_tex1;
        IMITexturePtr m_tex2;
    };
    
    //
    class IMIStreamIn : public IMIProcess {
    public:
        IMIStreamIn(IMIInstPtr _app);
        
        ~IMIStreamIn();
        
        void createInStream(cptr8 _name,s32 _type,IMI_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, bool _show = false);
        
        void createInStream(cptr8 _name,s32 _type,IMI_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, IMI_TEXIN _tex, bool _show = false);

        void createInTextureStream(cptr8 _name, u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 _type,IMI_PIC_FORMATE _formate,s32 _w,s32 _h,f32 _angle, bool _show = false);
        
        void destroyInStream(cptr8 _name);
        
        void active(cptr8 _name);
        
        void unactive(cptr8 _name);
        
        void pushStreamData(cptr8 _name,u8* _srcPtr,s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
        void pushTextureStream(cptr8 _name,u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, s32 width,s32 height,s32 pixelFormat,s32 _angle);
        
        void update(f32 _dt);
        
    protected:
        //IMI_TEXIN
        typedef IMIMap<IMIString,StreamInCorePtr> TEXMAP;
        TEXMAP m_TexMap;
        //
        IMILockPtr m_streamLock;
    };
        

}//!namespace imi



#endif //IMI_STREAMIN_H
