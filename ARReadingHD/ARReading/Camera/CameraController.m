//
//  CameraController.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "CameraController.h"

@implementation CameraController

- (id)initWithFrameRect:(CGRect)frameRect {
    // input
	AVCaptureDeviceInput* input = [AVCaptureDeviceInput deviceInputWithDevice:[AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo] error:nil]; // 选了默认的 video device
    
    // output
	AVCaptureVideoDataOutput *output = [[AVCaptureVideoDataOutput alloc] init];
	output.alwaysDiscardsLateVideoFrames = YES;
    
    // 對輸出端的queue做設定
	[output setSampleBufferDelegate:self queue:dispatch_get_main_queue()];
    
	output.videoSettings = [NSDictionary
                            dictionaryWithObject: [NSNumber numberWithInt:kCVPixelFormatType_32BGRA]
                            forKey: (id)kCVPixelBufferPixelFormatTypeKey];
    
	// Session presets low, medium, high, 640x480...
    session = [[AVCaptureSession alloc] init];
//    session.sessionPreset = AVCaptureSessionPreset1280x720;
    session.sessionPreset = AVCaptureSessionPreset640x480;
    
    if (!input) {
        //
    }
	[session addInput:input];
	[session addOutput:output];
    
	self.previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:session];
	self.previewLayer.frame = frameRect;
//    self.previewLayer.frame = CGRectMake(0, 0, 320, 240);
    
    //[self.previewLayer setPosition:CGPointMake(CGRectGetMidX(frameRect), CGRectGetMidY(frameRect))];  //default
    
//	self.previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;   // 保证 横纵比，剪切使全屏
	self.previewLayer.zPosition = -5;   //为了 glView在前面？

    return self;
}

- (void)start {
    //	[session startRunning];
	// Start the session. This is done asychronously since -startRunning doesn't return until the session is running.
	dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
		[session startRunning];
	});
}
- (void)stop {
	[session stopRunning];    
}
- (BOOL)isRunning {
    return [session isRunning];
}

- (void)captureLoop:(CMSampleBufferRef)cameraBuffer {

}

#pragma mark -
#pragma mark AVCaptureVideoDataOutputSampleBufferDelegate

// 输出 imageBuffer ，周期调用
- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
	if (self.isRunning) {
//		CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
//		_tic();
//		[self copyToValueBufferFromPixelBuffer:imageBuffer];        // 这里
//		_toc();
//		[self updatePreviewView];
        [self captureLoop:sampleBuffer];
	}
}

@end
