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
    m_pSVE = sv::SVInst::makeCreate();
    NSString* t_sve_path = @"";
#if SVE_TOOL_USE_METAL
    t_sve_path = [[NSBundle mainBundle] pathForResource:@"sve-metal" ofType:@"bundle"];
#elif SVE_TOOL_USE_GLES
    t_sve_path = [[NSBundle mainBundle] pathForResource:@"sve-gles" ofType:@"bundle"];
#endif
    NSString* t_sve_path_ = [t_sve_path stringByAppendingString:@"/"];
    m_pSVE->addRespath([t_sve_path_ UTF8String]);
    //
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
    //return nullptr;
}
/*
  Renderer Metal
 */
-(void)createRM:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable {
    if( m_pSVE ) {
        sv::SVRendererPtr t_re =m_pSVE->createRenderer(sv::E_R_METAL);
        sv::SVRendererMetalPtr t_re_metal = std::dynamic_pointer_cast<sv::SVRendererMetal>(t_re);
        if(t_re_metal) {
            //渲染器初始化
            t_re_metal->init(_device,_drawable,_drawable.texture);
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
    //
    m_pSVE->updateSVE(0.33f);
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
