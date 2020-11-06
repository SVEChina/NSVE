//
//  CGCamera.m
//
//  Created by 李晓帆 on 2018/9/3.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#import "CGCamera.h"
#import <AssetsLibrary/AssetsLibrary.h>
#import <AVFoundation/AVFoundation.h>
#import <ImageIO/ImageIO.h>
@interface CGCamera()<AVCaptureVideoDataOutputSampleBufferDelegate, AVCaptureAudioDataOutputSampleBufferDelegate>{
    NSLock *m_lock;
    char *m_frame_cpy;
    bool    m_pauseCamera;
    AVCaptureDevice *m_backCameraDevice;
    AVCaptureDevice *m_frontCameraDevcie;
    AVCaptureDevice *m_curCameraDevcie;
    AVCaptureSession *m_captureSession;
    AVCaptureDeviceInput *m_curCameraInput;
    dispatch_queue_t m_sessionQueue;
    dispatch_queue_t m_videoQueue;
    dispatch_queue_t m_audioQueue;
    bool             m_isMirrored;
    int              m_width;
    int              m_height;
}
@end

@implementation CGCamera

- (instancetype)init{
    self = [super init];
    if (self) {
        m_pauseCamera = false;
        m_width = 720;
        m_height = 1280;
        m_frame_cpy = (char *)malloc(m_width*m_height*4);
        [self initializeCamera];
    }
    return self;
}

- (void)initializeCamera {
    m_lock = [[NSLock alloc]init];
    m_videoQueue = dispatch_queue_create("com.sve.capture.video", DISPATCH_QUEUE_SERIAL);
    
    NSError *error;
    m_captureSession = [[AVCaptureSession alloc] init];
    
#ifdef RECORD_AUDIO
    /* Audio */
    _audioDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeAudio];
    _audioIn = [[AVCaptureDeviceInput alloc] initWithDevice:_audioDevice error:nil];
    if ( [_captureSession canAddInput:_audioIn] ) {
        [_captureSession addInput:_audioIn];
    }
    self.audioOutput = [[AVCaptureAudioDataOutput alloc] init];
    // Put audio on its own queue to ensure that our video processing doesn't cause us to drop audio
    self.audioQueue = dispatch_queue_create( "com.sve.capture.audio", DISPATCH_QUEUE_SERIAL );
    [self.audioOutput setSampleBufferDelegate:self queue:self.audioQueue];
    
    if ( [_captureSession canAddOutput:self.audioOutput] ) {
        [_captureSession addOutput:self.audioOutput];
    }
    _audioConnection = [self.audioOutput connectionWithMediaType:AVMediaTypeAudio];
#endif // RECORD_AUDIO
    NSArray<AVCaptureDeviceType> *deviceType = @[AVCaptureDeviceTypeBuiltInWideAngleCamera, AVCaptureDeviceTypeBuiltInDualCamera];
    AVCaptureDeviceDiscoverySession *videoDeviceDiscoverySession = [AVCaptureDeviceDiscoverySession discoverySessionWithDeviceTypes:deviceType mediaType:AVMediaTypeVideo position:AVCaptureDevicePositionUnspecified];
    //获取 devices
    NSArray<AVCaptureDevice *> *devices = videoDeviceDiscoverySession.devices;
    
    for(AVCaptureDevice *device in devices) {
        if(device.position == AVCaptureDevicePositionBack) {
            m_backCameraDevice = device;
        } else if(device.position == AVCaptureDevicePositionFront) {
            m_frontCameraDevcie = device;
        }
    }
    m_curCameraDevcie = m_frontCameraDevcie;
    m_curCameraInput = [AVCaptureDeviceInput deviceInputWithDevice:m_curCameraDevcie error:&error];
    
    if([m_captureSession canAddInput:m_curCameraInput]) {
        [m_captureSession addInput:m_curCameraInput];
    }
    
    self.videoOutput = [[AVCaptureVideoDataOutput alloc] init];
    [self.videoOutput setAlwaysDiscardsLateVideoFrames:NO];
    [self.videoOutput setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA] forKey:(id)kCVPixelBufferPixelFormatTypeKey]]; //
    [self.videoOutput setSampleBufferDelegate:self queue:m_videoQueue];
    if([m_captureSession canAddOutput:self.videoOutput]) {
        [m_captureSession addOutput:self.videoOutput];
    }
    m_captureSession.sessionPreset = AVCaptureSessionPreset1280x720;//AVCaptureSessionPresetPhoto;//AVCaptureSessionPresetiFrame1280x720;//AVCaptureSessionPresetiFrame960x540; //
    _videoConnection = [self.videoOutput connectionWithMediaType:AVMediaTypeVideo];
    if ([_videoConnection isVideoOrientationSupported])
    {
        AVCaptureVideoOrientation orientation = AVCaptureVideoOrientationPortrait;
        [_videoConnection setVideoOrientation:orientation];
        [_videoConnection setVideoMirrored:YES];
    }
    [self setFrameRate:30];
    [m_captureSession commitConfiguration];
}

- (void)dealloc{
    m_backCameraDevice = nil;
    m_frontCameraDevcie = nil;
    m_curCameraDevcie = nil;
    m_captureSession = nil;
    m_curCameraInput = nil;
    m_sessionQueue = nil;
    m_videoQueue = nil;
    m_audioQueue = nil;
}

- (int)getFrameWidth{
    return  m_width;
}

- (int)getFrameHeight{
    return  m_height;
}

- (char *)getFrameData{
    return m_frame_cpy;
}

-(AVCaptureWhiteBalanceGains)clampGains:(AVCaptureWhiteBalanceGains)gains toMinVal:(CGFloat)minVal andMaxVal:(CGFloat)maxVal {
    AVCaptureWhiteBalanceGains tmpGains = gains;
    tmpGains.blueGain = MAX(MIN(tmpGains.blueGain, maxVal), minVal);
    tmpGains.redGain = MAX(MIN(tmpGains.redGain, maxVal), minVal);
    tmpGains.greenGain = MAX(MIN(tmpGains.greenGain, maxVal), minVal);
    return tmpGains;
}

//设置相机采集帧率
-(void) setFrameRate:(int)rate{
    if ([m_curCameraDevcie respondsToSelector:@selector(activeVideoMinFrameDuration)]) {
        [m_curCameraDevcie lockForConfiguration:nil];
        m_curCameraDevcie.activeVideoMinFrameDuration = CMTimeMake(1, rate);
        m_curCameraDevcie.activeVideoMaxFrameDuration = CMTimeMake(1, rate);
        [m_curCameraDevcie unlockForConfiguration];
    }
}


- (void)startCapture {
    dispatch_queue_t sessionQueue = dispatch_queue_create("com.example.camera.capture_session", DISPATCH_QUEUE_SERIAL);
    m_sessionQueue = sessionQueue;
    dispatch_async(sessionQueue, ^(void) {
        [self->m_captureSession startRunning];
    });
}

- (void)stopCapture {
    dispatch_async(m_sessionQueue, ^(void) {
        [self->m_captureSession stopRunning];
    });
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection{
    if (!m_pauseCamera) {
        CVPixelBufferRef pixelBuf = CMSampleBufferGetImageBuffer(sampleBuffer);
        if(CVPixelBufferLockBaseAddress(pixelBuf, 0) == kCVReturnSuccess){
            size_t width = CVPixelBufferGetWidth(pixelBuf);
            size_t height = CVPixelBufferGetHeight(pixelBuf);
            size_t bytesPerRow = CVPixelBufferGetBytesPerRowOfPlane(pixelBuf, 0);
            OSType pixelFormat = CVPixelBufferGetPixelFormatType(pixelBuf);
            if (pixelFormat == kCVPixelFormatType_32BGRA) {
                GLubyte* bufferPtr = (GLubyte *)CVPixelBufferGetBaseAddress(pixelBuf);
                memcpy(m_frame_cpy, bufferPtr, m_width*m_height*4);
                
            }else {
                //YUV 数据要这么取！！！！！！！！！！！！！！！！！！！
//                GLubyte* bufferPtr0 = (GLubyte  *)CVPixelBufferGetBaseAddressOfPlane(_pixelBuf, 0);
//                IMIStreamInPtr t_streamIn = t_app->getBasicSys()->getStreamIn();
//                if(t_streamIn){
//                    t_streamIn->pushStreamData([SCENENAME UTF8String], bufferPtr0, (s32)width, (s32)height, pixelFormat, 0);
//                }
            }
            CVPixelBufferUnlockBaseAddress(pixelBuf, 0);
        }
    }
}

- (void)switchCamera{
    dispatch_async(m_sessionQueue, ^(void) {
        [self->m_captureSession beginConfiguration ];
        self->m_pauseCamera = true;
        if(self->m_curCameraDevcie == self->m_frontCameraDevcie) {
            NSError *error;
            AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:self->m_backCameraDevice error:&error];
            [self->m_captureSession removeInput:self->m_curCameraInput];
            if([self->m_captureSession canAddInput:input]) {
                [self->m_captureSession addInput:input];
                self->m_curCameraInput = input;
                self->m_curCameraDevcie = self->m_backCameraDevice;
            }
            self->m_isMirrored = NO;
        } else {
            NSError *error;
            AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:self->m_frontCameraDevcie error:&error];
            [self->m_captureSession removeInput:self->m_curCameraInput];
            if([self->m_captureSession canAddInput:input]) {
                [self->m_captureSession addInput:input];
                self->m_curCameraInput = input;
                self->m_curCameraDevcie = self->m_frontCameraDevcie;
            }
            self->m_isMirrored = YES;
        }
        self->_videoConnection = [self.videoOutput connectionWithMediaType:AVMediaTypeVideo];
        if ([self->_videoConnection isVideoOrientationSupported]){
            AVCaptureVideoOrientation orientation = AVCaptureVideoOrientationPortrait;
            [self->_videoConnection setVideoOrientation:orientation];
            [self->_videoConnection setVideoMirrored:self->m_isMirrored];
        }
        // Changes take effect once the outermost commitConfiguration is invoked.
        [self->m_captureSession commitConfiguration];
        self->m_pauseCamera = false;
    });
}

- (void)setWhiteTemperature:(CGFloat)current{
    [m_curCameraDevcie lockForConfiguration:nil];
    if ([m_curCameraDevcie isWhiteBalanceModeSupported:AVCaptureWhiteBalanceModeLocked]) {
        AVCaptureWhiteBalanceGains currentGains = m_curCameraDevcie.deviceWhiteBalanceGains;
        if(current>8000){
            current=8000;
        }
        if(current<3000){
            current=3000;
        }
        CGFloat currentTint = [m_curCameraDevcie temperatureAndTintValuesForDeviceWhiteBalanceGains:currentGains].tint;
        AVCaptureWhiteBalanceTemperatureAndTintValues tempAndTintValues;
        tempAndTintValues.temperature = current;
        tempAndTintValues.tint = currentTint;
        AVCaptureWhiteBalanceGains deviceGains = [m_curCameraDevcie deviceWhiteBalanceGainsForTemperatureAndTintValues:tempAndTintValues];
        //        CGFloat maxWhiteBalanceGain = videoDevice.maxWhiteBalanceGain;
        //        CGFloat mixWhiteBalanceGain = videoDevice.mixWhiteBalanceGain;
        //   deviceGains = [self clampGains:deviceGains toMinVal:mixWhiteBalanceGain andMaxVal:maxWhiteBalanceGain];
        [m_curCameraDevcie setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:deviceGains completionHandler:nil];
    }
    [m_curCameraDevcie unlockForConfiguration];
}

-(CGFloat)getTemperature{
    CGFloat temperature=0;
    [m_curCameraDevcie lockForConfiguration:nil];
    if ([m_curCameraDevcie isWhiteBalanceModeSupported:AVCaptureWhiteBalanceModeLocked]) {
        AVCaptureWhiteBalanceGains currentGains = m_curCameraDevcie.deviceWhiteBalanceGains;
        temperature = [m_curCameraDevcie temperatureAndTintValuesForDeviceWhiteBalanceGains:currentGains].temperature;
    }
    [m_curCameraDevcie unlockForConfiguration];
    return temperature;
}

- (void)setCameraFocusing:(CGPoint)point{
    NSError *error = nil;
    [m_curCameraDevcie lockForConfiguration:&error];
    if ([m_curCameraDevcie isFocusPointOfInterestSupported] &&[m_curCameraDevcie isFocusModeSupported:AVCaptureFocusModeContinuousAutoFocus]) {
        [m_curCameraDevcie setFocusMode:AVCaptureFocusModeContinuousAutoFocus];
        [m_curCameraDevcie setFocusPointOfInterest:point];
    }
    [m_curCameraDevcie unlockForConfiguration];
}

- (void)openHDR{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        [m_curCameraDevcie setAutomaticallyAdjustsVideoHDREnabled:true];
        if (m_curCameraDevcie.activeFormat.isVideoHDRSupported) {
            [m_curCameraDevcie setVideoHDREnabled:YES];
        }
    }
    
}

- (void)setExposureTargetBias:(CGFloat)bias
{
    [m_curCameraDevcie lockForConfiguration:nil];
    [m_curCameraDevcie setExposureTargetBias:(float)bias completionHandler:nil];
    [m_curCameraDevcie unlockForConfiguration];
}

- (void)setCameraExposure:(CGPoint)point isContinuousAuto:(bool) flag{
//        NSError *error = nil;
//        [m_curCameraDevcie lockForConfiguration:&error];
//        if(flag){
//            if ([m_curCameraDevcie isExposureModeSupported:AVCaptureExposureModeContinuousAutoExposure ])
//            {
//                [m_curCameraDevcie setExposurePointOfInterest:point];
//                m_curCameraDevcie.exposureMode = AVCaptureExposureModeContinuousAutoExposure;
//            }
//        }else{
//            if ([m_curCameraDevcie isExposureModeSupported:AVCaptureExposureModeAutoExpose ])
//            {
//                [m_curCameraDevcie setExposurePointOfInterest:point];
//                m_curCameraDevcie.exposureMode = AVCaptureExposureModeAutoExpose;
//            }
//        }
//        [m_curCameraDevcie unlockForConfiguration];
}

- (void)setAutoContinuousWhiteMode:(BOOL)flag{
    NSError *error = nil;
    [m_curCameraDevcie lockForConfiguration:&error];
    if(flag){
        if ([m_curCameraDevcie isWhiteBalanceModeSupported:AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance]) {
            [m_curCameraDevcie setWhiteBalanceMode:AVCaptureWhiteBalanceModeContinuousAutoWhiteBalance];
        }
    }else{
        if ([m_curCameraDevcie isWhiteBalanceModeSupported:AVCaptureWhiteBalanceModeAutoWhiteBalance]) {
            [m_curCameraDevcie setWhiteBalanceMode:AVCaptureWhiteBalanceModeAutoWhiteBalance];
        }
    }
    [m_curCameraDevcie unlockForConfiguration];
}
@end
