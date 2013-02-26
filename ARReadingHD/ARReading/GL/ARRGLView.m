//
//  ARRGLView.m
//  ARReadingHD
//
//  Created by tclh123 on 13-2-22.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#import "ARRGLView.h"

// 顶点 信息的结构Vertex
typedef struct {
    float Position[3];  //位置
    float Color[4];     //颜色
} Vertex;

// 4个点
Vertex Vertices[] = {   // z = -1 为地面？
//    {{0, 0, -1}, {1, 0, 0, 1}},     // r                  // TODO: 为什么下面那个会抖，上面这个以前貌似不会？？
//    {{1, 0, -1}, {0, 1, 0, 1}},      // g
//    {{1, 1, -1}, {0, 0, 1, 1}},     // b
//    {{0, 1, -1}, {0, 0, 0, 1}}     // black
    
    {{-1, -1, 0}, {1, 0, 0, 1}},     // r
    {{1, -1, 0}, {0, 1, 0, 1}},      // g
    {{1, 1, 0}, {0, 0, 1, 1}},     // b
    {{-1, 1, 0}, {0, 0, 0, 1}}     // black

    // OpenGL 的 z轴是垂直屏幕向外的，所以 z坐标为负数
};
// 三角形顶点的 数组 , 存顶点index
GLubyte Indices[] = {
    0, 1, 2,    // 右上
    2, 3, 0     // 左下
};

//// 8个点
//const Vertex Vertices[] = {
//    {{1, -1, 0}, {1, 0, 0, 1}},
//    {{1, 1, 0}, {1, 0, 0, 1}},
//    {{-1, 1, 0}, {0, 1, 0, 1}},
//    {{-1, -1, 0}, {0, 1, 0, 1}},
//    
//    {{1, -1, -1}, {1, 0, 0, 1}},
//    {{1, 1, -1}, {1, 0, 0, 1}},
//    {{-1, 1, -1}, {0, 1, 0, 1}},
//    {{-1, -1, -1}, {0, 1, 0, 1}}
//};
//
//// 6个面，每个面2个三角形
//const GLubyte Indices[] = {
//    // Front
//    0, 1, 2,
//    2, 3, 0,
//    // Back
//    4, 6, 5,
//    4, 7, 6,
//    // Left
//    2, 7, 3,
//    7, 6, 2,
//    // Right
//    0, 4, 1,
//    4, 1, 5,
//    // Top
//    6, 2, 1,
//    1, 6, 5,
//    // Bottom
//    0, 3, 7,
//    0, 7, 4
//};

@implementation ARRGLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
        [self setupVertexBufferObjects];    // VBO
        
        [self compileShaders];
        
//        [self render];
    }
    return self;
}

- (void)setupViewWithFocalX:(float)focalX focalY:(float)focalY {
    _focalX = focalX;
    _focalY = focalY;
    
    _projection = [CC3GLMatrix matrix];     // WHY:用 CoreAR的 顺序不行。。？
    float left = -0.5 * self.cameraFrameSize.width / focalY;
	float right = 0.5 * self.cameraFrameSize.width / focalY;
	float bottom = -0.5 * self.cameraFrameSize.height / focalX;
	float top = 0.5 * self.cameraFrameSize.height / focalX;
    [_projection populateFromFrustumLeft:left andRight:right andBottom:bottom andTop:top andNear:1 andFar:1000];
    
    // glViewport 设置UIView中用于渲染的部分
    glViewport(0, 0, self.frame.size.width, self.frame.size.height);
}

// 清理屏幕，并渲染
- (void)render:(ARRMarker*)markers num:(int)markers_num {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(_projectionUniform, 1, GL_FALSE, _projection.glMatrix);
    
    // 配置 shader属性 指针
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(_colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (sizeof(float) *3));
    
    float matrix[4][4], matrixGL[16];
    for (int i=0; i<markers_num; i++) {
        DD(markers[i].num) DP(markers[i].c1) DP(markers[i].c2) DP(markers[i].c3) DP(markers[i].c4)
        
        arrMarkerGetTrans(&markers[i], 2.0f, self.cameraFrameSize.width, self.cameraFrameSize.height, _focalX, _focalY,
                          matrix, matrixGL);
        
        // model-view matrix
//        CC3GLMatrix *modelView = [CC3GLMatrix matrix];
//        [modelView populateFromTranslation:CC3VectorMake(0, 0, -7)];    // 平移 (x,y,z)
//        glUniformMatrix4fv(_modelViewUniform, 1, 0, modelView.glMatrix);
        
        glUniformMatrix4fv(_modelViewUniform, 1, 0, matrixGL);
        
        glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, 0);
    }
    
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

// 清理屏幕，并渲染
- (void)render {
    
    // clear
    //glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);  // 把屏幕清理一下，显示另一个颜色吧。（RGB 0, 104, 55，绿色吧）
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // 清理buffer
    //glEnable(GL_DEPTH_TEST);    // 开启深度测试
    
    // projection
    glUniformMatrix4fv(_projectionUniform, 1, GL_FALSE, _projection.glMatrix);   // *_projectionUniform <- projection.glMatrix
    
    // model-view matrix
    CC3GLMatrix *modelView = [CC3GLMatrix matrix];
    [modelView populateFromTranslation:CC3VectorMake(0, 0, -7)];    // 平移 (x,y,z)
//    _currentRotation += displayLink.duration *90;       // _currentRotation 每秒会增加90度
//    [modelView rotateBy:CC3VectorMake(_currentRotation, _currentRotation, 0)];  // 同时沿x，y轴旋转
    glUniformMatrix4fv(_modelViewUniform, 1, 0, modelView.glMatrix);
    
    // 配置 shader属性 指针
    glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), 0);   // _positionSlot是 属性 的整数索引，或者说handle；Position 有3个float；地址为0，因为Position定义在shader的开头。
    glVertexAttribPointer(_colorSlot, 4, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (GLvoid*) (sizeof(float) *3));    // 地址为 (GLvoid*) (sizeof(float) *3)，因为前面有Position（包含3个float）。
    
    // 画
    // glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
    glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]),
                   GL_UNSIGNED_BYTE, 0);    // GL_TRIANGLES 指用三角形画（与使用VBO有关）；sizeof(Indices)/sizeof(Indices[0])为要画的元素数；GL_UNSIGNED_BYTE指Indices中的类型
    
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

// VBO: vertex buffer object
- (void)setupVertexBufferObjects {     //防止指针退化
    
    // 顶点buffer
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);    // GL_STATIC_DRAW 不能被更新
    
    // 顶点索引buffer
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
}

// 在运行时编译shaders
- (void)compileShaders {
    
    // 编译vertex shader 和 fragment shader
    GLuint vertexShader = [self compileShaderWithFile:@"SimpleVertex" withType:GL_VERTEX_SHADER];
    GLuint fragmentShader = [self compileShaderWithFile:@"SimpleFragment" withType:GL_FRAGMENT_SHADER];
    
    // 连接 vertex 和 fragment shader成一个完整的program
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    // 检查是否有error，并输出信息
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);    // GL_LINK_STATUS
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        NSString *messageString = [NSString stringWithUTF8String:messages];
        NSLog(@"%@", messageString);
        exit(1);
    }
    
    // 执行program
    glUseProgram(programHandle);
    
    // 获得变量指针，启用属性
    _positionSlot = glGetAttribLocation(programHandle, "Position");
    _colorSlot = glGetAttribLocation(programHandle, "SourceColor");
    glEnableVertexAttribArray(_positionSlot);
    glEnableVertexAttribArray(_colorSlot);
    
    // 维护 Uniform 指针
    _projectionUniform = glGetUniformLocation(programHandle, "Projection");
    _modelViewUniform = glGetUniformLocation(programHandle, "Modelview");
}

@end
