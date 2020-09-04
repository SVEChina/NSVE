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
//Metal-OSX
-(void)create_OSX_Metal:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable;
//Metal-OSX
-(void)create_IOS_Metal:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable;
//
-(void)destroyMetal;
//GL-OSX
- (void)create_OSX_GL:(void*)ctx Width:(int)_w Height:(int)_h Version:(int)_version;
//GL-IOS
- (void)create_IOS_GL:(void*)ctx Width:(int)_w Height:(int)_h Version:(int)_version;
//
- (void)destroyGL;
//
-(void)render;

@end
