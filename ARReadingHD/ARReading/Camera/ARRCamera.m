//
//  ARRCamera.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-20.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "ARRCamera.h"

// constants
const int imageWidth = 640;
const int imageHeight = 480;

@implementation ARRCamera

static inline void MKDetectorHirzerCopyBuffer(CVPixelBufferRef pixelBuffer, unsigned char* colorBuffer) {
    
    uint8_t *baseAddress = (uint8_t *)CVPixelBufferGetBaseAddress(pixelBuffer);
    const size_t height = CVPixelBufferGetHeight(pixelBuffer);
    const size_t bytesPerRow = CVPixelBufferGetBytesPerRow(pixelBuffer);
    
    memcpy(colorBuffer, baseAddress, bytesPerRow * height);
}

- (id)initWithFrameRect:(CGRect)frameRect {
    self = [super initWithFrameRect:frameRect];
    
    // ARR init!
    
    // colorBuffer alloc
    colorBuffer = (unsigned char*)calloc(1, (imageWidth * imageHeight) * sizeof(unsigned char) * 4);

    // detector alloc
    detector = (ARREdgeDetector*)malloc(sizeof(ARREdgeDetector));
    
    // detector image alloc
    detector->image = (ARRImage*)malloc(sizeof(ARRImage));
    detector->image->width = imageWidth;
    detector->image->height = imageHeight;
    
    return self;
}

- (void)captureLoop:(CMSampleBufferRef)cameraBuffer {
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(cameraBuffer);

    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    NSAssert(CVPixelBufferGetPixelFormatType(imageBuffer) == kCVPixelFormatType_32BGRA,
             @"PixelFormatType not supported");
    
    const int width		= CVPixelBufferGetWidth(imageBuffer);
    const int height	= CVPixelBufferGetHeight(imageBuffer);
    if (imageWidth != width || imageHeight != height) {
//        [self imageSizedChangedWidht:width height:height];
        colorBuffer = (unsigned char*)reallocf(colorBuffer, (width * height) * sizeof(unsigned char) * 4);
        detector->image->width = width;
        detector->image->height = height;
    }
    
    MKDetectorHirzerCopyBuffer(imageBuffer, colorBuffer);
    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
    
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
