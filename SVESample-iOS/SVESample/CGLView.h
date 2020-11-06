//
//  CGLView.h
//  IMISample
//
//  Created by 付一洲 on 2020/10/14.
//  Copyright © 2020 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface CGLView : UIView
- (void)createGLLayerWithWidth:(int)width Height:(int)height;
@end

NS_ASSUME_NONNULL_END
