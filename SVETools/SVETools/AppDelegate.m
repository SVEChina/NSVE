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
@interface AppDelegate () {
    
}

@property (weak) IBOutlet NSWindow *window;

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    //
    [[CGInst getInst] cgInit];
    // Insert code here to initialize your application
    NSView *renderV = [[CMetalView alloc] initWithFrame:self.window.contentView.bounds];
    #if SVE_TOOL_USE_METAL
        renderV = [[CMetalView alloc] initWithFrame:self.window.contentView.bounds];
    #elif SVE_TOOL_USE_GLES
        renderV = [[CGLESView alloc] initWithFrame:self.window.contentView.bounds];
    #endif
    [self.window.contentView addSubview:renderV];
    //
    [[NSNotificationCenter defaultCenter] addObserver:self.window
                                             selector:@selector(windowDidResize:)
                                                 name:NSWindowDidResizeNotification
                                               object:self];

}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (void)windowDidResize:(NSNotification*)aNotification {
    NSLog(@"window resize!");
}


@end
