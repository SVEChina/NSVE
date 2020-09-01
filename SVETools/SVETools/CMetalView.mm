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

- (void)setFrameSize:(NSSize)newSize {
    [super setFrameSize:newSize];
    //
    if(metalLayer) {
//        id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
//        if(drawable.texture) {
//            NSLog(@"main tex %d resize:%d %d",drawable.texture,drawable.texture.width, drawable.texture.height);
//        }
    }
}

-(void)buildMetal {
    //创建渲染器,Metal渲染器。
    id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
    if(drawable) {
        [[CGInst getInst] create_OSX_Metal:self.mDevice drawable:drawable];
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

- (void)mouseDown:(NSEvent *)theEvent {
    NSLog(@"mouseDown:%f %f",theEvent.locationInWindow.x, theEvent.locationInWindow.y);
}

- (void)mouseDragged:(NSEvent *)theEvent {
    NSLog(@"mouseDragged:%f %f",theEvent.locationInWindow.x, theEvent.locationInWindow.y);
}

- (void)mouseUp:(NSEvent *)theEvent {
}

- (void)mouseMoved:(NSEvent *)theEvent {
    NSLog(@"mouseMoved:%f %f",theEvent.locationInWindow.x, theEvent.locationInWindow.y);
}

- (void)scrollWheel:(NSEvent *)theEvent {
    //theEvent.deltaY 后滑动是正，前滑是负
    //鼠标的滚动可以通过 deltaX 和 deltaY 两个属性来获取分别在水平方向和垂直方向的滚动偏移
    NSLog(@"scrollWheel delta:%f %f %f \n",theEvent.deltaX,theEvent.deltaY,theEvent.deltaZ);
}

- (void)rightMouseDown:(NSEvent *)theEvent {
}

- (void)otherMouseDown:(NSEvent *)theEvent {
    NSLog(@"otherMouseDown");
}

- (void)rightMouseUp:(NSEvent *)theEvent {
    NSLog(@"rightMouseUp");
   
}

- (void)otherMouseUp:(NSEvent *)theEvent {
    NSLog(@"otherMouseUp");
}

- (void)rightMouseDragged:(NSEvent *)theEvent {
    NSLog(@"rightMouseDragged");
    
}

- (void)otherMouseDragged:(NSEvent *)theEvent {
    NSLog(@"otherMouseDragged");
}

- (void)mouseEntered:(NSEvent *)theEvent {
    NSLog(@"mouse enter(%f,%f) \n",theEvent.locationInWindow.x,theEvent.locationInWindow.y);
}

- (void)mouseExited:(NSEvent *)theEvent {
    NSLog(@"mouse exit(%f,%f) \n",theEvent.locationInWindow.x,theEvent.locationInWindow.y);
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    //NSLog(@"sve drawRect!");
}

@end
