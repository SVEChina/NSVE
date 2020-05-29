//
//  AppDelegate.m
//  SVETools
//
//  Created by 付一洲 on 2020/5/26.
//  Copyright © 2020 付一洲. All rights reserved.
//

#import "AppDelegate.h"
#import "CMetalView.h"
#import "CGInst.h"
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/MTLDevice.h>

@interface AppDelegate () {
    CMetalView* metalview;
    //CAMetalLayer* metallayer;
}

@property (weak) IBOutlet NSWindow *window;

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    metalview = [[CMetalView alloc] initWithFrame:self.window.contentView.bounds];
    [self.window.contentView addSubview:metalview];
    //
    [[NSNotificationCenter defaultCenter] addObserver:self.window
                                             selector:@selector(windowDidResize:)
                                                 name:NSWindowDidResizeNotification
                                               object:self];
    //
    [[CGInst getInst] cgInit];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (void)windowDidResize:(NSNotification*)aNotification {
    NSLog(@"window resize!");
}


@end
