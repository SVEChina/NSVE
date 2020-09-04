//
//  CGLESView.m
//  SVETools
//
//  Created by 付一洲 on 2020/5/29.
//  Copyright © 2020 付一洲. All rights reserved.
//

#import "CGLESView.h"
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/CVDisplayLink.h>
#import "CGInst.h"
#include "src/app/SVInst.h"

@interface CGLESView () {
    NSOpenGLPixelFormat *m_format;
    NSOpenGLContext* m_context;
    CVDisplayLinkRef displayLink;
}


@end

@implementation CGLESView

- (instancetype)initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    if( self ) {
        //外部构建的GL环境
        static const NSOpenGLPixelFormatAttribute attr[] = {
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            0
        };
        m_format = [[NSOpenGLPixelFormat alloc] initWithAttributes:(const NSOpenGLPixelFormatAttribute*)&attr];
        m_context = [[NSOpenGLContext alloc] initWithFormat:m_format shareContext:nil];
        [self setPixelFormat:m_format];
        [self setOpenGLContext:m_context];
        [m_context makeCurrentContext];
        //
        [self buildOpenGL];
    }
    return self;
}

- (void)buildOpenGL{
    int t_w = self.frame.size.width;
    int t_h = self.frame.size.height;
    //创建渲染器,OPENGL渲染器
    [[CGInst getInst] create_OSX_GL:(void*)m_context Width:t_w Height:t_h Version:150];
    [self creatTimer];
}

-(void)creatTimer {
    CGDirectDisplayID displayID = CGMainDisplayID();
    CVReturn error = kCVReturnSuccess;
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
    [self clearGLContext];
    [self destroyTimer];
}

static CVReturn renderCallback(CVDisplayLinkRef displayLink,
                               const CVTimeStamp *inNow,
                               const CVTimeStamp *inOutputTime,
                               CVOptionFlags flagsIn,
                               CVOptionFlags *flagsOut,
                               void *displayLinkContext){
    NSLog(@"renderCallback \n ");
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"sve timers \n ");
        [(__bridge CGLESView*)displayLinkContext renderGL];
    });
    return kCVReturnSuccess;
}

-(void)renderGL {
//    [m_context makeCurrentContext];
//    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    [m_context flushBuffer];
    [[CGInst getInst] render];
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
}


@end
