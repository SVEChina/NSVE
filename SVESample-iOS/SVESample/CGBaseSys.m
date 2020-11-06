//
//  CGBaseSys.m
//  IMISample
//
//  Created by 李晓帆 on 22/10/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import "CGBaseSys.h"

static CGBaseSys *mInst;
@interface CGBaseSys (){
    CGCamera *mCamera;
}

@end

@implementation CGBaseSys
+(instancetype) getInst{
    if(mInst == nil){
        mInst = [CGBaseSys new];
    }
    return mInst;
}

- (void)initSys{
    [self createCamera];
}

- (void)createCamera{
    //初始化相机
    if (!mCamera) {
        mCamera = [[CGCamera alloc] init];
    //    mCamera.delegate = self;
        [mCamera startCapture];
        [mCamera setCameraExposure:CGPointMake(0.5, 0.5) isContinuousAuto:false];
    }
}

- (CGCamera *)getCamera{
    return mCamera;
}
@end
