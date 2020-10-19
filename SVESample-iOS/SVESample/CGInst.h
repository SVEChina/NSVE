//
//  CGInst.h
//  SVESample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import <GLKit/GLKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface CGInst : NSObject
+ (instancetype) getInst;
//
-(void)cgInit;
//
-(void)cgDestroy;
//
-(void*)getSVE;
//
-(void)createRM:(id<MTLDevice>)_device drawable:(id<CAMetalDrawable>)_drawable;
//
-(void)destroyRM;
//
-(void)createGLES:(EAGLContext*)_ctx version:(int)_ver drawable:(CAEAGLLayer *)_layer;
//
-(void)destroyGLES;
//
-(void)render;
//
-(void)test;

@end

NS_ASSUME_NONNULL_END
