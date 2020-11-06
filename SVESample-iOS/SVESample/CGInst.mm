//
//  CGInst.m
//  IMISample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "CGInst.h"
#import "CGDef.h"
#import "CGBaseSys.h"
#import "CGDetectMgr.h"
#include "src/app/IMIInst.h"
#include "src/env/IMICtxIOS.h"

//#define IMI_CORE IMI_GLES//IMI_METAL

static CGInst *mInst;

@interface CGInst() {
    imi::IMIInstPtr m_p_sve;
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
        m_p_sve = nullptr;
    }
    return self;
}

-(void)dealloc {
}

-(void)cgInit{
    //创建IMI引擎
    m_p_sve = imi::IMIInst::makeCreate();
    //设置资源文件
    NSString *t_sve_res = @"imi-metal";
    if(IMI_CORE == IMI_GLES ) {
        t_sve_res = @"imi-gles";
    }
//    else if( IMI_CORE == IMI_METAL ) {
//        t_sve_res = @"imi-metal";
//    }
    NSString* t_sve_path = [[NSBundle mainBundle] pathForResource:t_sve_res ofType:@"bundle"];
    t_sve_path = [t_sve_path stringByAppendingString:@"/"];
    m_p_sve->addRespath([t_sve_path UTF8String]);
    m_p_sve->init();
    IMI_LOG_INFO("sve init end!");
    //创建UI系统
    //[[CGUI getInst] cgInit:0];
}

-(void)cgDestroy {
    //开始IMI
    //[[CGUI getInst] cgDestroy];
    if(m_p_sve) {
        m_p_sve->destroy();
        m_p_sve = nullptr;
    }
}

-(void*)getIMI {
    return m_p_sve.get();
}

-(void)createRM:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
    if( m_p_sve ) {
//        //创建Metal
//        imi::IMICtxBasePtr t_ctx = m_p_sve->createEnv(imi::E_R_METAL_IOS);
//        imi::IMICtxIOSMetalPtr t_ctx_metal = std::dynamic_pointer_cast<imi::IMICtxIOSMetal>(t_ctx);
//        if(t_ctx_metal) {
//        }
    }
}

//
-(void)destroyRM {
    if(m_p_sve) {
        m_p_sve->destroyEnv();
    }
}

//
-(void)createGLES:(EAGLContext*)_ctx version:(int)_ver drawable:(CAEAGLLayer *)_layer {
    if( m_p_sve ) {
        imi::IMICtxBasePtr t_ctx = m_p_sve->createEnv(imi::E_R_GLES_IOS);
        imi::IMICtxIOSGLESPtr t_ctx_gles = std::dynamic_pointer_cast<imi::IMICtxIOSGLES>(t_ctx);
        if(t_ctx_gles) {
            t_ctx_gles->init( (__bridge void*)_ctx, _ver, (__bridge void*)_layer);
        }
    }
}

-(void)destroyGLES {
    if(m_p_sve) {
        m_p_sve->destroyEnv();
    }
}

-(void)render {
    if(m_p_sve) {
        //
        CGCamera *camera = [[CGBaseSys getInst] getCamera];
        //送入人脸识别
        unsigned char *keyData = [[CGDetectMgr getInst] detectWithFormate:CG_PF_BGRA buffer:(unsigned char*)[camera getFrameData] width:[camera getFrameWidth] height:[camera getFrameHeight]];
        m_p_sve->inputKeyData(keyData);
        //送入引擎当作背景渲染
        m_p_sve->inputFrame((unsigned char*)[camera getFrameData], [camera getFrameWidth], [camera getFrameHeight]);
        //
        m_p_sve->updateIMI(0.033f);
        m_p_sve->renderIMI();
    }
}

-(void)test {
    if(m_p_sve) {
        m_p_sve->test();
    }
}

@end
