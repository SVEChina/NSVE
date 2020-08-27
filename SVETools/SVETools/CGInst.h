//
//  CGInst.h
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/NSMenu.h>
#import <QuartzCore/CAMetalLayer.h>
#import "CGState.h"

@class CGLogic;
@class CGUI;

@interface CGInst : NSObject

+ (instancetype) getInst;

-(void)cgInit;

-(void)cgDestroy;
//
-(void)resizeWidth:(int)_w Height:(int)_h;
//
-(void*)getSVE;
//
-(void)createMetal:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable;
//
-(void)destroyMetal;
//
- (void)createGLWidth:(int)_w Height:(int)_h;
//
- (void)destroyGL;
//
-(void)render;

@end
