//
//  CGInst.m
//  SVESample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "CGInst.h"
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
//    [[CGUI getInst] cgInit:0];
}

-(void)cgDestroy {
    //开始SVE
//    [[CGUI getInst] cgDestroy];
    [self destroySVE];
}

-(void)initSVE{
    m_pSVE = sv::SVInst::makeCreate();
    m_pSVE->init();
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
        sv::SVRendererPtr t_rm =m_pSVE->createRM(E_M_METAL);
        sv::SVRendererMetalPtr t_rm_metal = std::dynamic_pointer_cast<sv::SVRendererMetal>(t_rm);
        t_rm_metal->initParam(_device,_drawable,_drawable.texture);
    }
}

//
-(void)destroyRM {
    
}

-(void)render {
    //
    m_pSVE->renderSVE();
}
@end
