//
//  AppDelegate.m
//  SVETools
//
//  Created by 付一洲 on 2020/5/26.
//  Copyright © 2020 付一洲. All rights reserved.
//

#import "AppDelegate.h"
#import "WinDelegate.h"
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
    self.window.delegate = [[WinDelegate alloc] init];
    
    //
    [[NSNotificationCenter defaultCenter] addObserver:self.window
                                             selector:@selector(windowDidResize:)
                                                 name:NSWindowDidResizeNotification
                                               object:self];
    //
    [[CGInst getInst] cgInit];
    // Insert code here to initialize your application
#ifdef SVE_TOOL_USE_METAL
    renderView = [[CMetalView alloc] initWithFrame:self.window.contentView.bounds];
#elif SVE_TOOL_USE_GLES
    renderView = [[CGLESView alloc] initWithFrame:self.window.contentView.bounds];
#endif
    [self.window.contentView addSubview:renderView];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
    int a = 0;
}


@end
