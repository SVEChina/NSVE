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
    m_pSVE = sv::SVInst::makeCreate();
    //
    NSString* t_sve_path = [[NSBundle mainBundle] pathForResource:@"sve-metal" ofType:@"bundle"];
    NSString* t_sve_path_ = [t_sve_path stringByAppendingString:@"/"];
    m_pSVE->addRespath([t_sve_path_ UTF8String]);
    //
    m_pSVE->init();
   
//    m_pSVE->startSVE();
}

-(void)destroySVE{
    if(m_pSVE) {
        m_pSVE->destroy();
        m_pSVE = nullptr;
    }
}

-(void*)getSVE {
    return m_pSVE.get();
    //return nullptr;
}

//
-(void)createRM:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
    if( m_pSVE ) {
        sv::SVRendererPtr t_rm =m_pSVE->createRM(sv::E_M_METAL);
        sv::SVRendererMetalPtr t_rm_metal = std::dynamic_pointer_cast<sv::SVRendererMetal>(t_rm);
        if(t_rm_metal) {
            //渲染器初始化
            t_rm_metal->init(_device,_drawable,_drawable.texture);
        }
    }
}

//
-(void)destroyRM {
    
}

-(void)render {
    //
    m_pSVE->renderSVE();
}

////数据重置
//-(void)reset {
//    [self.m_pDataMgr reset];
//    [self.m_pLogic reset];
//}
//
////改变编辑器模式
//-(void)setEditMode:(EDITMODE)_mode {
//    if(m_editMode!=_mode) {
//        //赋值
//        m_editMode = _mode;
//        //逻辑变化
//        [self.m_pLogic setEditMode:_mode];
//        //ui变化
//        [[CGUI getInst] setEditMode:_mode];
//    }
//}
//
//-(EDITMODE)getEditMode {
//    return m_editMode;
//}

@end
