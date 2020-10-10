//
//  CGInst.m
//  SVESample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "CGInst.h"
#include "src/app/SVInst.h"
#include "src/env/SVCtxIOS.h"
#include "src/rendercore/SVMetal/SVRendererMetal.h"

static CGInst *mInst;

@interface CGInst() {
    sv::SVInstPtr m_p_sve;
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
    //创建SVE引擎
    m_p_sve = sv::SVInst::makeCreate();
    m_p_sve->init();
    //创建UI系统
    //[[CGUI getInst] cgInit:0];
}

-(void)cgDestroy {
    //开始SVE
    //[[CGUI getInst] cgDestroy];
    if(m_p_sve) {
        m_p_sve->destroy();
        m_p_sve = nullptr;
    }
}

-(void*)getSVE {
    return m_p_sve.get();
}

//
-(void)createRM:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
    if( m_p_sve ) {
        //创建Metal
        if(false) {
            sv::SVCtxBasePtr t_ctx = m_p_sve->createEnv(sv::E_R_METAL_IOS);
            sv::SVCtxIOSMetalPtr t_ctx_metal = std::dynamic_pointer_cast<sv::SVCtxIOSMetal>(t_ctx);
            if(t_ctx_metal) {
                //
                
            }
        } else {
            //创建OpenGLES
            sv::SVCtxBasePtr t_ctx = m_p_sve->createEnv(sv::E_R_GLES_IOS);
            sv::SVCtxIOSGLESPtr t_ctx_gles = std::dynamic_pointer_cast<sv::SVCtxIOSGLES>(t_ctx);
            if(t_ctx_gles) {
                //
            }
        }
    }
}

//
-(void)destroyRM {
    
}

-(void)render {
    if(m_p_sve) {
        m_p_sve->renderSVE();
    }
}
@end
