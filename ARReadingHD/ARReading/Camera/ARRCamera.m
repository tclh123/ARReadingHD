//
//  ARRCamera.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "ARRCamera.h"

// constants
const int DefaultWidth = 640;
const int DefaultHeight = 480;

@implementation ARRCamera

// 24BGR <- 32BGRA
- (void)copyToColorBuffer_24GBR:(CVPixelBufferRef)pixelBuffer {
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    
    NSAssert(CVPixelBufferGetPixelFormatType(pixelBuffer) == kCVPixelFormatType_32BGRA,
             @"PixelFormatType not supported");
    
    size_t width = CVPixelBufferGetWidth(pixelBuffer);
    size_t height = CVPixelBufferGetHeight(pixelBuffer);
    
    if (self.width != width || self.height != height) {
        [self changeSizeWithWidth:width height:height];
    }
    
    uint8_t *baseAddress = (uint8_t *)CVPixelBufferGetBaseAddress(pixelBuffer);
    memcpy(tempBuffer, baseAddress, sizeof(unsigned char) * width * height * 4);
	unsigned char *p = tempBuffer;
    
    int idxD = 0;
	
    // x，y轴 方向？
	for (int y = height-1, idxS = width * 4 * y; y >= 0; y--) {
		for (int x = width * 4 - 4; x >= 0; x-=4) {
            colorBuffer[idxD++] = p[idxS+x];
            colorBuffer[idxD++] = p[idxS+x+1];
            colorBuffer[idxD++] = p[idxS+x+2];
		}
		idxS -= (width * 4);
	}
    
    DD(idxD);
    
    
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
}

- (id)initWithFrameRect:(CGRect)frameRect {
    self = [super initWithFrameRect:frameRect];
    
    // ARR init!
    
    // Buffer alloc
    tempBuffer = (unsigned char*)calloc(1, (DefaultWidth * DefaultHeight) * sizeof(unsigned char) * 4);
    colorBuffer = (unsigned char*)calloc(1, (DefaultWidth * DefaultHeight) * sizeof(unsigned char) * 3);
    
    // detector alloc
    detector = (ARREdgeDetector*)malloc(sizeof(ARREdgeDetector));
    
    // detector image alloc
    detector->image = (ARRImage*)malloc(sizeof(ARRImage));
    detector->image->width = DefaultWidth;
    detector->image->height = DefaultHeight;
    
    self.width = DefaultWidth;
    self.height = DefaultHeight;
    
    return self;
}

- (void)changeSizeWithWidth:(int)width height:(int)height {
    tempBuffer = (unsigned char*)reallocf(tempBuffer, (width * height) * sizeof(unsigned char) * 4);
    colorBuffer = (unsigned char*)reallocf(tempBuffer, (width * height) * sizeof(unsigned char) * 3);
    
    detector->image->width = width;
    detector->image->height = height;
    
    self.width = width;
    self.height = height;
}

- (void)captureLoop:(CMSampleBufferRef)cameraBuffer {
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(cameraBuffer);
    [self copyToColorBuffer_24GBR:imageBuffer];
    
    /////// 至此得到 colorBuffer
    
    // detector set buffer
    detector->image->data = colorBuffer;
    
    // detect markers
    ARRMarker *markers = NULL;
    
    int markers_num = 0;
    
    arrFindMarkers(detector, &markers, &markers_num);
    DD(markers_num);
}

@end
