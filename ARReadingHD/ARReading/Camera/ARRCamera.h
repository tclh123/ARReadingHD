//
//  ARRCamera.h
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "CameraController.h"

#include "ar.h"

@interface ARRCamera : CameraController {
    unsigned char *tempBuffer;  // 32
    unsigned char *colorBuffer; // 24
    ARREdgeDetector *detector;
}

@property (nonatomic, assign) int width;
@property (nonatomic, assign) int height;

- (void)copyToColorBuffer_24GBR:(CVPixelBufferRef)pixelBuffer;
- (void)changeSizeWithWidth:(int)width height:(int)height;

@end
