//
//  CGUI.m
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import "CGUI.h"
#import <QuartzCore/QuartzCore.h>
#import <QuartzCore/CAMetalLayer.h>
#import "CMetalView.h"


static CGUI *mInst;

@interface CGUI() {
    CMetalView* pview;
    CAMetalLayer* pMetalLayer;
}
@end

@implementation CGUI

+ (instancetype) getInst {
    if(mInst == nil){
        mInst = [CGUI new];
    }
    return mInst;
}

- (instancetype)init{
    self = [super init];
    if (self) {
    }
    return self;
}

-(void)dealloc {
}

-(void)cgInit:(int)_mode {
    //pview = [[CMetalView alloc] initWithFrame: ];
}

-(void)cgDestroy {

}

@end
