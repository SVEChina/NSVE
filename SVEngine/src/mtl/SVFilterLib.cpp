//
// SVFilterLib.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFilterLib.h"
#include "../app/SVInst.h"
#include "../file/SVFileMgr.h"
#include "SVFilterBase.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVScene.h"

using namespace sv;

SVFilterBasePtr SVFilterLib::openFilter(SVInstPtr _app,FTTYPE _name,SV_TEXIN _texin) {
    SVFilterBasePtr t_filter = MakeSharedPtr<SVFilterBase>(_app);
    t_filter->setPostProcess();
    t_filter->setTargetQuene(E_TEX_MAIN);
    t_filter->setTargetSwap(E_TEX_MAIN);
    t_filter->setTargetUse(_texin);
    if(_name == FILTER_GRAY) {
        t_filter->setName("filterGray");
        t_filter->setMtl("filterGray");
        SVSurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            SVTexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
            t_surface->setTexture(1, 0, _tex);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
        }
        _app->getSceneMgr()->addFilter("filterGray", t_filter);
    }else if(_name == FILTER_HAZE) {
        t_filter->setName("filterHaze");
        t_filter->setMtl("filterHaze");
        SVSurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            SVTexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
            t_surface->setTexture(1, 0, _tex);
            t_surface->setParam("dis", 0.1f);
            t_surface->setParam("slope", 0.1f);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
            FVec3 t_haze_color = FVec3(1.0f,0.0f,1.0f);
            t_surface->setParam("hazeColor", t_haze_color);
        }
        _app->getSceneMgr()->addFilter("filterHaze", t_filter);
    }else if(_name == FILTER_HUE) {
        t_filter->setName("filterHue");
        t_filter->setMtl("filterHue");
        SVSurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            SVTexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
            t_surface->setTexture(1, 0, _tex);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
            t_surface->setParam("hueAdjust", 0.1f);
        }
        _app->getSceneMgr()->addFilter("filterHue", t_filter);
    }else if(_name == FILTER_BLUR) {
        t_filter->setMtl("filterBlur"); //filterGray
        
    }else if(_name == FILTER_SHARP) {
        t_filter->setMtl("filterSharp"); //filterGray
        
    }else if(_name == FILTER_LUT) {
        t_filter->setName("filterLUT");
        t_filter->setMtl("filterLUT");
        SVSurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            SVTexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
            SVTexturePtr _tex_img = _app->getTexMgr()->getTexture("res/filterimg/facewhitefilter.png");
            t_surface->setTexture(1, 0, _tex);
            t_surface->setTexture(1, 1, _tex_img);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
        }
        _app->getSceneMgr()->addFilter("filterLUT", t_filter);
    }else if(_name == FILTER_HDR) {
        t_filter->setName("filterHDR");
        t_filter->setMtl("filterHDR");
        SVSurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            SVTexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
            t_surface->setTexture(1, 0, _tex);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
            FVec2 t_size = FVec2(_tex->getTextureDsp()->m_width,
                                 _tex->getTextureDsp()->m_height);
            t_surface->setParam("hdr_size", t_size);
        }
        _app->getSceneMgr()->addFilter("filterHDR", t_filter);
    }
    return t_filter;
}

bool SVFilterLib::closeFilter(SVInstPtr _app,FTTYPE _name) {
    SVString t_filter_name = "";
    if(_name == FILTER_GRAY) {
        t_filter_name = "filterGray";
    }else if(_name == FILTER_HAZE) {
        t_filter_name = "filterHaze";
    }else if(_name == FILTER_HUE) {
        t_filter_name = "filterHue";
    }else if(_name == FILTER_BLUR) {
        t_filter_name = "filterBlur";
    }else if(_name == FILTER_SHARP) {
        t_filter_name = "filterSharp";
    }else if(_name == FILTER_LUT) {
        t_filter_name = "filterLUT";
    }
    return _app->getSceneMgr()->delFilter(t_filter_name.c_str());
}

SVFilterBasePtr SVFilterLib::getFilter(SVInstPtr _app,FTTYPE _name) {
    SVString t_filter_name = "";
    if(_name == FILTER_GRAY) {
        t_filter_name = "filterGray";
    }else if(_name == FILTER_HAZE) {
        t_filter_name = "filterHaze";
    }else if(_name == FILTER_HUE) {
        t_filter_name = "filterHue";
    }else if(_name == FILTER_BLUR) {
        t_filter_name = "filterBlur";
    }else if(_name == FILTER_SHARP) {
        t_filter_name = "filterSharp";
    }else if(_name == FILTER_LUT) {
        t_filter_name = "filterLUT";
    }
    return _app->getSceneMgr()->getFilter(t_filter_name.c_str());
}

//特殊效果
void SVFilterLib::openGOF(SVInstPtr _app,SV_TEXIN _target) {
    //main-gof1
    SVFilterBasePtr t_gof1 = MakeSharedPtr<SVFilterBase>(_app);
    t_gof1->setPostProcess();
    //t_gof1->setTargetQuene(_target);
    t_gof1->setTargetSwap(E_TEX_END);
//    t_gof1->setName("filterLUT");
//    t_gof1->setMtl("filterLUT");
    SVSurfacePtr t_surface = t_gof1->getSurface();
    if(t_surface) {
//        SVTexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
//        SVTexturePtr _tex_img = _app->getTexMgr()->getTexture("res/filterimg/facewhitefilter.png");
//        t_surface->setTexture(1, 0, _tex);
//        t_surface->setTexture(1, 1, _tex_img);
//        FVec2 t_invert = FVec2(1.0f,1.0f);
//        t_surface->setParam("u_invert", t_invert);
    }
    _app->getSceneMgr()->addFilter("gof1", t_gof1);
    //gof1-gof2
    SVFilterBasePtr t_gof2 = MakeSharedPtr<SVFilterBase>(_app);
    t_gof2->setPostProcess();
    //t_gof2->setTargetQuene(_target);
    //t_gof2->setTargetSwap(E_TEX_MAIN);
    _app->getSceneMgr()->addFilter("gof2", t_gof2);
    //main + gof2 -> result
    SVFilterBasePtr t_gof3 = MakeSharedPtr<SVFilterBase>(_app);
    t_gof3->setPostProcess();
    //t_gof2->setTargetQuene(_target);
    t_gof2->setTargetSwap(E_TEX_MAIN);
    _app->getSceneMgr()->addFilter("gof3", t_gof3);
    //swap
}

void SVFilterLib::clostGOF(SVInstPtr _app) {
    _app->getSceneMgr()->delFilter("gof1");
    _app->getSceneMgr()->delFilter("gof2");
    _app->getSceneMgr()->delFilter("gof3");
}

void SVFilterLib::openBeauty(SVInstPtr _app,SV_TEXIN _target) {
    
}

void SVFilterLib::clostBeauty(SVInstPtr _app) {
    
}
