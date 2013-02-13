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
typedef struct {
    ARRVec *c1, c2, c3, c4; // corner
    ARRSegment chain[ARR_EACH_MARKER_SEGMENT_MAX];
} ARRMarker;
void arrMarkerReconstruct(ARRMarker* marker);

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

// TODO: Edeg Detector's functions
/*
 int edgeKernel( unsigned char* offset, const int pitch );
 int edgeKernelX( int x, int y );
 int edgeKernelY( int x, int y );
 
 std::vector<Edgel> findEdgelsInRegion(const int left, const int top, const int width, const int height );
 std::vector<ARMarker> findMarkers();    //!!
 
 void scanLine(int offset, int step, int max, int width, int y);
 bool extendLine( Vector2f startpoint, const Vector2f slope, const Vector2f gradient, Vector2f& endpoint, const int maxlength );
 Vector2f edgeGradientIntensity(int x, int y);
 
 void setBuffer(Buffer* buffer);
 
 std::vector<LineSegment> findLineSegment(std::vector<Edgel> edgels);
 std::vector<LineSegment> mergeLineSegments(std::vector<LineSegment> linesegments, int max_iterations);
 void extendLineSegments( std::vector<LineSegment> &lineSegments );
 std::vector<LineSegment> findLinesWithCorners(std::vector<LineSegment> &linesegments);
 
 void findChainOfLines( LineSegment &startSegment, bool atStartPoint, std::vector<LineSegment> &linesegments, std::vector<LineSegment> &chain, int &length);
 
 // debug functions
 
 void debugDrawLineSegments( bool draw ) { drawLineSegments = draw; }
 void debugDrawPartialMergedLineSegments( bool draw ) { drawPartialMergedLineSegments = draw; }
 void debugDrawMergedLineSegments( bool draw ) { drawMergedLineSegments = draw; }
 void debugDrawExtendedLineSegments( bool draw ) { drawExtendedLineSegments = draw; }
 void debugDrawCorners( bool draw ) { drawCorners = draw; }
 void debugDrawMarkers( bool draw ) { drawMarkers = draw; }
 void debugDrawSectors( bool draw ) { drawSectors = draw; }
 void debugDrawEdges( bool draw ) { drawEdges = draw; }
 void debugDrawSectorGrids( bool draw ) { drawSectorGrids = draw; }
 
 void drawLine( int x1, int y1, int x2, int y2, int r, int g, int b, int t);
 void drawPoint( int x, int y, int r, int g, int b, int t);
 void drawArrow( int x1, int y1, int x2, int y2, float xn, float yn, int r, int g, int b, int t);
 */

#endif
