//
//  CMetalView.m
//  SVETools
//
//  Created by 付一洲 on 2020/5/29.
//  Copyright © 2020 付一洲. All rights reserved.
//

#import "CMetalView.h"
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/CVDisplayLink.h>

@interface CMetalView () {
    CAMetalLayer* metalLayer;
    CVDisplayLinkRef displayLink;
}

@property (nonatomic, strong) id<MTLDevice>  mDevice;
@property (nonatomic, strong) id<MTLCommandQueue>   mCommandQueue;

@end

@implementation CMetalView

- (instancetype)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    if( self ) {
        //
        self.mDevice = MTLCreateSystemDefaultDevice();
        self.mCommandQueue = [self.mDevice newCommandQueue];
        //创建metal环境
        metalLayer = [CAMetalLayer layer];
        metalLayer.device = self.mDevice;
        metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        metalLayer.frame = frameRect;
        [self buildMetal];
    }
    return self;
    
}

-(void)buildMetal {
    [self setWantsLayer:true];
    [self setLayer:metalLayer];
    [self creatTimer];
}

-(void)creatTimer {
    CGDirectDisplayID   displayID = CGMainDisplayID();
    CVReturn            error = kCVReturnSuccess;
    error = CVDisplayLinkCreateWithCGDisplay(displayID, &displayLink);
    if (error){
        NSLog(@"DisplayLink created with error:%d", error);
        displayLink = nullptr;
    }
    CVDisplayLinkSetOutputCallback(displayLink, renderCallback, (__bridge void *)self);
    CVDisplayLinkStart(displayLink);
}

-(void)destroyTimer{
    CVDisplayLinkStop(displayLink);
    CVDisplayLinkRelease(displayLink);
}

- (void)dealloc{
    [self destroyTimer];
}

static CVReturn renderCallback(CVDisplayLinkRef displayLink,
                               const CVTimeStamp *inNow,
                               const CVTimeStamp *inOutputTime,
                               CVOptionFlags flagsIn,
                               CVOptionFlags *flagsOut,
                               void *displayLinkContext){
    //NSLog(@"sve timers \n ");
    dispatch_sync(dispatch_get_main_queue(), ^{
        //NSLog(@"sve timers \n ");
        [(__bridge CMetalView*)displayLinkContext renderMetal];
    });
    return kCVReturnSuccess;
}

-(void)renderMetal {
    NSLog(@"sve renderMetal!");
    id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
    id<MTLTexture> texture = drawable.texture;
    //
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
}

- (void)drawRect:(NSRect)dirtyRect {
    NSLog(@"sve drawRect!");
    //
    [super drawRect:dirtyRect];
    //[self render];
    // Drawing code here.
}

@end
