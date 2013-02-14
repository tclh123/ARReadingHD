//
//  vInnerP.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>

#include "matrix.h"

double arrVecInnerProduct( ARRVec *x, ARRVec *y )
{
    double   result = 0.0;
    int      i;
    
    //if( x->num != y->num ) exit(0); // exit(0)?
    
    for( i = 0; i < x->num; i++ ) {
        result += x->data[i] * y->data[i];
    }
    
    return( result );
}