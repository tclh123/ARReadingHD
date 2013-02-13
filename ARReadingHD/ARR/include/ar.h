//
//  ar.h
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#ifndef ARReadingHD_ar_h
#define ARReadingHD_ar_h

#include "type.h"
#include "config.h"
#include "matrix.h"

/* Image Buffer */
typedef struct {
    int width;
    int height;
    ARRByte *data;
} ARRImage;

ARRImage* arrImageAlloc(int width, int height);
ARRByte arrImageGetPixel(ARRImage *image, int x, int y, int channel);
double arrImageGetPixelColor(ARRImage *image, int x, int y, int channel);

/* ARR Marker */



#endif
