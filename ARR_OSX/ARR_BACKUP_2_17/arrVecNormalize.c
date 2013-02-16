//
//  arrVecNormalize.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-16.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "matrix.h"

int arrVecNormalize(ARRVec *v)
{
    float length = arrVecLength(v);
    v->x /= length;
    v->y /= length;
    return 0;
}

float arrVecLength(ARRVec *v)
{
    return (float)sqrt(v->x*v->x + v->y*v->y);
}