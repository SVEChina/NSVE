//
//  CGBaseSys.h
//  IMISample
//
//  Created by 李晓帆 on 22/10/2020.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CGCamera.h"
NS_ASSUME_NONNULL_BEGIN
@interface CGBaseSys : NSObject
+ (instancetype)getInst;
- (void)initSys;
- (CGCamera *)getCamera;
@end

NS_ASSUME_NONNULL_END
