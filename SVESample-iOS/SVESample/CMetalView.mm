//
//  CMetalView.m
//  SVESample
//
//  Created by 李晓帆 on 9/6/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "CMetalView.h"
#import <QuartzCore/CAMetalLayer.h>
#import "CGInst.h"
#include "src/app/SVInst.h"
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
        self.mDevice = MTLCreateSystemDefaultDevice();
        self.mCommandQueue = [self.mDevice newCommandQueue];
        //创建metal环境
        metalLayer = [CAMetalLayer layer];
        metalLayer.device = self.mDevice;
        metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        metalLayer.frame = frameRect;
        [self.layer insertSublayer:metalLayer atIndex:0];
        [self buildMetal];
    }
    return self;
    
}

-(void)buildMetal {
    //NSLog(@"sve renderMetal!");
    id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
    id<MTLTexture> texture = drawable.texture;
    //创建渲染器
    [[CGInst getInst] createRM:self.mDevice drawable:drawable];
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
