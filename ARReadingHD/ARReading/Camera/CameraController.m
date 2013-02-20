//
//  CameraController.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "CameraController.h"

@implementation CameraController

- (void)initCameraWithFrameRect:(CGRect)frameRect {
    // input
	AVCaptureDeviceInput* input = [AVCaptureDeviceInput deviceInputWithDevice:[AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo] error:nil]; // 选了默认的 video device
    
    // output
	AVCaptureVideoDataOutput *output = [[AVCaptureVideoDataOutput alloc] init];
	output.alwaysDiscardsLateVideoFrames = YES;
    
    // 對輸出端的queue做設定
	[output setSampleBufferDelegate:self queue:dispatch_get_main_queue()];   // 异步？
    
	output.videoSettings = [NSDictionary
                            dictionaryWithObject: [NSNumber numberWithInt:kCVPixelFormatType_32BGRA]
                            forKey: (id)kCVPixelBufferPixelFormatTypeKey];
    
	// Session presets low, medium, high, 640x480...
    session = [[AVCaptureSession alloc] init];
	session.sessionPreset = AVCaptureSessionPreset640x480;
    
    if (!input) {
        //
    }
	[session addInput:input];
	[session addOutput:output];
    
	previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:session];
	previewLayer.frame = frameRect;

	//previewLayer.videoGravity = AVLayerVideoGravityResizeAspect;   // default
	//previewLayer.zPosition = -5;

	//[self.view.layer addSublayer:self.previewLayer];
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
	}
}

@end
