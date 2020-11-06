//
// IMIFilterLib.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFilterLib.h"
#include "../app/IMIInst.h"
#include "../file/IMIFileMgr.h"
#include "IMIFilterBase.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMIScene.h"

using namespace imi;

IMIFilterBasePtr IMIFilterLib::openFilter(IMIInstPtr _app,FTTYPE _name,IMI_TEXIN _texin) {
    IMIFilterBasePtr t_filter = MakeSharedPtr<IMIFilterBase>(_app);
    t_filter->setPostProcess();
    t_filter->setTargetQuene(E_TEX_MAIN);
    t_filter->setTargetSwap(E_TEX_MAIN);
    t_filter->setTargetUse(_texin);
    if(_name == FILTER_GRAY) {
        t_filter->setName("filterGray");
        t_filter->setMtl("filterGray");
        IMISurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            IMITexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
            t_surface->setTexture(1, 0, _tex);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
        }
        _app->getSceneMgr()->addFilter("filterGray", t_filter);
    }else if(_name == FILTER_HAZE) {
        t_filter->setName("filterHaze");
        t_filter->setMtl("filterHaze");
        IMISurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            IMITexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
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
        IMISurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            IMITexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
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
        IMISurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            IMITexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
            IMITexturePtr _tex_img = _app->getTexMgr()->getTexture("res/filterimg/facewhitefilter.png");
            t_surface->setTexture(1, 0, _tex);
            t_surface->setTexture(1, 1, _tex_img);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
        }
        _app->getSceneMgr()->addFilter("filterLUT", t_filter);
    }else if(_name == FILTER_HDR) {
        t_filter->setName("filterHDR");
        t_filter->setMtl("filterHDR");
        IMISurfacePtr t_surface = t_filter->getSurface();
        if(t_surface) {
            IMITexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
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

bool IMIFilterLib::closeFilter(IMIInstPtr _app,FTTYPE _name) {
    IMIString t_filter_name = "";
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

IMIFilterBasePtr IMIFilterLib::getFilter(IMIInstPtr _app,FTTYPE _name) {
    IMIString t_filter_name = "";
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
void IMIFilterLib::openGOF(IMIInstPtr _app,IMI_TEXIN _target) {
    //main-gof1
    IMIFilterBasePtr t_gof1 = MakeSharedPtr<IMIFilterBase>(_app);
    t_gof1->setPostProcess();
    //t_gof1->setTargetQuene(_target);
    t_gof1->setTargetSwap(E_TEX_END);
//    t_gof1->setName("filterLUT");
//    t_gof1->setMtl("filterLUT");
    IMISurfacePtr t_surface = t_gof1->getSurface();
    if(t_surface) {
//        IMITexturePtr _tex = _app->getTexMgr()->getInTexture(E_TEX_MAIN);
//        IMITexturePtr _tex_img = _app->getTexMgr()->getTexture("res/filterimg/facewhitefilter.png");
//        t_surface->setTexture(1, 0, _tex);
//        t_surface->setTexture(1, 1, _tex_img);
//        FVec2 t_invert = FVec2(1.0f,1.0f);
//        t_surface->setParam("u_invert", t_invert);
    }
    _app->getSceneMgr()->addFilter("gof1", t_gof1);
    //gof1-gof2
    IMIFilterBasePtr t_gof2 = MakeSharedPtr<IMIFilterBase>(_app);
    t_gof2->setPostProcess();
    //t_gof2->setTargetQuene(_target);
    //t_gof2->setTargetSwap(E_TEX_MAIN);
    _app->getSceneMgr()->addFilter("gof2", t_gof2);
    //main + gof2 -> result
    IMIFilterBasePtr t_gof3 = MakeSharedPtr<IMIFilterBase>(_app);
    t_gof3->setPostProcess();
    //t_gof2->setTargetQuene(_target);
    t_gof2->setTargetSwap(E_TEX_MAIN);
    _app->getSceneMgr()->addFilter("gof3", t_gof3);
    //swap
}

void IMIFilterLib::clostGOF(IMIInstPtr _app) {
    _app->getSceneMgr()->delFilter("gof1");
    _app->getSceneMgr()->delFilter("gof2");
    _app->getSceneMgr()->delFilter("gof3");
}

void IMIFilterLib::openBeauty(IMIInstPtr _app,IMI_TEXIN _target) {
    
}

void IMIFilterLib::clostBeauty(IMIInstPtr _app) {
    
}
