//
//  WinDelegate.mm
//  SVEShowGift
//
//  Created by 李晓帆 on 2018/6/21.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import "WinDelegate.h"
#import <QuartzCore/CVDisplayLink.h>
//#include "MainGLView.h"
#import "CGInst.h"

//
@interface WinDelegate (){
}
@end

@implementation WinDelegate

-(instancetype)init {
    self = [super init];
    if(self) {
        
    }
    return self;
}

-(void)dealloc{
}

- (void)windowDidResize:(NSNotification *)notification {
    int a = 0;
}

- (void)windowDidExpose:(NSNotification *)notification {
    int a = 0;
}

- (void)windowWillMove:(NSNotification *)notification {
    //int a = 0;
}

- (void)windowDidMove:(NSNotification *)notification {
    //int a = 0;
}

//- (void)windowDidBecomeKey:(NSNotification *)notification {
//    int a = 0;
//}

- (void)windowDidResignKey:(NSNotification *)notification {
    //int a = 0;
}

- (void)windowDidBecomeMain:(NSNotification *)notification {
    //int a = 0;
}

- (void)windowDidResignMain:(NSNotification *)notification {
    //int a = 0;
}

- (void)windowWillClose:(NSNotification *)notification {
    //int a = 0;
}

- (void)windowWillMiniaturize:(NSNotification *)notification {
    
}

@end
