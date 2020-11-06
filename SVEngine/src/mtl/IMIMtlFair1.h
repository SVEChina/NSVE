//
// IMIMtlFair1.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTL_FAIR1_H
#define IMI_MTL_FAIR1_H

#include "IMIMtlCore.h"

namespace imi {
    
    //
    class IMIMtlFilterBrilaterl : public IMIMtlCore {
    public:
        IMIMtlFilterBrilaterl(IMIInstPtr _app);
        
        IMIMtlFilterBrilaterl(IMIMtlFilterBrilaterl *_mtl);
        
        ~IMIMtlFilterBrilaterl();
        
        virtual IMIMtlCorePtr clone();
        
        void setOffset(f32 _offw,f32 _offh);
        
        void setDistance(f32 _dis);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);

        f32 m_texelWidthOffset;
        f32 m_texelHeightOffset;
        f32 m_distanceNormalizationFactor;
        
        bool m_paramDirty;
    };
    
    //
    class IMIMtlFilterBrilaterl2 : public IMIMtlCore {
    public:
        IMIMtlFilterBrilaterl2(IMIInstPtr _app);
        
        IMIMtlFilterBrilaterl2(IMIMtlFilterBrilaterl2 *_mtl);
        
        ~IMIMtlFilterBrilaterl2();
        
        virtual IMIMtlCorePtr clone();
        
        void setOffset(f32 _offw,f32 _offh);
        
        void setDistance(f32 _dis);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        
        f32 m_texelWidthOffset;
        f32 m_texelHeightOffset;
        f32 m_distanceNormalizationFactor;
        
        bool m_paramDirty;
    };
    
    //
    class IMIMtlGaussian : public IMIMtlCore {
    public:
        IMIMtlGaussian(IMIInstPtr _app);
        
        IMIMtlGaussian(IMIMtlGaussian *_mtl);
        
        ~IMIMtlGaussian();
        
        virtual IMIMtlCorePtr clone();
        
        void setRadius(f32 _radius);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_radius;
        //
        bool m_paramDirty;
    };

    class IMIMtlBlur : public IMIMtlCore {
    public:
        IMIMtlBlur(IMIInstPtr _app);
        
        IMIMtlBlur(IMIMtlBlur *_mtl);

        ~IMIMtlBlur();
        
        virtual IMIMtlCorePtr clone();

        void setRadius(f32 _radius);

    protected:
        virtual void _submitMtl(IMIRendererPtr _render);

        f32 m_radius;
        //
        bool m_paramDirty;
    };
    
    class IMIMtlBlurFair : public IMIMtlCore {
    public:
        IMIMtlBlurFair(IMIInstPtr _app);
        
        IMIMtlBlurFair(IMIMtlBlurFair *_mtl);
        
        ~IMIMtlBlurFair();
        
        void setSmooth(f32 _smooth);
        
        virtual void _submitMtl(IMIRendererPtr _render);
        
        virtual IMIMtlCorePtr clone();
        
    protected:
        f32 m_blurAlpha;
    };
    
    class IMIMtlFairLtraLow : public IMIMtlCore {
    public:
        IMIMtlFairLtraLow(IMIInstPtr _app);
        
        IMIMtlFairLtraLow(IMIMtlFairLtraLow *_mtl);
        
        ~IMIMtlFairLtraLow();
        
        void setSmooth(f32 _smooth);
        
        virtual void _submitMtl(IMIRendererPtr _render);
        
        virtual IMIMtlCorePtr clone();
        
    protected:
        f32 m_smooth;
    };
    
    class IMIMtlBlurFairGus : public IMIMtlCore {
    public:
        IMIMtlBlurFairGus(IMIInstPtr _app);
        
        IMIMtlBlurFairGus(IMIMtlBlurFairGus *_mtl);
        
        ~IMIMtlBlurFairGus();
        
        void setSmooth(f32 _smooth);
        
        virtual void _submitMtl(IMIRendererPtr _render);
        
        virtual IMIMtlCorePtr clone();
        
    protected:
        f32 m_smooth;
    };

}//!namespace imi




#endif //IMI_MTL_FAIR1_H
