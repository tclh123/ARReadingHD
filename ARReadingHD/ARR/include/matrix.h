//
//  matrix.h
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#ifndef ARReadingHD_matrix_h
#define ARReadingHD_matrix_h

#include "type.h"
#include "config.h"

/* vector 
    向量
 */
typedef struct {
    double *data;
    int num;
} ARRVec;

ARRVec* arrVecAlloc(int num);
int arrVecFree(ARRVec*);
double arrVecInnerProduct(ARRVec *vec1, ARRVec *vec2);

/* Edge(edgel?) 
    边缘点，有方向
 */
typedef struct {
    ARRVec *position;
    ARRVec *slope;   //斜率
} ARREdge;

ARREdge* arrEdgeAlloc(int x, int y);
BOOL arrEdgeIsCompatible(ARREdge *edge1, ARREdge *edge2);

/* linesegment
    线段
 */
typedef struct {
    ARREdge *start, *end;
    ARRVec *slope;
    BOOL remove, start_corner, end_corner;
	ARRVec *supportEdgels[ARR_EACH_SEGMENT_EDGES_MAX];
    int num;    // supportEdgels' num
} ARRSegment;

// TODO:
ARRSegment* arrSegmentAlloc(); //LineSegment() : remove(false), start_corner(false), end_corner(false) {}
BOOL arrSegmentIsInclude(ARREdge *edge);
void arrSegmentAddSupport(ARREdge *edge);
BOOL arrSegmentIsCompatible(ARRSegment *seg);
ARRVec* arrSegmentIntersect(ARRSegment *seg);
BOOL arrSegmentIsEquel(ARRSegment *seg);
/*
 return (start.position.x == rhs.start.position.x &&
 start.position.y == rhs.start.position.y &&
 end.position.x == rhs.end.position.x &&
 end.position.y == rhs.end.position.y
 );
 */


#endif
