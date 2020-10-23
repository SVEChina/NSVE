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
    bool _test;
}

@property (nonatomic , strong) EAGLContext* mContext;

@end

@implementation CGLView

- (instancetype)initWithFrame:(CGRect)frameRect {
    self = [super initWithFrame:frameRect];
    if( self ) {
        
    }
    return self;
    
}

- (void)buildGL {
    //初始化渲染上下文，管理所有绘制的状态，命令及资源信息。
    //kEAGLRenderingAPIOpenGLES3
    _eaglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    //创建渲染器
    [[CGInst getInst] createGLES:_eaglContext version:2 drawable:_eaglLayer];
    //
    [self creatTimer];
}


-(void)creatTimer {
    // Call render 60 times a second.
    displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(renderGL)];
    displayLink.preferredFramesPerSecond = 60;
    [displayLink addToRunLoop:NSRunLoop.currentRunLoop forMode:NSDefaultRunLoopMode];
}

-(void)renderGL {
    [[CGInst getInst] render];
    //
    if(_test) {
        _test = false;
        [[CGInst getInst] test];
    }
}

- (void)createGLLayerWithWidth:(int)width Height:(int)height{
    if (!_eaglLayer) {
        _test = true;
        //创建gl环境
        _eaglLayer = [CAEAGLLayer layer];
        _eaglLayer.frame = CGRectMake(0, 0, width, height);
        _eaglLayer.opaque = YES; //CALayer默认是透明的
        _eaglLayer.drawableProperties = @{
            kEAGLDrawablePropertyRetainedBacking :[NSNumber numberWithBool:YES],
            kEAGLDrawablePropertyColorFormat : kEAGLColorFormatRGBA8 };
        //
        [self.layer addSublayer:_eaglLayer];
        [self buildGL];
        //adapt layer
        _eaglLayer.anchorPoint = CGPointMake(0.5, 0.5);
        float t_layer_scale_x = self.bounds.size.width/width;
        float t_layer_scale_y = self.bounds.size.height/height;
        float t_scale = t_layer_scale_x > t_layer_scale_y ? t_layer_scale_x : t_layer_scale_y;
        CATransform3D translate = CATransform3DMakeTranslation((self.bounds.size.width - width)*0.5, (self.bounds.size.height - height)*0.5, 0);
        CATransform3D transform = CATransform3DScale(translate, t_scale, t_scale ,1.0);
        _eaglLayer.transform = transform;
        
        _eaglLayer.backgroundColor = [UIColor whiteColor].CGColor;
    }
}

@end
