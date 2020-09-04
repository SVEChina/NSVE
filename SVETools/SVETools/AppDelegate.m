//
//  AppDelegate.m
//  SVETools
//
//  Created by 付一洲 on 2020/5/26.
//  Copyright © 2020 付一洲. All rights reserved.
//

#import "AppDelegate.h"
#import "CMetalView.h"
#import "CGLESView.h"
#import "CGInst.h"
#import "CGDef.h"

@interface AppDelegate () {
    NSView* renderView;
}

@property (weak) IBOutlet NSWindow *window;

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    //
    [self.window setTitle: @"光子工作室—"];
    [self.window setAcceptsMouseMovedEvents: YES];
    [self.window setReleasedWhenClosed: NO];
    [self.window makeKeyAndOrderFront:self]; // shows and focuses the window
    [self.window center];
    //
    //监听窗口变化
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification object:nil];
    //
    [[CGInst getInst] cgInit];
    // Insert code here to initialize your application
    if(SVE_CORE == SVE_METAL) {
        renderView = [[CMetalView alloc] initWithFrame:self.window.contentView.bounds];
    }else if(SVE_CORE == SVE_GL) {
        renderView = [[CGLESView alloc] initWithFrame:self.window.contentView.bounds];
    }else if(SVE_CORE == SVE_GLES) {
        //renderView = [[CGLESView alloc] initWithFrame:self.window.contentView.bounds];
    }
    [self.window.contentView addSubview:renderView];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    
}

-(void)windowDidResize:(NSNotification *)notification{
    NSWindow *window = notification.object;
    NSLog(@"window resize:%f %f",window.frame.size.width, window.frame.size.height);
    NSSize t_size = window.frame.size;
    [renderView setFrameSize:t_size];
    //
    [[CGInst getInst] resizeWidth:t_size.width Height:t_size.height];
}


@end
