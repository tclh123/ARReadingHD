//
//  GLView.h
//  ARReadingHD
//
//  Created by tclh123 on 13-2-22.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>   // CAEAGLLayer

@interface GLView : UIView {
    CAEAGLLayer *_eaglLayer;    // CA EAGL Layer
    EAGLContext *_context;      // EAGL context
    
    // buffer
    GLuint _colorRenderBuffer;
    GLuint _depthRenderBuffer;  // 深度测试 buffer
}

- (GLuint)compileShaderWithSourceCode:(NSString*)shaderSourceCode withType:(GLenum)shaderType;
- (GLuint)compileShaderWithFile:(NSString*)shaderFileName withType:(GLenum)shaderType;
- (void)render;

@end
