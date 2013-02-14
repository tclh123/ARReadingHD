//
//  arrSegmentIntersect.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>

#include "matrix.h"

ARRVec* arrSegmentIntersect(ARRSegment *seg, ARRSegment *seg2)
{
    ARRVec *intersection = arrVecAlloc(2);

	double denom = ( (seg2->end->position->data[1] - seg2->start->position->data[1])
                    * (seg->end->position->data[0] - seg->start->position->data[0]) )
                    -
                    ( (seg2->end->position->data[0] - seg2->start->position->data[0])
                     * (seg->end->position->data[1] - seg->start->position->data[1]) );
	
    double nume_a = ( (seg2->end->position->data[0] - seg2->start->position->data[0])
                     * (seg->start->position->data[1] - seg2->start->position->data[1]) )
                    -
                    ( (seg2->end->position->data[1] - seg2->start->position->data[1])
                     * (seg->start->position->data[0] - seg2->start->position->data[0]));
    
	double ua = nume_a / denom;
	
	intersection->data[0] = seg->start->position->data[0] + ua * (seg->end->position->data[0] - seg->start->position->data[0]);
	intersection->data[1] = seg->start->position->data[1] + ua * (seg->end->position->data[1] - seg->start->position->data[1]);
	
	return intersection;
}