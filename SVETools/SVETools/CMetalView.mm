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
#import "CGInst.h"
#include "src/app/SVInst.h"

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

- (void)resizeSubviewsWithOldSize:(NSSize)oldSize {
    [super resizeSubviewsWithOldSize:oldSize];
}

-(void)buildMetal {
    //创建渲染器,Metal渲染器。
    id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
    if(drawable) {
        [[CGInst getInst] createMetal:self.mDevice drawable:drawable];
    }
    [self setWantsLayer:true];
    [self setLayer:metalLayer];
    [self creatTimer];
}

-(void)creatTimer {
    NSLog(@"creatTimer begin!\n");
    CGDirectDisplayID displayID = CGMainDisplayID();
    CVReturn error = CVDisplayLinkCreateWithCGDisplay(displayID, &displayLink);
    if (error){
        NSLog(@"DisplayLink created with error:%d", error);
        displayLink = nullptr;
        return ;
    }
    CVDisplayLinkSetOutputCallback(displayLink, renderCallback, (__bridge void *)self);
    CVDisplayLinkStart(displayLink);
    NSLog(@"creatTimer end!\n");
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
    NSLog(@"sve timers renderCallback begin\n ");
    //改成异步推给主线程的任务，同步会造成死锁
    dispatch_async( dispatch_get_main_queue(), ^{
        NSLog(@"sve timers - run \n ");
        [(__bridge CMetalView*)displayLinkContext renderMetal];
    });
    NSLog(@"sve timers renderCallback end\n ");
    return kCVReturnSuccess;
}

-(void)renderMetal {
    [[CGInst getInst] render];
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    //NSLog(@"sve drawRect!");
}

@end
