//
//  ar.h
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#ifndef ARReadingHD_ar_h
#define ARReadingHD_ar_h

#include "common.h"
#include "type.h"
#include "config.h"
#include "matrix.h"

/// 除了 ARRImage、ARREdgeDetector 结构体，其他结构体中都不含成员指针

/// 函数风格，所谓 output：指带Alloc功能的，change：只是改变值而已


/* Image Buffer */
typedef struct {
    int width;
    int height;
    ARRByte *data;
} ARRImage;

ARRImage* arrImageAlloc(int width, int height);
// TODO: free或setData？
ARRByte arrImageGetPixel(ARRImage *image, int x, int y, int channel);
double arrImageGetPixelColor(ARRImage *image, int x, int y, int channel);

/* ARR Marker */
typedef struct {
    ARRVec c1, c2, c3, c4; // corner。 TODO：保留指针还是？
    ARRSegment chain[ARR_EACH_MARKER_SEGMENT_MAX]; //4条边
    int num;    // size of chain.
} ARRMarker;
void arrMarkerReconstruct(ARRMarker *marker);
void arrMarkerCopyChain(ARRMarker *marker, ARRSegment *chain);

/* Edeg Detector */
typedef struct {
    ARRImage *image;
    
    // debug line settings
    BOOL drawLineSegments,
        drawPartialMergedLineSegments,
        drawMergedLineSegments,
        drawExtendedLineSegments,
        drawMarkers,
        drawSectors,
        drawSectorGrids,
        drawEdges,
        drawCorners;
} ARREdgeDetector;

// TODO: 把画线的抽离出来
// TODO: Edeg Detector's functions
void arrSetDebugLine(ARREdgeDetector *detector,
                     BOOL drawLineSegments,
                     BOOL drawPartialMergedLineSegments,
                     BOOL drawMergedLineSegments,
                     BOOL drawExtendedLineSegments,
                     BOOL drawCorners,
                     BOOL drawMarkers,
                     BOOL drawSectors,
                     BOOL drawSectorGrids,
                     BOOL drawEdges);

// Edge Kernel?
int arrEdgeKernel(ARRByte *offset, const int pitch);
int arrEdgeKernelX(ARREdgeDetector *detector, int x, int y);
int arrEdgeKernelY(ARREdgeDetector *detector, int x, int y);

int arrFindEdgesInRegion(ARREdgeDetector *detecotr, const int left, const int top, const int width, const int height,
                         ARREdge **edges, int *num);  //output edges, change num.
ARRVec arrEdgeGradientIntensity(ARREdgeDetector *detector, int x, int y);

int arrFindMarkers(ARREdgeDetector *detector,
                   ARRMarker **markers, int *num); //output markers, change num

//  Segments
// 找线段
int arrFindSegments(ARREdgeDetector *detector, ARREdge *edges, int edges_num,
                       ARRSegment **segments, int *num);    //output segment, change num
// 合并（连接）线段
int arrMergeSegments(ARREdgeDetector *detector, int max_iterations,
                     ARRSegment *segments, int *num);  // change segments, num  // 调用 arrExtendLine
BOOL arrExtendLine(ARREdgeDetector *detector, ARRVec *startpoint, const ARRVec *slope, const ARRVec * gradient,
                          ARRVec *endpoint, const int maxlength );    // output endpoint
// 扩展（延伸）线段
void arrExtendSegments(ARREdgeDetector *detector, ARRSegment *segments, int num);    // change segments //调用 arrExtendLine

// 找带角点的线段
int arrFindLinesWithCorners(ARREdgeDetector *detector, ARRSegment *segments, int num,
                            ARRSegment **lineWithCorners, int *line_num);  // output lineWithCorners, change line_num
// 找链（矩形4条边）
int arrFindChainOfLines(ARREdgeDetector *detector,
                        ARRSegment *startSegment,
                        BOOL atStartPoint,
                        ARRSegment *segments,
                        int *segments_num,
                        ARRSegment *chain,
                        int *chain_num,
                        int *length);     // change segments, chain, chain_num, length  // 其实chain_num == length ?


//void arrSetImageBuffer(ARREdgeDetector *detector, ARRImage *image);

 // draw functions

/*
 TODO:
 
 void setBuffer(Buffer* buffer);
 
 void drawLine( int x1, int y1, int x2, int y2, int r, int g, int b, int t);
 void drawPoint( int x, int y, int r, int g, int b, int t);
 void drawArrow( int x1, int y1, int x2, int y2, float xn, float yn, int r, int g, int b, int t);
 */

#endif
