//
//  IMIBrightnessMtl.hpp
//  IMIngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef IMI_MTLBRIGHTNESSCONTRAST_H
#define IMI_MTLBRIGHTNESSCONTRAST_H

#include "IMIMtlCore.h"

namespace imi {
    
    class IMIMtlBrightnessContrast : public IMIMtlCore  {
    public:
        IMIMtlBrightnessContrast(IMIInstPtr _app);
        
        IMIMtlBrightnessContrast(IMIMtlBrightnessContrast* _mtl);
        
        ~IMIMtlBrightnessContrast();
        
        virtual IMIMtlCorePtr clone();
        
        void setBrightness(f32 _smooth);
        
        void setContrast(f32 _smooth);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_brightness;
        f32 m_contrast;
    };
    
    class IMIMtlSaturation : public IMIMtlCore  {
    public:
        IMIMtlSaturation(IMIInstPtr _app);
        
        IMIMtlSaturation(IMIMtlSaturation* _mtl);
        
        ~IMIMtlSaturation();
        
        virtual IMIMtlCorePtr clone();
        
        void setSaturation(f32 _smooth);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_saturation;
    };
    
    class IMIMtlVibrance : public IMIMtlCore  {
    public:
        IMIMtlVibrance(IMIInstPtr _app);
        
        IMIMtlVibrance(IMIMtlVibrance* _mtl);
        
        ~IMIMtlVibrance();
        
        virtual IMIMtlCorePtr clone();
        
        void setVibrance(f32 _smooth);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_vibrance;
    };
    
    class IMIMtlShadowHighlight : public IMIMtlCore  {
    public:
        IMIMtlShadowHighlight(IMIInstPtr _app);
        
        IMIMtlShadowHighlight(IMIMtlShadowHighlight* _mtl);
        
        ~IMIMtlShadowHighlight();
        
        virtual IMIMtlCorePtr clone();
        
        void setShadow(f32 _smooth){
            m_shadow=_smooth;
        }
        
        void setHighlight(f32 _smooth){
            m_HighLight=_smooth;
        }
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_shadow;
        f32 m_HighLight;
        
    };
    
    class IMIMtlWhiteBlackLevel : public IMIMtlCore  {
    public:
        IMIMtlWhiteBlackLevel(IMIInstPtr _app);
        
        IMIMtlWhiteBlackLevel(IMIMtlWhiteBlackLevel* _mtl);
        
        ~IMIMtlWhiteBlackLevel();
        
        virtual IMIMtlCorePtr clone();
        
        void setShadow(f32 _smooth){
            m_shadow=_smooth;
        }
        
        void setHighlight(f32 _smooth){
            m_HighLight=_smooth;
        }
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_shadow;
        f32 m_HighLight;
    };
    
    class IMIMtlColorBalance: public IMIMtlCore  {
    public:
        IMIMtlColorBalance(IMIInstPtr _app);
        
        IMIMtlColorBalance(IMIMtlColorBalance* _mtl);
        
        ~IMIMtlColorBalance();
        
        inline void setRedShift(f32 _redShift){
            m_redShift=_redShift;
        }
        inline void setBlueShift(f32 _blueShift){
            m_blueShift=_blueShift;
        }
        inline void setGreenShift(f32 _greenShift){
            m_greenShift=_greenShift;
        }
        inline void setSDRedShift(f32 _sdredShift){
            m_sdredShift=_sdredShift;
        }
        inline void setSDGreenShift(f32 _sdgreenShift){
            m_sdgreenShift=_sdgreenShift;
        }
        inline void setSDBlueShift(f32 _sdblueShift){
            m_sdblueShift=_sdblueShift;
        }
        inline void setHHRedShift(f32 _hhredShift){
            m_hhredShift=_hhredShift;
        }
        inline void setHHGreenShift(f32 _hhgreenShift){
            m_hhgreenShift=_hhgreenShift;
        }
        inline void setHHBlueShift(f32 _hhblueShift){
            m_hhblueShift=_hhblueShift;
        }
        
        virtual IMIMtlCorePtr clone();
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        f32 m_redShift;
        f32 m_greenShift;
        f32 m_blueShift;
        f32 m_sdredShift;
        f32 m_sdgreenShift;
        f32 m_sdblueShift;
        f32 m_hhredShift;
        f32 m_hhgreenShift;
        f32 m_hhblueShift;
    };
    
    class IMIMtlHSL : public IMIMtlCore  {
    public:
        IMIMtlHSL(IMIInstPtr _app);
        
        IMIMtlHSL(IMIMtlHSL* _mtl);
        
        ~IMIMtlHSL();
        
        virtual IMIMtlCorePtr clone();

        inline void setSaturationRed(f32 _smooth){
            m_saturationRed=_smooth;
        }

        inline  void setHueRed(f32 _smooth){
            m_HueRed=_smooth;
        }

        inline  void setLightnessRed(f32 _smooth){
            m_LightnessRed=_smooth;
        }

        inline void setSaturationYellow(f32 _smooth){
            m_saturationYellow=_smooth;
        }

        inline void setHueYellow(f32 _smooth){
            m_HueYellow=_smooth;
        }

        inline void setLightnessYellow(f32 _smooth){
            m_LightnessYellow=_smooth;
        }

        inline  void setSaturationGreen(f32 _smooth){
            m_saturationGreen=_smooth;
        }

        inline void setHueGreen(f32 _smooth){
            m_HueGreen=_smooth;
        }

        inline void setLightnessGreen(f32 _smooth){
            m_LightnessGreen=_smooth;
        }

        inline void setSaturationMagenta(f32 _smooth){
            m_saturationMagenta=_smooth;
        }

        inline void setHueMagenta(f32 _smooth){
            m_HueMagenta=_smooth;
        }

        inline void setLightnessMagenta(f32 _smooth){
            m_LightnessMagenta=_smooth;
        }

        inline void setSaturationBlue(f32 _smooth){
            m_saturationBlue=_smooth;
        }

        inline void setHueBlue(f32 _smooth){
            m_HueBlue=_smooth;
        }

        inline  void setLightnessBlue(f32 _smooth){
            m_LightnessBlue=_smooth;
        }
        
        inline void  setSaturationCyan(f32 _smooth){
            m_saturationCyan=_smooth;
        }
        
        inline void setHueCyan(f32 _smooth){
            m_HueCyan=_smooth;
        }
        
        inline void setLightnessCyan(f32 _smooth){
            m_LightnessCyan=_smooth;
        }
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_saturationRed;
        f32 m_HueRed;
        f32 m_LightnessRed;
        
        f32 m_saturationYellow;
        f32 m_HueYellow;
        f32 m_LightnessYellow;
        
        f32 m_saturationGreen;
        f32 m_HueGreen;
        f32 m_LightnessGreen;
        
        f32 m_saturationMagenta;
        f32 m_HueMagenta;
        f32 m_LightnessMagenta;
        
        f32 m_saturationBlue;
        f32 m_HueBlue;
        f32 m_LightnessBlue;
        
        f32 m_saturationCyan;
        f32 m_HueCyan;
        f32 m_LightnessCyan;
        
    };
    
    class IMIMtlWhiteBalance : public IMIMtlCore  {
    public:
        IMIMtlWhiteBalance(IMIInstPtr _app);
        
        IMIMtlWhiteBalance(IMIMtlWhiteBalance* _mtl);
        
        ~IMIMtlWhiteBalance();
        
        virtual IMIMtlCorePtr clone();
        
        void setTemperature(f32 _smooth);
        
        void setTint(f32 _smooth);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_Temperature;
        f32 m_Tint;
    };
    
    class IMIMtlGamma : public IMIMtlCore  {
    public:
        IMIMtlGamma(IMIInstPtr _app);
        
        IMIMtlGamma(IMIMtlGamma* _mtl);
        
        ~IMIMtlGamma();
        
        virtual IMIMtlCorePtr clone();
        
        void setGamma(f32 _smooth);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_Gamma;
    };
    
    class IMIMtlExposure : public IMIMtlCore  {
    public:
        IMIMtlExposure(IMIInstPtr _app);
        
        IMIMtlExposure(IMIMtlExposure* _mtl);
        
        ~IMIMtlExposure();
        
        virtual IMIMtlCorePtr clone();
        
        void setExposure(f32 _smooth);
        
    protected:
        virtual void _submitMtl(IMIRendererPtr _render);
        //
        f32 m_Exposure;
    };
        
    
    
}//!namespace imi


#endif /* IMI_MTLBRIGHTNESSCONTRAST_H */

