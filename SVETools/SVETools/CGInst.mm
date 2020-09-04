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
    NSString *t_sve_res = @"sve-metal";
    if(SVE_CORE == SVE_GLES ) {
        t_sve_res = @"sve-gles";
    }else if( SVE_CORE == SVE_METAL ) {
        t_sve_res = @"sve-metal";
    }else if( SVE_CORE == SVE_GL ) {
        t_sve_res = @"sve-gl";
    }
    NSString* t_sve_path = [[NSBundle mainBundle] pathForResource:t_sve_res ofType:@"bundle"];
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

//创建OSX-Metal
-(void)create_OSX_Metal:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
#ifdef SV_OSX
    if( m_sve_obj ) {
        sv::SVCtxBasePtr t_ctx =m_sve_obj->createEnv(sv::E_R_METAL_OSX);
        sv::SVCtxOSXMetalPtr t_ctx_metal = std::dynamic_pointer_cast<sv::SVCtxOSXMetal>(t_ctx);
        if(t_ctx_metal) {
            t_ctx_metal->init(m_sve_obj,_device,_drawable,_drawable.texture);
        }
    }
#endif
}

//创建IOS-Metal
-(void)create_IOS_Metal:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
#ifdef SV_IOS
    if( m_sve_obj ) {
        sv::SVCtxBasePtr t_ctx = m_sve_obj->createEnv(sv::E_R_METAL_OSX);
        sv::SVCtxOSXMetalPtr t_ctx_metal_osx = std::dynamic_pointer_cast<sv::SVCtxOSXMetal>(t_ctx);
        if(t_ctx_metal_osx) {
            t_ctx_metal_osx->init(m_sve_obj,_device,_drawable,_drawable.texture);
        }
    }
#endif
}

-(void)destroyMetal {
    if( m_sve_obj ){
        //m_sve_obj->destroyEnv();
    }
}

/*
 Renderer OpenGL
 */
//创建OSX-GL环境
- (void)create_OSX_GL:(void*)_ctx Width:(int)_w Height:(int)_h Version:(int)_version {
#ifdef SV_OSX
    if( m_sve_obj ) {
        sv::SVCtxBasePtr t_ctx_base = m_sve_obj->createEnv(sv::E_R_GL_OSX);
        sv::SVCtxOSXGLPtr t_ctx_gl_osx = std::dynamic_pointer_cast<sv::SVCtxOSXGL>(t_ctx_base);
        if(t_ctx_gl_osx) {
            t_ctx_gl_osx->init(m_sve_obj,_ctx,_w,_h,_version);
        }
    }
#endif
}

//创建IOS-GL环境
- (void)create_IOS_GL:(void*)_ctx Width:(int)_w Height:(int)_h Version:(int)_version {
#ifdef SV_IOS
    if( m_sve_obj ) {
        sv::SVCtxBasePtr t_ctx = m_sve_obj->createEnv(sv::E_R_GLES_IOS);
        sv::SVCtxIOSGLESPtr t_ctx_gles_ios = std::dynamic_pointer_cast<sv::SVCtxIOSGLES>(t_ctx);
        if(t_ctx_gles_ios) {
            //t_ctx_gles_ios->init(m_sve_obj,_ctx,_w,_h);
        }
    }
#endif
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
