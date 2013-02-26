//
//  ARRCamera.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "ARRCamera.h"


@implementation ARRCamera

// 24BGR <- 32BGRA
- (void)copyToColorBuffer_24GBR:(CVPixelBufferRef)pixelBuffer {
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    
    NSAssert(CVPixelBufferGetPixelFormatType(pixelBuffer) == kCVPixelFormatType_32BGRA,
             @"PixelFormatType not supported");
    
    size_t width = CVPixelBufferGetWidth(pixelBuffer);
    size_t height = CVPixelBufferGetHeight(pixelBuffer);
    
    if (self.bufferWidth != width || self.bufferHeight != height) {
        [self changeSizeWithWidth:width height:height];
    }
    
    uint8_t *baseAddress = (uint8_t *)CVPixelBufferGetBaseAddress(pixelBuffer);
    memcpy(tempBuffer, baseAddress, sizeof(unsigned char) * width * height * 4);
	unsigned char *p = tempBuffer;
    
    // i <- j
    for (int i=0, j=0; j<width*height*4; ) {
        colorBuffer[i++] = p[j++];
        colorBuffer[i++] = p[j++];
        colorBuffer[i++] = p[j++];
        j+=1; //skip alpha channel
    }
    
//    // x，y轴 方向？
//    int idxD = 0;
//	for (int y = height-1, idxS = width * 4 * y; y >= 0; y--) {
//		for (int x = width * 4 - 4; x >= 0; x-=4) {
//            colorBuffer[idxD++] = p[idxS+x];
//            colorBuffer[idxD++] = p[idxS+x+1];
//            colorBuffer[idxD++] = p[idxS+x+2];
//		}
//		idxS -= (width * 4);
//	}
    
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
}

// init
- (id)initWithFrameRect:(CGRect)frameRect {
    self = [super initWithFrameRect:frameRect]; // init camera
    
    // ARR init!
    
    // Buffer alloc
    tempBuffer = (unsigned char*)calloc(1, (self.bufferWidth * self.bufferHeight) * sizeof(unsigned char) * 4);
    colorBuffer = (unsigned char*)calloc(1, (self.bufferWidth * self.bufferHeight) * sizeof(unsigned char) * 3);
    
    // detector alloc
    detector = (ARREdgeDetector*)malloc(sizeof(ARREdgeDetector));
    
    // detector image alloc
    detector->image = (ARRImage*)malloc(sizeof(ARRImage));
    detector->image->width = self.bufferWidth;
    detector->image->height = self.bufferHeight;
    
    // GL init!
    self.glView = [[ARRGLView alloc] initWithFrame:CGRectMake(0, 0, frameRect.size.width, frameRect.size.width * self.frameRatio)];
    self.glView.cameraFrameSize = CGSizeMake(self.bufferWidth, self.bufferHeight);
    [self.glView setupViewWithFocalX:self.focalLength focalY:self.focalLength];
    
    return self;
}

- (void)changeSizeWithWidth:(int)width height:(int)height {
    tempBuffer = (unsigned char*)reallocf(tempBuffer, (width * height) * sizeof(unsigned char) * 4);
    colorBuffer = (unsigned char*)reallocf(colorBuffer, (width * height) * sizeof(unsigned char) * 3);
    
    detector->image->width = width;
    detector->image->height = height;
    
    self.bufferWidth = width;
    self.bufferHeight = height;
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
    
//    [self.glView render];
    [self.glView render:markers num:markers_num];
}

@end
