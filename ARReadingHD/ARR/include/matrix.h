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
    float x, y;
} ARRVec;

ARRVec* arrVecAlloc(float x, float y);
int arrVecFree(ARRVec*);
double arrVecInnerProduct(ARRVec *vec1, ARRVec *vec2);

/* Edge(edgel?) 
    边缘点，有方向
 */
typedef struct {
    ARRVec position;
    ARRVec slope;   //斜率
} ARREdge;

ARREdge* arrEdgeAlloc(float x, float y);
int arrEdgeFree(ARREdge*);
BOOL arrEdgeIsCompatible(ARREdge *edge1, ARREdge *edge2);

/* linesegment
    线段
 */
typedef struct {
    ARREdge start, end;
    ARRVec slope;
    BOOL remove, start_corner, end_corner;
	ARREdge supportEdgels[ARR_EACH_SEGMENT_EDGES_MAX];     // 当 Alloc Segment
    int num;    // supportEdgels' num
} ARRSegment;

// TODO:
ARRSegment* arrSegmentAlloc(); //LineSegment() : remove(false), start_corner(false), end_corner(false) {}
int arrSegmentFree(ARRSegment*);

int arrSegmentAddSupport(ARRSegment *seg, ARREdge *edge);

BOOL arrSegmentIsInclude(ARRSegment *seg, ARREdge *edge);
BOOL arrSegmentIsCompatible(ARRSegment *seg, ARRSegment *seg2);
ARRVec arrSegmentIntersect(ARRSegment *seg, ARRSegment *seg2);
BOOL arrSegmentIsEquel(ARRSegment *seg, ARRSegment *seg2);



#endif
