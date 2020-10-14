//
//  CGLView.m
//  SVESample
//
//  Created by 付一洲 on 2020/10/14.
//  Copyright © 2020 李晓帆. All rights reserved.
//
//  CGLView.mm
//

#import "CGLView.h"
#import <QuartzCore/CAMetalLayer.h>
#import "CGInst.h"
#include "src/app/SVInst.h"

@interface CGLView () {
    EAGLContext *_eaglContext; // OpenGL context,管理使用opengl es进行绘制的状态,命令及资源
    CAEAGLLayer *_eaglLayer;
    CADisplayLink* displayLink;
    int _width;
    int _height;
}

@property (nonatomic , strong) EAGLContext* mContext;

@end

@implementation CGLView

- (instancetype)initWithFrame:(CGRect)frameRect {
    self = [super initWithFrame:frameRect];
    if( self ) {
        //创建gl环境
        _eaglLayer = [CAEAGLLayer layer];
        _eaglLayer.frame = frameRect;
        _eaglLayer.opaque = YES; //CALayer默认是透明的
        _width = frameRect.size.width;
        _height = frameRect.size.height;
        //
        _eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool: NO],
                                         kEAGLDrawablePropertyRetainedBacking,
                                         kEAGLColorFormatRGBA8,
                                         kEAGLDrawablePropertyColorFormat,
                                         nil];
        //[self.layer addSublayer:_eaglLayer];
        [self.layer insertSublayer:_eaglLayer atIndex:0];
        //
        [self buildGL];
    }
    return self;
    
}

- (void)buildGL {
    //初始化渲染上下文，管理所有绘制的状态，命令及资源信息。
    _eaglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    //创建渲染器
    [[CGInst getInst] createGLES:_eaglContext version:3 width:_width height:_height];
    //
    [self creatTimer];
}


-(void)creatTimer {
    // Call render 60 times a second.
    displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(renderMetal)];
    displayLink.preferredFramesPerSecond = 60;
    [displayLink addToRunLoop:NSRunLoop.currentRunLoop forMode:NSDefaultRunLoopMode];
}

-(void)renderMetal {
    [[CGInst getInst] render];
}

@end
