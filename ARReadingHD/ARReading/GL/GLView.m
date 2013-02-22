//
//  GLView.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-22.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "GLView.h"

@interface GLView()

- (void)setupLayer;
- (void)setupContext;
- (void)setupDepthBuffer;
- (void)setupRenderBuffer;
- (void)setupFrameBuffer;

@end

@implementation GLView

// override initWithFrame 构造函数
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        [self setupLayer];
        [self setupContext];
        [self setupDepthBuffer];            // depth
        [self setupRenderBuffer];           // color
        [self setupFrameBuffer];            // frame
    }
    return self;
}

// 编译 shader，并返回 handle
- (GLuint)compileShaderWithSourceCode:(NSString*)shaderSourceCode withType:(GLenum)shaderType {
    
    GLuint shaderHandle = glCreateShader(shaderType);
    
    // 把NSString转换成C-string
    const char* shaderStringUTF8 = [shaderSourceCode UTF8String];
    int shaderStringLength = [shaderSourceCode length];
    
    glShaderSource(shaderHandle, 1, &shaderStringUTF8, &shaderStringLength);
    
    // 4. 调用glCompileShader 在运行时编译shader
    glCompileShader(shaderHandle);
    
    // 5. glGetShaderiv 和 glGetShaderInfoLog  会把error信息输出到屏幕。（然后退出）
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);    // 是否成功
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);    // 什么错误
        NSString *messageString = [NSString stringWithUTF8String:messages];
        NSLog(@"%@", messageString);
        exit(1);
    }
    
    return shaderHandle;
}

// 编译 shader，并返回 handle
- (GLuint)compileShaderWithFile:(NSString*)shaderFileName withType:(GLenum)shaderType {
    
    // 1. 这是一个UIKit编程的标准用法，就是在NSBundle中查找某个文件。
    NSString* shaderPath = [[NSBundle mainBundle] pathForResource:shaderFileName
                                                           ofType:@"glsl"];
    NSError* error;
    NSString* shaderSourceCode = [NSString stringWithContentsOfFile:shaderPath
                                                       encoding:NSUTF8StringEncoding error:&error];
    if (!shaderSourceCode) {
        NSLog(@"Error loading shader: %@", error.localizedDescription);
        exit(1);
    }
    
    return [self compileShaderWithSourceCode:shaderSourceCode withType:shaderType];
}

// override layerClass, 设置为特殊的layer，用以获得OpenGL的内容
+ (Class)layerClass {
    return [CAEAGLLayer class];
}

// 设置layer为透明？
- (void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = NO;
}

// 创建OpenGL Context
- (void)setupContext {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;  //选ES2的api
    _context = [[EAGLContext alloc] initWithAPI:api];   // alloc, init
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    if (![EAGLContext setCurrentContext:_context]) {    // set EAGLContext
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

// 创建color render buffer（渲染缓冲区）
- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer); //返回一个唯一的integer来标记render buffer（这里把这个唯一值赋值到_colorRenderBuffer）
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);    //其实就是告诉OpenGL，我们定义的buffer对象是属于哪一种OpenGL对象
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer]; //为render buffer分配空间
}

// 创建depth buffer（深度测试 缓冲区）
- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    // glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}


// 创建一个 frame buffer（帧缓冲区）
- (void)setupFrameBuffer {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    // 它让你把前面创建的buffer render依附在frame buffer的GL_COLOR_ATTACHMENT0位置上。
    // glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    
    // 把 depth buffer 附到 frame buffer上
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

// 清理屏幕，并渲染
- (void)render {
    // dummy
}

@end
