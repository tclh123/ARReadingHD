//
//  arrSegmentIsEquel.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include "matrix.h"

BOOL arrSegmentIsEquel(ARRSegment *seg, ARRSegment *seg2)
{
    
    return (seg->start->position->data[0] == seg2->start->position->data[0] &&
            seg->start->position->data[1] == seg2->start->position->data[1] &&
            seg->end->position->data[0] == seg2->end->position->data[0] &&
            seg->end->position->data[1] == seg2->end->position->data[1]);
}