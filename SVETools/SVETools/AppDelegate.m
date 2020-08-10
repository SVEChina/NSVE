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
    [[NSNotificationCenter defaultCenter] addObserver:self.window
                                             selector:@selector(windowDidResize:)
                                                 name:NSWindowDidResizeNotification
                                               object:self];
    //
    [[NSNotificationCenter defaultCenter] addObserver:self.window
                                             selector:@selector(windowDidClose:)
                                                 name:NSWindowWillCloseNotification
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

- (void)windowDidResize:(NSNotification*)aNotification {
    NSLog(@"window resize!");
    //[[CGInst getInst] resize];
}

- (void)windowDidClose:(NSNotification*)aNotification {
    NSLog(@"window close!");
}




@end
