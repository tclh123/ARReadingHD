//
//  CameraController.h
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
//#import <CoreGraphics/CoreGraphics.h>

@interface CameraController : NSObject<AVCaptureVideoDataOutputSampleBufferDelegate> {
    AVCaptureSession              *session;
}

//const
@property (nonatomic, assign) float focalLength;

// 
@property (nonatomic, retain) AVCaptureVideoPreviewLayer    *previewLayer;
@property (nonatomic, assign) float frameRatio;
@property (nonatomic, assign) float bufferWidth;
@property (nonatomic, assign) float bufferHeight;

- (id)initWithFrameRect:(CGRect)frameRect;
- (void)start;
- (void)stop;
- (BOOL)isRunning;
- (void)captureLoop:(CMSampleBufferRef)cameraBuffer;

@end
