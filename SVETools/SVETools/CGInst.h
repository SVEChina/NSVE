//
//  CGInst.h
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/NSMenu.h>
#import "CGState.h"

@class CGLogic;
@class CGUI;

@interface CGInst : NSObject

+ (instancetype) getInst;

-(void)cgInit;

-(void)cgDestroy;

-(void*) getSVE {
    return m_pSVE;
}

@end
