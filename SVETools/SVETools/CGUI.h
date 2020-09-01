//
//  CGUI.h
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/NSMenu.h>
#import <AppKit/NSViewController.h>
#import <AppKit/NSWindow.h>
#import "CGState.h"

@interface CGUI : NSObject

+ (instancetype) getInst;

-(void)cgInit:(int)_mode;

-(void)cgDestroy;


@end
