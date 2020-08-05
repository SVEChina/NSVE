//
//  CGInst.m
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import "CGInst.h"
#import "CGUI.h"
#include "src/app/SVInst.h"
#include "src/rendercore/SVMetal/SVRendererMetal.h"

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
    //开始SVE
    [[CGUI getInst] cgDestroy];
    [self destroySVE];
}

-(void)initSVE{
    SV_LOG_ERROR("sve init begin!");
    m_pSVE = sv::SVInst::makeCreate();
    NSString* t_sve_path = [[NSBundle mainBundle] pathForResource:@"sve-metal" ofType:@"bundle"];
    NSString* t_sve_path_ = [t_sve_path stringByAppendingString:@"/"];
    m_pSVE->addRespath([t_sve_path_ UTF8String]);
    m_pSVE->init();
    SV_LOG_ERROR("sve init end!");
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

//
-(void)createRM:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
    if( m_pSVE ) {
        sv::SVRendererPtr t_rm =m_pSVE->createRM(sv::E_M_METAL);
        sv::SVRendererMetalPtr t_rm_metal = std::dynamic_pointer_cast<sv::SVRendererMetal>(t_rm);
        if(t_rm_metal) {
            //渲染器初始化
            SV_LOG_ERROR("sve createRM begin! \n");
            t_rm_metal->init(_device,_drawable,_drawable.texture);
            SV_LOG_ERROR("sve createRM end! \n");
        }
    }
}

//
-(void)destroyRM {
    
}

-(void)render {
    SV_LOG_ERROR("sve render begin!");
    m_pSVE->updateSVE(0.33f);
    m_pSVE->renderSVE();
    SV_LOG_ERROR("sve render end!");
}


@end
