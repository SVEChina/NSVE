//
//  CGDetectMgr.h
//  SYEngine-Demo
//
//  Created by 李晓帆 on 29/9/2020.
//  Copyright © 2020 徐子昱. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CGDef.h"
NS_ASSUME_NONNULL_BEGIN

@interface CGDetectMgr : NSObject
+ (instancetype)getInst;
- (void)initMgr;
- (unsigned char *)detectWithFormate:(enum CG_PIC_FORMATE)_formate buffer:(unsigned char *)_buffer width:(int)_width height:(int)_height;
@end

NS_ASSUME_NONNULL_END
