//
//  CMetalView.h
//  SVETools
//
//  Created by 付一洲 on 2020/5/29.
//  Copyright © 2020 付一洲. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface CMetalView : NSView

-(void)resize:(NSRect)rc;

@end

NS_ASSUME_NONNULL_END
