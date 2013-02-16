//
//  vInnerP.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>

#include "matrix.h"

float arrVecInnerProduct( ARRVec *x, ARRVec *y )
{
    
    return( x->x*y->x + x->y*y->y );
}