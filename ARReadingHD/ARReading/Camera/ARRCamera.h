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
    unsigned char *colorBuffer;
    ARREdgeDetector *detector;
}

@end
