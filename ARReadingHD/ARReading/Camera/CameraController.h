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
    AVCaptureVideoPreviewLayer    *previewLayer;
}

//@property (nonatomic, retain) AVCaptureSession              *session;
//@property (nonatomic, retain) AVCaptureVideoPreviewLayer    *previewLayer;

- (void)initCameraWithFrameRect:(CGRect)frameRect;
- (void)start;
- (void)stop;
- (BOOL)isRunning;

@end
