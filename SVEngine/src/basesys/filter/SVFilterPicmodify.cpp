//
// SVFilterPicmodify.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFilterPicmodify.h"
#include "../../core/SVPass.h"
#include "../../base/SVParamTbl.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"
#include "../../mtl/SVShader.h"
#include "../../mtl/SVMtlCore.h"
#include "../../mtl/SVSurface.h"
#include "../../rendercore/SVRenderer.h"
#include "../../rendercore/SVRenderMgr.h"
#include "../../rendercore/SVRShader.h"

using namespace sv;

SVFilterPicmodify::SVFilterPicmodify(SVInstPtr _app)
:SVFilterBase(_app){
}

SVFilterPicmodify::~SVFilterPicmodify(){
}

//创建
bool SVFilterPicmodify::create() {
//    s32 t_w =  mApp->m_global_param.m_sv_width;
//    s32 t_h =  mApp->m_global_param.m_sv_height;
//    //创建材质
//    m_acutancemtl=MakeSharedPtr<SVMtlAcutance>(mApp);
////    //m_acutancemtl->setTexcoordFlip(1.0f, 1.0f);
////    m_acutancemtl->setTexSizeIndex(0,0.5/t_w,0.5/ t_h);
////    m_acutancemtl->setTexSizeIndex(1,0.5/255.0,0.0);
//    m_baseOnmtl=MakeSharedPtr<SVMtlBasedOn>(mApp);
//    //m_baseOnmtl->setTexcoordFlip(1.0f, 1.0f);
////    m_baseOnmtl->setTexSizeIndex(0,0.5/t_w,0.5/ t_h);
////    m_baseOnmtl->setTexSizeIndex(1,0.5/255.0,0.0);
//    //创建pass
//    m_pass = MakeSharedPtr<SVPass>(mApp);
//    m_pass->setMtl("");
//    SVSurfacePtr t_surface = m_pass->getSurface();
//    if(t_surface) {
//        SVTexturePtr teximg = mApp->getTexMgr()->getTexture("svres/filterimg/facewhitefilter.png", true);
//        t_surface->setTexture(1, teximg, 1);
//    }
    //t_pass1->setMtl(m_baseOnmtl);
    //t_pass1->setInTex(0,E_TEX_MAIN);
    //t_pass1->setInTex(1,teximg);
    //t_pass1->setOutTex(E_TEX_HELP0);
    //t_pass1->mTag = "filter-baseon";
//    //
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>(mApp);
//    //t_pass2->setMtl(m_acutancemtl);
//    t_pass2->setInTex(0, E_TEX_HELP0);
//    t_pass2->setOutTex(E_TEX_MAIN);
//    t_pass2->mTag = "write-back";
//    m_pPassNode->addPass(t_pass2);
    return true;
}

//void SVFilterPicmodify::setFilterParam(f32 _value,SVFILTERITEMTYPE _type){
////    if (m_mtl) {
////        if(_type==E_SHADOWS_FILTER){
////            setShadows(-_value*0.01f);
////        }else if(_type==E_CONTRAST_FILTER){
////            setContrast(_value*0.01f);
////        }else if(_type==E_SATURATION_FILTER){
////            setSaturation(_value*0.01f);
////        }else if(_type==E_BRIGHTNESS_FILTER){
////            setBrightness(_value*0.01f);
////        }else if(_type==E_WHITENING_FILTER){
////            setWhitening(_value*0.01f);
////        }else if(_type==E_HIGHLIGHTS_FILTER){
////            setHighlights(_value*0.01f);
////        }else if(_type==E_GAMMA_FILTER){
////            if(_value==-100){
////                setGamma(-1.0);
////            }else{
////                setGamma((_value+100.0)/100.0);
////            }
////        }else if(_type==E_REDSHIFT_FILTER){
////            setRedShift(_value);
////        }else if(_type==E_GREENSHIFT_FILTER){
////            setGreenShift(_value);
////        }else if(_type==E_BLUESHIFT_FILTER){
////            setBlueShift(_value);
////        }else if(_type==E_SDREDSHIFT_FILTER){
////            setSDRedShift(_value);
////        }else if(_type==E_SDGREENSHIFT_FILTER){
////            setSDGreenShift(_value);
////        }else if(_type==E_SDBLUESHIFT_FILTER){
////            setSDBlueShift(_value);
////        }else if(_type==E_HHREDSHIFT_FILTER){
////            setHHRedShift(_value);
////        }else if(_type==E_HHGREENSHIFT_FILTER){
////            setHHGreenShift(_value);
////        }else if(_type==E_HHBLUESHIFT_FILTER){
////            setHHBlueShift(_value);
////        }else if(_type==E_TEMPERATURE_FILTER){
////            float _temperature=(_value+100)/100.0*5000;
////            _temperature=_temperature < 5000 ? 0.0004 * (_temperature-5000.0) : 0.00006 * (_temperature-5000.0);
////            setTemperature(_temperature);
////        }else if(_type==E_TINT_FILTER){
////            setTint(_value);
////        }
////    }
////    if(m_acutancemtl){
////        if(_type==E_ACUTANCE_FILTER){
////            setAcutance(_value/100.0);
////        }
////    }
//}
//
//f32 SVFilterPicmodify::getFilterParam(SVFILTERITEMTYPE _type){
////    if(_type==E_SHADOWS_FILTER){
////        return getShadows();
////    }else if(_type==E_CONTRAST_FILTER){
////        return getContrast();
////    }else if(_type==E_SATURATION_FILTER){
////        return getSaturation();
////    }else if(_type==E_BRIGHTNESS_FILTER){
////        return getBrightness();
////    }else if(_type==E_WHITENING_FILTER){
////        return getWhitening();
////    }else if(_type==E_HIGHLIGHTS_FILTER){
////        return getHighlights();
////    }else if(_type==E_GAMMA_FILTER){
////        return getGamma();
////    }else if(_type==E_REDSHIFT_FILTER){
////        return getRedShift();
////    }else if(_type==E_GREENSHIFT_FILTER){
////        return getGreenShift();
////    }else if(_type==E_BLUESHIFT_FILTER){
////        return getBlueShift();
////    }else if(_type==E_SDREDSHIFT_FILTER){
////        return getSDRedShift();
////    }else if(_type==E_SDGREENSHIFT_FILTER){
////        return getSDGreenShift();
////    }else if(_type==E_SDBLUESHIFT_FILTER){
////        return getSDBlueShift();
////    }else if(_type==E_HHREDSHIFT_FILTER){
////        return getHHRedShift();
////    }else if(_type==E_HHGREENSHIFT_FILTER){
////        return getHHGreenShift();
////    }else if(_type==E_HHBLUESHIFT_FILTER){
////        return getHHBlueShift();
////    }else if(_type==E_TEMPERATURE_FILTER){
////        return getTint();
////    }else if(_type==E_TINT_FILTER){
////        return getTint();
////    }else if(_type==E_ACUTANCE_FILTER){
////        return getAcutance();
////    }
//    return 0;
//}

//销毁
void SVFilterPicmodify::destroy() {
}

void SVFilterPicmodify::update(f32 _dt){
//    if( m_mtl && m_mtl->getShader() ){
////        SVSurfacePtr t_surface = m_pass->getSurface();
////        t_surface->setParam("u_shadows", m_shadows);
////        t_surface->setParam("u_highlights", m_highlights);
////        t_surface->setParam("u_contrast", m_contrast);
////        t_surface->setParam("u_saturation", m_saturation);
////        t_surface->setParam("u_brightness", m_brightness);
////        t_surface->setParam("u_whitening", m_whitening);
////        t_surface->setParam("u_gamma", m_gamma);
////        t_surface->setParam("u_redShift", m_redShift);
////        t_surface->setParam("u_greenShift", m_greenShift);
////        t_surface->setParam("u_blueShift", m_blueShift);
////        t_surface->setParam("u_sdredShift", m_sdredShift);
////        t_surface->setParam("u_sdgreenShift", m_sdgreenShift);
////        t_surface->setParam("u_sdblueShift", m_sdblueShift);
////        t_surface->setParam("u_hhredShift", m_hhredShift);
////        t_surface->setParam("u_hhgreenShift", m_hhgreenShift);
////        t_surface->setParam("u_hhblueShift", m_hhblueShift);
////        t_surface->setParam("u_tint", m_tint);
////        t_surface->setParam("u_temperature", m_temperature);
//        //SVShaderPtr t_shader = m_mtl->getShader();
//        //t_shader->submitParam(<#SVParamTblPtr _param#>)
//    }
////    m_pass->update(_dt);
////    //
////    if(m_acutancemtl){
////        m_acutancemtl->setAcutance(m_acutance);
////    }
}
