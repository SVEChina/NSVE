//
//  CGCamera.h
//
//  Created by 李晓帆 on 2018/9/3.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <AVFoundation/AVFoundation.h>
@protocol CameraDelegate<NSObject>
@optional
- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection;
@end
@interface CGCamera : NSObject
@property(weak,nonatomic)id<CameraDelegate> delegate;
@property(nonatomic, strong) AVCaptureVideoDataOutput *videoOutput;
@property(nonatomic, strong) AVCaptureAudioDataOutput *audioOutput;
@property(nonatomic, strong) AVCaptureConnection *audioConnection;
@property(nonatomic, strong) AVCaptureConnection *videoConnection;

- (void)switchCamera;
- (void)startCapture;
- (void)stopCapture;
- (void)setFrameRate:(int)rate;
- (int)getFrameWidth;
- (int)getFrameHeight;
//
- (void)openHDR;
- (void)setWhiteTemperature:(CGFloat)current;
- (CGFloat)getTemperature;
- (void)setCameraFocusing:(CGPoint)point;
- (void)setExposureTargetBias:(CGFloat)bias;
- (void)setAutoContinuousWhiteMode:(BOOL)flag;
- (void)setCameraExposure:(CGPoint)point isContinuousAuto:(bool)flag;
@end
