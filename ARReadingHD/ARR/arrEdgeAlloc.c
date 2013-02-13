//
//  arrEdgeAlloc.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

ARREdge* arrEdgeAlloc(int x, int y) {
    ARREdge *edge = (ARREdge*)malloc(sizeof(ARREdge));
    if(edge == NULL) return NULL;
    
    edge->position = arrVecAlloc(2);
    if(edge->position == NULL) { free(edge); return NULL; }
    edge->position->data[0] = x;
    edge->position->data[1] = y;

    return edge;
}