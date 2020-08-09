//
//  CGInst.m
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import "CGInst.h"
#import "CGUI.h"
#import "CGDef.h"
#include "src/app/SVInst.h"
#include "src/rendercore/SVMetal/SVRendererMetal.h"
#include "src/rendercore/SVGL/SVRendererGL.h"

static CGInst *mInst;

@interface CGInst() {
    sv::SVInstPtr m_pSVE;
}
@end

@implementation CGInst

+(instancetype) getInst{
    if(mInst == nil){
        mInst = [CGInst new];
    }
    return mInst;
}


- (instancetype)init{
    self = [super init];
    if (self) {
        m_pSVE = nullptr;
    }
    return self;
}

-(void)dealloc {
}

-(void)cgInit{
//    //创建SVE引擎
    [self initSVE];
    //创建UI系统
    [[CGUI getInst] cgInit:0];
}

-(void)cgDestroy {
    [[CGUI getInst] cgDestroy];
    [self destroySVE];
}

-(void)initSVE{
    SV_LOG_INFO("sve init begin!");
    m_pSVE = sv::SVInst::makeCreate();
    NSString *t_sveResource = @"sve-metal";
#if SVE_TOOL_USE_METAL
    t_sveResource = @"sve-metal";
#elif SVE_TOOL_USE_GLES
    t_sveResource = @"sve-gles";
#endif
    NSString* t_sve_path = [[NSBundle mainBundle] pathForResource:t_sveResource ofType:@"bundle"];
    t_sve_path = [t_sve_path stringByAppendingString:@"/"];
    m_pSVE->addRespath([t_sve_path UTF8String]);
    m_pSVE->init();
    SV_LOG_INFO("sve init end!");
}

-(void)destroySVE{
    if(m_pSVE) {
        m_pSVE->destroy();
        m_pSVE = nullptr;
    }
}

-(void*)getSVE {
    return m_pSVE.get();
}
/*
  Renderer Metal
 */
-(void)createRM:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
    if( m_pSVE ) {
        sv::SVRendererPtr t_renderer =m_pSVE->createRenderer(sv::E_R_METAL);
        sv::SVRendererMetalPtr t_r_metal = std::dynamic_pointer_cast<sv::SVRendererMetal>(t_renderer);
        if(t_r_metal) {
            //渲染器初始化
            SV_LOG_INFO("sve createRM begin! \n");
            t_r_metal->init(_device,_drawable,_drawable.texture);
            SV_LOG_INFO("sve createRM end! \n");
        }
    }
}

-(void)destroyRM {
    if( m_pSVE ){
        m_pSVE->destroyRenderer();
    }
}

/*
 Renderer OpenGL
 */
- (void)createGLWidth:(int)_w Height:(int)_h{
    if( m_pSVE ) {
        sv::SVRendererPtr t_re =m_pSVE->createRenderer(sv::E_R_GLES);
        sv::SVRendererGLPtr t_re_gles = std::dynamic_pointer_cast<sv::SVRendererGL>(t_re);
        if(t_re_gles) {
            //渲染器初始化
            t_re_gles->init(_w, _h);
        }
    }
}

- (void)destroyGL{
    if( m_pSVE ){
        m_pSVE->destroyRenderer();
    }
}

-(void)render {
    SV_LOG_ERROR("sve render begin!");
    m_pSVE->updateSVE(0.33f);
    m_pSVE->renderSVE();
    SV_LOG_ERROR("sve render end!");
}


@end
