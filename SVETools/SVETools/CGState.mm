//
//  CGState.mm
//  SVEShowGift
//
//  Created by 付一洲 on 2018/6/26.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import "CGState.h"

static CGState *mInst;

@interface CGState() {
}
@end

@implementation CGState

+(instancetype) getInst{
    if(mInst == nil){
        mInst = [CGState new];
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

@end
