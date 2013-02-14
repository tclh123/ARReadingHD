//
//  arrSegmentIsInclude.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include <math.h>

#include "matrix.h"

BOOL arrSegmentIsInclude(ARRSegment *seg, ARREdge *edge)
{
    if(!arrEdgeIsCompatible(seg->start, edge)) return FLASE;
    
	// distance to line: (AB x AC)/|AB|
	// A = r1
	// B = r2
	// C = cmp
    
	// AB ( r2.x - r1.x, r2.y - r1.y )
	// AC ( cmp.x - r1.x, cmp.y - r1.y )
    
    double cross = (seg->end->position->data[0] - seg->start->position->data[0])
                    * (edge->position->data[1] - seg->start->position->data[1]);
	cross -= (seg->end->position->data[1]- seg->start->position->data[1])
             * ( edge->position->data[0]-seg->start->position->data[0]);
    
    double d1 = seg->start->position->data[0] - seg->end->position->data[0];
    double d2 = seg->start->position->data[1] - seg->end->position->data[0];
    
    double d_length = sqrt(d1*d1 + d2*d2);  // ToDo: vLength(...)
    
    double distance = cross / d_length;
    
	return fabs(distance) < 0.75f;  //double?
}