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
#include "src/env/SVCtxOSX.h"

static CGInst *mInst;

@interface CGInst() {
    sv::SVInstPtr m_sve_obj;
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
        m_sve_obj = nullptr;
    }
    return self;
}

-(void)dealloc {
}

-(void)cgInit{
    //创建SVE引擎
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
    m_sve_obj = sv::SVInst::makeCreate();
    NSString *t_sveResource = @"sve-metal";
#if SVE_TOOL_USE_METAL
    t_sveResource = @"sve-metal";
#elif SVE_TOOL_USE_GLES
    t_sveResource = @"sve-gles";
#endif
    NSString* t_sve_path = [[NSBundle mainBundle] pathForResource:t_sveResource ofType:@"bundle"];
    t_sve_path = [t_sve_path stringByAppendingString:@"/"];
    m_sve_obj->addRespath([t_sve_path UTF8String]);
    m_sve_obj->init();
    SV_LOG_INFO("sve init end!");
}

-(void)destroySVE{
    if(m_sve_obj) {
        m_sve_obj->destroy();
        m_sve_obj = nullptr;
    }
}

-(void*)getSVE {
    return m_sve_obj.get();
}

/*
  Renderer Metal
 */

-(void)createMetal:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
    if( m_sve_obj ) {
        sv::SVCtxBasePtr t_ctx =m_sve_obj->createEnv(sv::E_R_METAL_OSX);
        sv::SVCtxOSXMetalPtr t_ctx_metal = std::dynamic_pointer_cast<sv::SVCtxOSXMetal>(t_ctx);
        if(t_ctx_metal) {
            t_ctx_metal->init(m_sve_obj,_device,_drawable,_drawable.texture);
        }
    }
}

-(void)destroyMetal {
    if( m_sve_obj ){
        m_sve_obj->destroyEnv();
    }
}

/*
 Renderer OpenGL
 */
- (void)createGLWidth:(int)_w Height:(int)_h{
//    if( m_sve_obj ) {
//        sv::SVRendererPtr t_re =m_sve_obj->createRenderer(sv::E_R_GLES);
//        sv::SVRendererGLPtr t_re_gles = std::dynamic_pointer_cast<sv::SVRendererGL>(t_re);
//        if(t_re_gles) {
//            //渲染器初始化
//            t_re_gles->init(_w, _h);
//        }
//    }
}

- (void)destroyGL{
//    if( m_sve_obj ){
//        m_sve_obj->destroyEnv();
//    }
}

-(void)resizeWidth:(int)_w Height:(int)_h {
    //sve引擎重设大小
    if(m_sve_obj) {
        m_sve_obj->resize(_w,_h);
    }
}

-(void)render {
    SV_LOG_ERROR("sve render begin!");
    if(m_sve_obj) {
        m_sve_obj->updateSVE(0.33f);
        m_sve_obj->renderSVE();
    }
    SV_LOG_ERROR("sve render end!");
}


@end
