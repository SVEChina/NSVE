//
//  CMetalView.m
//  IMISample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "CMetalView.h"
#import <QuartzCore/CAMetalLayer.h>
#import "CGInst.h"
#include "src/app/IMIInst.h"

@interface CMetalView () {
    CAMetalLayer* metalLayer;
    CADisplayLink* displayLink;
}
@property (nonatomic, strong) id<MTLDevice>  mDevice;
@property (nonatomic, strong) id<MTLCommandQueue>   mCommandQueue;
@end

@implementation CMetalView
- (instancetype)initWithFrame:(CGRect)frameRect {
    self = [super initWithFrame:frameRect];
    if( self ) {
        
    }
    return self;
    
}

-(void)buildMetal {
    //NSLog(@"sve renderMetal!");
    id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
    id<MTLTexture> texture = drawable.texture;
    //创建渲染器
    [[CGInst getInst] createRM:self.mDevice drawable:drawable];
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
    if(false) {
        //NSLog(@"sve renderMetal!");
        id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
        id<MTLTexture> texture = drawable.texture;
        //相当于rt
        MTLRenderPassDescriptor  *passDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
        passDescriptor.colorAttachments[0].texture = texture;
        passDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        passDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
        passDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
        //
        id<MTLCommandBuffer> commandBuffer = [self.mCommandQueue commandBuffer];
        id<MTLRenderCommandEncoder> commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:passDescriptor];
        //
        [commandEncoder endEncoding];
        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
    }else{
        [[CGInst getInst] render];
    }
    
}

- (void)createMetalLayerWithWidth:(int)width Height:(int)height{
    if (!metalLayer) {
        self.mDevice = MTLCreateSystemDefaultDevice();
        self.mCommandQueue = [self.mDevice newCommandQueue];
        //创建metal环境
        metalLayer = [CAMetalLayer layer];
        metalLayer.device = self.mDevice;
        metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        metalLayer.frame = CGRectMake(0, 0, width, height);
        [self.layer insertSublayer:metalLayer atIndex:0];
        [self buildMetal];
        //adapt layer
        metalLayer.anchorPoint = CGPointMake(0.5, 0.5);
        float t_layer_scale_x = self.bounds.size.width/width;
        float t_layer_scale_y = self.bounds.size.height/height;
        float t_scale = t_layer_scale_x > t_layer_scale_y ? t_layer_scale_x : t_layer_scale_y;
        CATransform3D translate = CATransform3DMakeTranslation((self.bounds.size.width - width)*0.5, (self.bounds.size.height - height)*0.5, 0);
        CATransform3D transform = CATransform3DScale(translate, t_scale, t_scale ,1.0);
        metalLayer.transform = transform;
        metalLayer.backgroundColor = [UIColor whiteColor].CGColor;
    }
}

- (void)drawRect:(CGRect)rect {
    //NSLog(@"sve drawRect!");
    //
    [super drawRect:rect];
    //[self render];
    // Drawing code here.
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
