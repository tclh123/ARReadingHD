//
//  arrSegmentAddSupport.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>

#include "matrix.h"

int arrSegmentAddSupport(ARRSegment *seg, ARREdge *edge)
{
    if(seg->num + 1 > ARR_EACH_SEGMENT_EDGES_MAX) return -1;
    
    // edge：要不要重新alloc一个？
    
    ARREdge *edgeNew = arrEdgeAlloc(edge->position->data[0], edge->position->data[1]);
    
    if (edgeNew == NULL) {
        return -1;
    }
        
    seg->supportEdgels[seg->num++] = edgeNew;
    
    return 0;
}