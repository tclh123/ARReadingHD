//
//  ARRGLView.h
//  ARReadingHD
//
//  Created by tclh123 on 13-2-22.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "CC3GLMatrix.h"

#include "ar.h"

@interface ARRGLView : GLView {
    // vertex_shader 传入变量 的指针
    GLuint _positionSlot;
    GLuint _colorSlot;
    
    // uniform matrix
    GLuint _projectionUniform;
    GLuint _modelViewUniform;
    
    // internal
//    float _currentRotation; // 维护旋转度数
    
    float _focalX;
    float _focalY;
    CC3GLMatrix *_projection;
}

@property (nonatomic, assign) CGSize cameraFrameSize;
- (void)render;
- (void)render:(ARRMarker*)markers num:(int)markers_num;

- (void)setupViewWithFocalX:(float)focalX focalY:(float)focalY;

@end
